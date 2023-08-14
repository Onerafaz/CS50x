import os

from flask import Flask, flash, redirect, render_template, request, url_for
from datetime import datetime
import sqlite3

app = Flask(__name__)


conn = sqlite3.connect('test.db')
@app.route('/')
def index():
    return render_template('index.html')


if __name__ == "__main__":
    app.run(debug=True)