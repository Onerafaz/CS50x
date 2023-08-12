CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE students (
    id INTEGER NOT NULL,
    student_name TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    id INTEGER NOT NULL,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE house_assignments (
    student_id INTEGER,
    house_id INTEGER,
    FOREIGN KEY (student_id) REFERENCES students(id),
    FOREIGN KEY (house_id) REFERENCES houses(id)
);