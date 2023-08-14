import os

from flask import Flask, flash, redirect, render_template, request, url_for
from datetime import datetime


app = Flask(__name__)
import sqlite3

conn = sqlite3.connect('test.db')
@app.route('/')
def index():
    return render_template('index.html')


if __name__ == "__main__":
    app.run(debug=True)