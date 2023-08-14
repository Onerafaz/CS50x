import os
import sqlite3
from datetime import datetime

from flask import Flask, flash, redirect, render_template, request, url_for

app = Flask(__name__)


conn = sqlite3.connect('/instance/test.db')


@app.route('/')
def index():
    return render_template('index.html')


if __name__ == "__main__":
    app.run(debug=True)