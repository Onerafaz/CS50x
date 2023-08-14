import os
import sqlite3
from datetime import datetime

from flask import Flask, flash, redirect, render_template, request, session, url_for, jsonify
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, sql_command, sql_query


app = Flask(__name__)


# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = sql_query(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation")

        # Ensure confirmation matches the password
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match")

        # Add rows into Database
        else:
            user = request.form.get("username")
            password = generate_password_hash(request.form.get("password"))

            try:
                # Insert user data into the database
                new_user = sql_command(
                    "INSERT INTO users (name, password) VALUES (?, ?)", user, password
                )
            except:
                # If error is returned the it means username is already taken
                return apology("username already exists")

            # Initialize session without going to login
            session["user_id"] = new_user

            return redirect("/")

    return render_template("register.html")


@app.route('/')
@login_required
def index():
    """After login show content"""
    user_id = session["user_id"]
    
    return render_template('index.html')


@app.route("/check")
def check_username():
    username = request.args.get("username")
    is_available = True

    if username:
        rows = sql_query("SELECT username FROM users WHERE username = ?", username)
        is_available = len(rows) == 0

    return jsonify({"available": is_available})


if __name__ == "__main__":
    app.run(debug=True)