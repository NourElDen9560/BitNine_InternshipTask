from psycopg2 import connect

connection = connect(
            host = "localhost",
            database="test",
            user = "postgres",
            password = "159787845pg")

cursor = connection.cursor()

cursor.execute("select * from user_table")

rows = cursor.fetchall()

print(rows)

connection.commit()

cursor.close()

connection.close()



