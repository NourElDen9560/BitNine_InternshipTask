const pool = require("./db");
 

pool.query("SELECT * FROM Users")
.then(result => {
  console.log("RESULT: ", result);
})
.catch(error => console.error(error));

pool.end();


