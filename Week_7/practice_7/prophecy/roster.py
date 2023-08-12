import csv
from cs50 import SQL

db = SQL("sqlite:///roster.db")


# Connect to the database
db = SQL("sqlite:///roster.db")

# Delete data from the house_assignments table first
db.execute("DELETE FROM house_assignments;")

# Delete all data from the students and houses tables
db.execute("DELETE FROM students;")
db.execute("DELETE FROM houses;")


# Open the CSV file and insert data into the 'students' and 'houses' tables
with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        student_name = row["student_name"]
        house = row["house"]
        head = row["head"]

        # Check if the student already exists in the 'students' table
        existing_student = db.execute("SELECT id FROM students WHERE student_name=?", student_name)

        if not existing_student:
            # If the student does not exist, insert it into the 'students' table
            db.execute("INSERT INTO students (student_name) VALUES (?)", student_name)
            student_id = db.execute("SELECT id FROM students WHERE student_name=?", student_name)[0]["id"]

            # Check if the house already exists in the 'houses' table
            existing_house = db.execute("SELECT id FROM houses WHERE house=?", house)

            if not existing_house:
                # If the house does not exist, insert it into the 'houses' table
                db.execute("INSERT INTO houses (house, head) VALUES (?, ?)", house, head)
                house_id = db.execute("SELECT id FROM houses WHERE house=?", house)[0]["id"]
            else:
                house_id = existing_house[0]["id"]

            # Insert the student-house assignment into the 'house_assignments' table
            db.execute("INSERT INTO house_assignments (student_id, house_id) VALUES (?, ?)", student_id, house_id)
