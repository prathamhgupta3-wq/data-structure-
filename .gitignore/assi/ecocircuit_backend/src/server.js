import 'dotenv/config';
import express from 'express';
import cors from 'cors';
import helmet from 'helmet';
import rateLimit from 'express-rate-limit';
import bcrypt from 'bcryptjs';
import jwt from 'jsonwebtoken';
import { z, ZodError } from 'zod';
import { db } from './db.js';
import path from 'node:path';
import { fileURLToPath } from 'node:url';

if (!process.env.JWT_SECRET || process.env.JWT_SECRET.length < 32) throw new Error('Set JWT_SECRET (at least 32 characters) in .env');
const app = express();
app.use(helmet({ contentSecurityPolicy: false }));
app.use(cors({ origin: (process.env.CORS_ORIGIN || 'http://localhost:5173,http://localhost:4000').split(',') }));
app.use(express.json({ limit: '30kb' }));
app.use('/api/auth', rateLimit({ windowMs: 15 * 60 * 1000, limit: 30, standardHeaders: 'draft-7', legacyHeaders: false }));
const wrap = fn => (req,res,next) => { try { Promise.resolve(fn(req,res,next)).catch(next); } catch(e) { next(e); } };
const email = z.string().email().max(254).transform(s=>s.toLowerCase());
const password = z.string().min(8).max(128);
const publicUser = u => ({ id:u.id, name:u.name, email:u.email, phone:u.phone, role:u.role, verified:!!u.verified });
const tokenFor = u => jwt.sign({ sub:String(u.id) },process.env.JWT_SECRET,{ expiresIn:'12h' });
function auth(req,res,next) {
 const token = /^Bearer (.+)$/.exec(req.headers.authorization || '')?.[1];
 if (!token) return res.status(401).json({error:'Authentication required'});
 try { const payload = jwt.verify(token,process.env.JWT_SECRET); const u=db.prepare('SELECT * FROM users WHERE id=?').get(payload.sub); if (!u) return res.status(401).json({error:'Account not found'}); req.user=u; next(); }
 catch { res.status(401).json({error:'Invalid or expired token'}); }
}
const role = (...roles) => (req,res,next) => roles.includes(req.user.role) ? next() : res.status(403).json({error:'Insufficient permissions'});
const id = z.coerce.number().int().positive();
const pickupInput = z.object({ category_id:id, quantity:z.number().int().positive().max(10000), address:z.string().trim().min(8).max(500), pincode:z.string().regex(/^\d{6}$/), preferred_date:z.string().regex(/^\d{4}-\d{2}-\d{2}$/).refine(s=>!Number.isNaN(Date.parse(s)) && new Date(s).toISOString().slice(0,10)===s && s>=new Date().toISOString().slice(0,10),'Invalid or past date'), notes:z.string().max(1000).optional().default('') }).strict();
const fetchPickup = n => db.prepare('SELECT * FROM pickup_requests WHERE id=?').get(n);
const logStatus = db.prepare('INSERT INTO pickup_status_history(pickup_id,old_status,new_status,changed_by) VALUES (?,?,?,?)');

