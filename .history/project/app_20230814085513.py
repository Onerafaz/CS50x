import os
import sqlite3
from datetime import datetime

from flask import Flask, flash, redirect, render_template, request, url_for

app = Flask(__name__)


conn = sqlite3.connect('/instance/test.db')

conn.execute('''CREATE TABLE COMPANY
         (ID INT PRIMARY KEY     NOT NULL,
         NAME           TEXT    NOT NULL,
         AGE            INT     NOT NULL,
         ADDRESS        CHAR(50),
         SALARY         REAL);''')
print "Table created successfully";

conn.close()


@app.route('/')
def index():
    return render_template('index.html')


if __name__ == "__main__":
    app.run(debug=True)