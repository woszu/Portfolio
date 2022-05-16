import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():

    # show current user portfolio on main page of finance
    users = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0", user_id=session["user_id"])
    quotes = {}

    for stock in stocks:
        quotes[stock["symbol"]] = lookup(stock["symbol"])

    cash_remaining = users[0]["cash"]
    total = cash_remaining

    return render_template("index.html", quotes=quotes, stocks=stocks, total=total, cash_remaining=cash_remaining)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Check if symbol is provided
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Check if number is provided
        elif not request.form.get("shares"):
            return apology("must provide number of shares you want to buy", 400)

        # Symbol check
        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("No such symbol in stock!", 400)

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("You can buy only positive integer number of shares", 400)

        if shares < 1:
            return apology("can't buy less than 1 shares", 400)

        # User check
        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

        # Check if user can affort to make transaction
        cash_remaining = rows[0]["cash"]
        price_per_share = quote["price"]
        total_price = price_per_share * shares

        if cash_remaining < total_price:
            return apology("You need more money!")

        db.execute("UPDATE users SET cash = cash - :price_per_share WHERE id = :user_id",
                   price_per_share=total_price, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price_per_share) VALUES(:user_id, :symbol, :shares, :price_per_share)",
                   user_id=session["user_id"],
                   symbol=request.form.get("symbol").upper(),
                   shares=shares,
                   price_per_share=price_per_share)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute(
        "SELECT symbol, shares, price_per_share, transaction_date FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

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

    if request.method == "POST":

        quote = lookup(request.form.get("symbol"))

        if quote != None:
            return render_template("quoted.html", quote=quote)

        else:
            return apology("No such symbol in stock!", 400)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":

        # Ensure username was provided
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was provided
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was provided
        elif not request.form.get("confirmation"):
            return apology("must retype your password", 400)

        # Ensure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords not match", 400)

        # Register new user and ensure there is no person with that username
        try:
            registered_user = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                                         username=request.form.get("username"),
                                         hash=generate_password_hash(request.form.get("password")))
        except:
            return apology("username already exists", 400)

        # Remember user
        session["user_id"] = registered_user

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("No such symbol in stock!", 400)

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("You can buy only positive integer number of shares", 400)

        # Check how many shares you have
        stock = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id AND symbol = :symbol GROUP BY symbol",
                           user_id=session["user_id"], symbol=request.form.get("symbol"))

        if shares > stock[0]["total_shares"]:
            return apology("You can't sell more than you have", 400)

        if shares < 1:
            return apology("can't sell less than 1 shares", 400)

        # User check
        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

        # Check if user can affort to make transaction
        cash_remaining = rows[0]["cash"]
        price_per_share = quote["price"]
        total_price = price_per_share * shares

        db.execute("UPDATE users SET cash = cash + :price_per_share WHERE id = :user_id",
                   price_per_share=total_price, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price_per_share) VALUES(:user_id, :symbol, :shares, :price_per_share)",
                   user_id=session["user_id"],
                   symbol=request.form.get("symbol").upper(),
                   shares=-shares,
                   price_per_share=price_per_share)

        return redirect("/")

    else:
        stocks = db.execute(
            "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares >= 1", user_id=session["user_id"])

        return render_template("sell.html", stocks=stocks)


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():

    if request.method == "POST":
        try:
            add = int(request.form.get("add"))
        except:
            return apology("amount must be a number of $", 400)

        db.execute("UPDATE users SET cash = cash + :add WHERE id = :user_id", user_id=session["user_id"], add=add)

        return redirect("/")

    else:
        return render_template("add.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
