import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]

    # Retrieve the user's portfolio data from the database (pseudocode)
    transactions_db = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price, ROUND(shares * price, 2) as value FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0",
        user_id,
    )
    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

    cash = round(cash_db[0]["cash"], 2)
    total = round(sum(row["value"] for row in transactions_db) + cash, 2)

    # Render the template with the processed portfolio data
    return render_template(
        "index.html", database=transactions_db, cash=cash, total=total
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Handle the empty entries
        if not symbol:
            return apology("Please provide a symbol")

        stock = lookup(symbol.upper())

        if stock == None:
            return apology("Symbol does not exist")

        try:
            shares = float(shares)
            if shares <= 0 or not shares.is_integer():
                return apology("Enter a valid positive integer number of shares")
        except ValueError:
            return apology("Enter a valid number of shares")

        transaction_value = shares * stock["price"]

        user_id = session["user_id"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        if user_cash < transaction_value:
            return apology("Not enough cash in bank")

        updt_cash = user_cash - transaction_value

        db.execute("UPDATE users SET cash = ? WHERE id = ?", updt_cash, user_id)

        date = datetime.datetime.now()

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
            user_id,
            stock["symbol"],
            int(shares),
            stock["price"],
            date,
        )

        flash("Bought!")

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]

    # Retrieve the user's portfolio data from the database (pseudocode)
    transactions_db = db.execute(
        "SELECT * FROM transactions WHERE user_id = ?", user_id
    )

    # Render the template with the processed portfolio data
    return render_template("history.html", database=transactions_db)


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
        rows = db.execute(
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


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    ## API token = pk_88fec634e36f4f47b3a75bb98c1132ca
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("no symbol provided")

        stock = lookup(symbol.upper())

        if stock == None:
            return apology("symbol not available")

        return render_template(
            "quoted.html",
            name=stock["name"],
            price=stock["price"],
            symbol=stock["symbol"],
        )

    return render_template("/quote.html")


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
                new_user = db.execute(
                    "INSERT INTO users (username, hash) VALUES (?, ?)", user, password
                )
            except:
                # If error is returned the it means usernme is already taken
                return apology("username already exists")

            # Initialize session without going to login
            session["user_id"] = new_user

            return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        # Ensure stock symbol is selected
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must select a stock symbol")

        # Ensure shares is a positive integer
        shares = request.form.get("shares")
        if not shares or not shares.isdigit():
            return apology("invalid number of shares")

        shares = int(shares)

        # Query database for user's shares of the selected stock
        rows = db.execute(
            "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
            session["user_id"],
            symbol,
        )

        if len(rows) != 1 or rows[0]["total_shares"] < shares:
            return apology("not enough shares to sell")

        # Retrieve stock's current price
        stock = lookup(symbol)
        if not stock:
            return apology("invalid stock symbol")

        # Calculate the total value of the sold shares
        value = shares * stock["price"]

        date = datetime.datetime.now()

        # Update the user's portfolio and transactions
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
            session["user_id"],
            symbol,
            -shares,
            stock["price"],
            date,
        )
        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?", value, session["user_id"]
        )

        flash("Sold!")

        # Redirect user to home page
        return redirect("/")

    else:
        # Query database for user's owned stock symbols
        rows = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0",
            session["user_id"],
        )
        symbols = [row["symbol"] for row in rows]

        selected_symbol = request.args.get("symbol")
        user_shares = 0

        if selected_symbol in symbols:
            user_shares_query = db.execute(
                "SELECT SUM(shares) FROM transactions WHERE user_id = ? AND symbol = ?",
                session["user_id"],
                selected_symbol,
            )
            user_shares = (
                user_shares_query[0]["SUM(shares)"]
                if user_shares_query and "SUM(shares)" in user_shares_query[0]
                else 0
            )

        return render_template(
            "sell.html",
            symbols=symbols,
            selected_symbol=selected_symbol,
            user_shares=user_shares,
        )


@app.route("/check")
def check_username():
    username = request.args.get("username")
    is_available = True

    if username:
        rows = db.execute("SELECT username FROM users WHERE username = ?", username)
        is_available = len(rows) == 0

    return jsonify({"available": is_available})


@app.route("/deposit", methods=["POST"])
@login_required
def deposit():
    """Deposit cash into account"""
    amount = request.form.get("amount")
    if not amount or float(amount) <= 0:
        return apology("Enter a valid amount to deposit")

    user_id = session["user_id"]
    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", amount, user_id)

    flash("Cash deposited!")

    # Redirect back to the index page
    return redirect("/")


@app.route("/withdraw", methods=["POST"])
@login_required
def withdraw():
    """Withdraw cash from account"""
    amount = request.form.get("amount")
    if not amount or float(amount) <= 0:
        return apology("Enter a valid amount to withdraw")

    user_id = session["user_id"]
    user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    user_cash = user_cash_db[0]["cash"]

    if float(amount) > user_cash:
        return apology("Insufficient funds")

    db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", amount, user_id)

    flash("Cash withdrawn!")

    # Redirect back to the index page
    return redirect("/")
