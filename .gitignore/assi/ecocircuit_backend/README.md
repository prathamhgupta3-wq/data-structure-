# EcoCircuit backend (Node.js + Express + SQLite)

This backend is designed for the **uploaded Stitch EcoCircuit HTML frontend**. It includes citizen registration/login, collector and admin roles, e-waste categories, collection centres, pickup requests, status tracking, and admin statistics.

## Run locally (Node.js 20+)

```bash
npm install
cp .env.example .env
# Edit .env: replace JWT_SECRET and ADMIN_SETUP_KEY with separate random 32+ character secrets
npm start
```

Visit `http://localhost:4000` to view the original Stitch frontend. API health: `http://localhost:4000/api/health`.

**Important:** The Stitch frontend is a static design with placeholder alerts and is **not wired to the API**. Connect its forms and buttons using `fetch()` or build dedicated login/dashboard pages. A frontend integration example is below. The API is operational after setup; the full application is not finished.

## Create the first admin

Only while no admin exists, POST `/api/setup/admin` with:

```json
{"setup_key":"your-ADMIN_SETUP_KEY","name":"Administrator","email":"admin@example.com","password":"strong-password-123"}
```

Then remove `ADMIN_SETUP_KEY` from `.env` and restart the server. **Never put the setup key in frontend code.**

## Main API endpoints

| Method | Route | Access |
|---|---|---|
| GET | `/api/health` | Public |
| POST | `/api/auth/register` | Public (citizen only) |
| POST | `/api/auth/login` | Public |
| GET | `/api/auth/me` | Logged in |
| GET | `/api/categories` | Public |
| GET | `/api/centres` | Public (verified only) |
| POST | `/api/pickups` | Citizen |
| GET | `/api/pickups` | Logged in (scoped by role) |
| GET | `/api/pickups/:id` | Owner, assigned collector, admin |
| PATCH | `/api/pickups/:id/cancel` | Owner citizen |
| PATCH | `/api/pickups/:id/assign` | Admin |
| PATCH | `/api/pickups/:id/status` | Assigned collector, admin |
| GET | `/api/admin/stats` | Admin |
| POST/GET | `/api/admin/collectors` | Admin |
| POST | `/api/admin/centres` | Admin |

## Example calls

Register citizen:

```bash
curl -X POST http://localhost:4000/api/auth/register -H 'Content-Type: application/json' -d '{"name":"Demo User","email":"demo@example.com","password":"strong-password-123","phone":"9999999999"}'
```

Use the returned token in `Authorization: Bearer YOUR_TOKEN`.

Create pickup:

```bash
curl -X POST http://localhost:4000/api/pickups -H 'Content-Type: application/json' -H 'Authorization: Bearer YOUR_TOKEN' -d '{"category_id":1,"quantity":2,"address":"Akurdi, Pimpri Chinchwad, Pune","pincode":"411035","preferred_date":"2026-12-01","notes":"Old electronics"}'
```

Frontend fetch example:

```js
const response = await fetch('/api/categories');
const categories = await response.json();
```

## Data and security notes

- SQLite database is created automatically in `data/ecocircuit.db` (gitignored).
- Passwords are hashed with bcrypt; JWT authentication lasts 12 hours.
- Only admins can create verified collector accounts and add centres.
- No verified centres are seeded: add only real, checked locations.
- Status workflow: pending → assigned → accepted → collected → delivered → completed. Failed/cancelled branches are supported.
- For public production deployment: configure HTTPS, robust backup and monitoring, real verification procedures, stronger account/session management, tests, and an appropriate hosted database. The setup is a local/demo foundation, not a production certification.
- Do not imply pickups, recycling payments, official municipal partnership, or collection-centre verification without actual arrangements.
