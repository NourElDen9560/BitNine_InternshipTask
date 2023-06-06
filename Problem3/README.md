# Problem 3: How To install node modules and Run Source code

## 1-NodeJS
- You need to have node and postgresql installed  on your operating system

- open terminal in the file location: ```problem3/1-NodeJs/node-postgres``` 

- run: ```npm install``` to install the driver modules

- run this query to create a table ```user_table```

```
# Postgresql table
CREATE TABLE IF NOT EXISTS public.user_table
(
user_id numeric(10,0) NOT NULL,
name character varying(50) COLLATE pg_catalog."default" NOT NULL, age numeric(3,0) NOT NULL,
phone character varying(20) COLLATE pg_catalog."default",
CONSTRAINT user_table_pkey PRIMARY KEY (user_id)
);
INSERT INTO public.user_table (user_id, name, age, phone) VALUES (3, 'Jenny', 34, NULL);
INSERT INTO public.user_table (user_id, name, age, phone) VALUES (2, 'Tom', 29, '1-800-123-1234'); 
INSERT INTO public.user_table (user_id, name, age, phone) VALUES (1, 'John', 28, NULL); 
``` 

- please connect your database to the driver by going to the src folder ```Problem3/1-NodeJs/src``` and open the db.js, and write your database credentials here:
```
const pool = new Pool({
  host: 'localhost',
  database: 'public',
  user: 'postgres',
  password: '<enter password of the postgres user>',
  port: 5432
});
```
- go to the src folder ```Problem3/1-NodeJs/src```, open terminal and run: ```node app.js```



### Development Environment & My Changes in the node-postgres dirver & How PG Works

After Analyzing the src code of node-posgres or "pg" driver, i concluded the following:

- pg contains three main modules: ```Client```, ```Query```, ```Result```.
- when we make a query using ```client/pool.query()```, pg creates a Client class and calls the ```Client.query()``` which makes a Query class, Query class then goes to the database running service and then calls  ```Result``` class (which has the structure of the returned Result) and then Result is stored in Query as a property.
- NodeJs uses async and Event Driven programming, it forms each row one after another using event emmiters.
- when all the rows are ready, ```Query.handleReadyForQuery()```fires ```end``` event with Result to the end user.
- i changed the returned result in this function.

## 2- Python
- I installed psycopg2 but i faced problems regarding the import file systems, it seems like the setup.py builds a file that is missing some libraries
- however, you can find the code i have written in the ```Problem3/2-Python/main.py```
