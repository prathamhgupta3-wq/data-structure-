import Database from 'better-sqlite3';
import fs from 'node:fs';
import path from 'node:path';
const file = path.resolve(process.env.DB_PATH || './data/ecocircuit.db');
fs.mkdirSync(path.dirname(file), { recursive: true });
export const db = new Database(file);
db.pragma('journal_mode = WAL');
db.pragma('foreign_keys = ON');
db.exec(`
CREATE TABLE IF NOT EXISTS users (
 id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, email TEXT NOT NULL UNIQUE,
 password_hash TEXT NOT NULL, phone TEXT, role TEXT NOT NULL DEFAULT 'citizen'
 CHECK(role IN ('citizen','collector','admin')), verified INTEGER NOT NULL DEFAULT 0,
 created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE IF NOT EXISTS waste_categories (
 id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL UNIQUE, description TEXT
);
CREATE TABLE IF NOT EXISTS collection_centres (
 id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, address TEXT NOT NULL,
 locality TEXT, pincode TEXT, latitude REAL, longitude REAL, phone TEXT,
 accepted_categories TEXT NOT NULL DEFAULT '[]', verified INTEGER NOT NULL DEFAULT 0,
 created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE IF NOT EXISTS pickup_requests (
 id INTEGER PRIMARY KEY AUTOINCREMENT, citizen_id INTEGER NOT NULL REFERENCES users(id),
 collector_id INTEGER REFERENCES users(id), category_id INTEGER NOT NULL REFERENCES waste_categories(id),
 quantity INTEGER NOT NULL CHECK(quantity > 0), address TEXT NOT NULL, pincode TEXT NOT NULL,
 preferred_date TEXT NOT NULL, notes TEXT, status TEXT NOT NULL DEFAULT 'pending'
 CHECK(status IN ('pending','assigned','accepted','collected','delivered','completed','cancelled','failed')),
 created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP, updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE IF NOT EXISTS pickup_status_history (
 id INTEGER PRIMARY KEY AUTOINCREMENT, pickup_id INTEGER NOT NULL REFERENCES pickup_requests(id),
 old_status TEXT, new_status TEXT NOT NULL, changed_by INTEGER NOT NULL REFERENCES users(id),
 changed_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);
CREATE INDEX IF NOT EXISTS idx_pickup_citizen ON pickup_requests(citizen_id);
CREATE INDEX IF NOT EXISTS idx_pickup_collector ON pickup_requests(collector_id);
`);
for (const name of ['Mobile phones','Laptops','Batteries','Chargers and cables','Small appliances','Large appliances','Other electronics']) db.prepare('INSERT OR IGNORE INTO waste_categories (name) VALUES (?)').run(name);