app.get('/api/health',(req,res)=>res.json({ok:true,service:'EcoCircuit API'}));
app.post('/api/auth/register',wrap(async(req,res)=>{
 const data=z.object({name:z.string().trim().min(2).max(100),email,password,phone:z.string().max(20).optional()}).strict().parse(req.body);
 if(db.prepare('SELECT id FROM users WHERE email=?').get(data.email)) return res.status(409).json({error:'Email already registered'});
 const hash=await bcrypt.hash(data.password,12);
 const result=db.prepare('INSERT INTO users(name,email,password_hash,phone,role) VALUES(?,?,?,?,?)').run(data.name,data.email,hash,data.phone||null,'citizen');
 const u=db.prepare('SELECT * FROM users WHERE id=?').get(result.lastInsertRowid);
 res.status(201).json({user:publicUser(u),token:tokenFor(u)});
}));
app.post('/api/auth/login',wrap(async(req,res)=>{
 const data=z.object({email,password:z.string()}).strict().parse(req.body);
 const u=db.prepare('SELECT * FROM users WHERE email=?').get(data.email);
 if(!u || !(await bcrypt.compare(data.password,u.password_hash))) return res.status(401).json({error:'Invalid credentials'});
 res.json({user:publicUser(u),token:tokenFor(u)});
}));
app.get('/api/auth/me',auth,(req,res)=>res.json({user:publicUser(req.user)}));
app.get('/api/categories',(req,res)=>res.json(db.prepare('SELECT * FROM waste_categories ORDER BY name').all()));
app.get('/api/centres',(req,res)=>res.json(db.prepare('SELECT * FROM collection_centres WHERE verified=1 ORDER BY name').all().map(c=>({...c,accepted_categories:JSON.parse(c.accepted_categories)}))));
app.get('/api/pickups',auth,(req,res)=>{
 const q=req.user.role==='admin' ? db.prepare('SELECT * FROM pickup_requests ORDER BY id DESC').all() : req.user.role==='collector' ? db.prepare('SELECT * FROM pickup_requests WHERE collector_id=? ORDER BY id DESC').all(req.user.id) : db.prepare('SELECT * FROM pickup_requests WHERE citizen_id=? ORDER BY id DESC').all(req.user.id);
 res.json(q);
});
app.post('/api/pickups',auth,role('citizen'),wrap((req,res)=>{
 const p=pickupInput.parse(req.body);
 if(!db.prepare('SELECT id FROM waste_categories WHERE id=?').get(p.category_id)) return res.status(400).json({error:'Unknown category'});
 const r=db.prepare('INSERT INTO pickup_requests(citizen_id,category_id,quantity,address,pincode,preferred_date,notes) VALUES(?,?,?,?,?,?,?)').run(req.user.id,p.category_id,p.quantity,p.address,p.pincode,p.preferred_date,p.notes);
 logStatus.run(r.lastInsertRowid,null,'pending',req.user.id);
 res.status(201).json(fetchPickup(r.lastInsertRowid));
}));
app.get('/api/pickups/:id',auth,wrap((req,res)=>{
 const p=fetchPickup(id.parse(req.params.id));
 if(!p) return res.status(404).json({error:'Pickup not found'});
 if(req.user.role!=='admin' && !(req.user.role==='citizen' && p.citizen_id===req.user.id) && !(req.user.role==='collector' && p.collector_id===req.user.id)) return res.status(403).json({error:'Forbidden'});
 res.json({...p,history:db.prepare('SELECT * FROM pickup_status_history WHERE pickup_id=? ORDER BY id').all(p.id)});
}));
app.patch('/api/pickups/:id/cancel',auth,role('citizen'),wrap((req,res)=>{
 const n=id.parse(req.params.id); const p=fetchPickup(n);
 if(!p || p.citizen_id!==req.user.id) return res.status(404).json({error:'Pickup not found'});
 if(!['pending','assigned'].includes(p.status)) return res.status(409).json({error:'Pickup cannot be cancelled now'});
 db.transaction(()=>{db.prepare("UPDATE pickup_requests SET status='cancelled',updated_at=CURRENT_TIMESTAMP WHERE id=?").run(n);logStatus.run(n,p.status,'cancelled',req.user.id);})();
 res.json(fetchPickup(n));
}));
app.patch('/api/pickups/:id/assign',auth,role('admin'),wrap((req,res)=>{
 const n=id.parse(req.params.id), collectorId=z.object({collector_id:id}).strict().parse(req.body).collector_id;
 const p=fetchPickup(n);if(!p) return res.status(404).json({error:'Pickup not found'});
 if(p.status!=='pending') return res.status(409).json({error:'Only pending pickups can be assigned'});
 const c=db.prepare("SELECT id FROM users WHERE id=? AND role='collector' AND verified=1").get(collectorId);
 if(!c) return res.status(400).json({error:'Collector not found or not verified'});
 db.transaction(()=>{db.prepare("UPDATE pickup_requests SET collector_id=?,status='assigned',updated_at=CURRENT_TIMESTAMP WHERE id=?").run(collectorId,n);logStatus.run(n,p.status,'assigned',req.user.id);})();
 res.json(fetchPickup(n));
}));
const transitions={assigned:['accepted','failed'],accepted:['collected','failed'],collected:['delivered'],delivered:['completed']};
app.patch('/api/pickups/:id/status',auth,role('collector','admin'),wrap((req,res)=>{
 const n=id.parse(req.params.id), {status}=z.object({status:z.enum(['accepted','collected','delivered','completed','failed'])}).strict().parse(req.body);
 const p=fetchPickup(n);if(!p) return res.status(404).json({error:'Pickup not found'});
 if(req.user.role==='collector' && p.collector_id!==req.user.id) return res.status(403).json({error:'Not assigned to you'});
 if(!transitions[p.status]?.includes(status)) return res.status(409).json({error:`Cannot change ${p.status} to ${status}`});
 db.transaction(()=>{db.prepare('UPDATE pickup_requests SET status=?,updated_at=CURRENT_TIMESTAMP WHERE id=?').run(status,n);logStatus.run(n,p.status,status,req.user.id);})();
 res.json(fetchPickup(n));
}));
app.get('/api/admin/stats',auth,role('admin'),(req,res)=>res.json({users:db.prepare('SELECT COUNT(*) AS n FROM users').get().n,pickups:db.prepare('SELECT COUNT(*) AS n FROM pickup_requests').get().n,byStatus:db.prepare('SELECT status,COUNT(*) AS count FROM pickup_requests GROUP BY status').all()}));
app.post('/api/admin/collectors',auth,role('admin'),wrap(async(req,res)=>{
 const d=z.object({name:z.string().min(2).max(100),email,password,phone:z.string().max(20).optional()}).strict().parse(req.body);
 if(db.prepare('SELECT id FROM users WHERE email=?').get(d.email)) return res.status(409).json({error:'Email already exists'});
 const r=db.prepare("INSERT INTO users(name,email,password_hash,phone,role,verified) VALUES(?,?,?,?, 'collector',1)").run(d.name,d.email,await bcrypt.hash(d.password,12),d.phone||null);
 res.status(201).json({user:publicUser(db.prepare('SELECT * FROM users WHERE id=?').get(r.lastInsertRowid))});
}));
app.get('/api/admin/collectors',auth,role('admin'),(req,res)=>res.json(db.prepare("SELECT id,name,email,phone,verified FROM users WHERE role='collector'").all()));
app.post('/api/admin/centres',auth,role('admin'),wrap((req,res)=>{
 const d=z.object({name:z.string().min(2).max(150),address:z.string().min(5).max(500),locality:z.string().max(100).optional(),pincode:z.string().regex(/^\d{6}$/).optional(),latitude:z.number().min(-90).max(90).nullable().optional(),longitude:z.number().min(-180).max(180).nullable().optional(),phone:z.string().max(20).optional(),accepted_categories:z.array(z.string().max(80)).max(30).default([]),verified:z.boolean().default(false)}).strict().parse(req.body);
 const r=db.prepare('INSERT INTO collection_centres(name,address,locality,pincode,latitude,longitude,phone,accepted_categories,verified) VALUES(?,?,?,?,?,?,?,?,?)').run(d.name,d.address,d.locality||null,d.pincode||null,d.latitude??null,d.longitude??null,d.phone||null,JSON.stringify(d.accepted_categories),Number(d.verified));
 res.status(201).json({id:Number(r.lastInsertRowid)});
}));
// One-time initial admin setup; remove ADMIN_SETUP_KEY from the environment after use.
app.post('/api/setup/admin',rateLimit({windowMs:60*60*1000,limit:5}),wrap(async(req,res)=>{
 if(!process.env.ADMIN_SETUP_KEY || process.env.ADMIN_SETUP_KEY.length<32) return res.status(404).json({error:'Not available'});
 if(db.prepare("SELECT id FROM users WHERE role='admin'").get()) return res.status(409).json({error:'Admin already exists'});
 const d=z.object({setup_key:z.string(),name:z.string().min(2),email,password}).strict().parse(req.body);
 const a=Buffer.from(d.setup_key),b=Buffer.from(process.env.ADMIN_SETUP_KEY);
 const {timingSafeEqual}=await import('node:crypto');
 if(a.length!==b.length || !timingSafeEqual(a,b)) return res.status(403).json({error:'Invalid setup key'});
 const hash=await bcrypt.hash(d.password,12);
 try {const r=db.prepare("INSERT INTO users(name,email,password_hash,role,verified) VALUES(?,?,?,'admin',1)").run(d.name,d.email,hash);res.status(201).json({user:publicUser(db.prepare('SELECT * FROM users WHERE id=?').get(r.lastInsertRowid))});}
 catch(e){if(e.code==='SQLITE_CONSTRAINT_UNIQUE') return res.status(409).json({error:'Email already registered'});throw e;}
}));
const root=path.dirname(fileURLToPath(import.meta.url));
app.use(express.static(path.resolve(root,'../frontend')));
app.get('/',(req,res)=>res.sendFile(path.resolve(root,'../frontend/index.html')));
app.use((req,res)=>res.status(404).json({error:'Route not found'}));
app.use((err,req,res,next)=>{
 if(err instanceof ZodError) return res.status(400).json({error:'Invalid input',details:err.issues.map(x=>({field:x.path.join('.'),message:x.message}))});
 if(err.code==='SQLITE_CONSTRAINT_UNIQUE') return res.status(409).json({error:'Duplicate entry'});
 if(err.code?.startsWith('SQLITE_CONSTRAINT')) return res.status(400).json({error:'Database constraint failed'});
 console.error(err);res.status(500).json({error:'Internal server error'});
});
const port=Number(process.env.PORT||4000);
app.listen(port,()=>console.log(`EcoCircuit running at http://localhost:${port}`));
