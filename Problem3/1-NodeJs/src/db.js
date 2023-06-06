const { Pool } = require("../node-postgres/packages/pg");

const pool = new Pool({
  user: 'postgres',
  host: 'localhost',
  database: 'public',
  password: 'enterYourPassowrdPlease',
  port: 5432,
});

module.exports = pool;