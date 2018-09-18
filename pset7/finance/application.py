from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    # query database for holdings
    id = session["user_id"]
    holdings_q = db.execute("SELECT * FROM balance WHERE user_id = :id", id=id)
    cash_q = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
    cash_no = cash_q[0]
    cash_b = cash_no["cash"]
    cash_int = int(cash_b)
    value_total = cash_int
    i=0
    ind =[]
    for holding in holdings_q:
        try:
            chec = lookup(holding["symbol"])
            price = int(chec["price"])
            ind.append({
                "balance_id": holding["balance_id"],
                "name": holding["symbol"],
                "price": price,
                "holdings": holding["holdings"],
                "value": price*int(holding["holdings"])
            })
            value_total= value_total + price*int(holding["holdings"])
        except: 
             ind.append({
                "balance_id": holding["balance_id"],
                "name": holding["symbol"],
                "price": "N/A",
                "holdings": holding["holdings"],
                "value": "N/A"})
    return render_template("index.html", ind = ind, cash_int = cash_int, value_total = value_total)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    
        # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        
        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("Please provide a symbol")
        # ensure shares was submitted
        if not request.form.get("shares"):
            return apology("Please provide a number of shares")
        # ensure shares is an int
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Please provide a number of shares")
        if not shares>0:
            return apology("Please provide a positive number of shares")
       
        # extract quote, check if symbol is valid
        result = lookup(request.form.get("symbol"))
        # alert if symbol is incorrect
        if not result:
            return apology("invalid symbol")
        name = result["name"]
        price = result["price"]
        symbol = result["symbol"]
        price_int = int(price)
        cost = price_int*shares
        id = session["user_id"]
        # check if user has money
        cash_q = db.execute("SELECT cash FROM users WHERE id = :id", id = id)
        cash_d = cash_q[0]
        cash = cash_d['cash']

        if cash < cost:
            return apology("not enough cash")
        
        #register the transaction in transactions
        db.execute("INSERT INTO 'transactions' ('user_id','symbol','price','stock_ammount','spent') VALUES (:id,:symbol,:price_int,:shares,:cost)"
        , id=id,symbol=symbol,price_int=price_int,shares=shares,cost=cost)
        
         #update user's cash
        new_cash_balance = cash-cost
        db.execute("UPDATE users SET cash = :new_cash_balance WHERE id = :id"
        , new_cash_balance=new_cash_balance, id=id)
        
        # query database for balance
        holdings_q = db.execute("SELECT balance_id, holdings FROM balance WHERE user_id = :id and symbol = :symbol", id =id, symbol=symbol)
        
        
        # check if balance exists
        if len(holdings_q) == 0:
            db.execute("INSERT INTO 'balance' ('user_id','symbol','holdings') VALUES (:id,:symbol,:holdings)"
            ,id=id, symbol=symbol, holdings=shares)
        
        # If no balance exists
        else:
            holdings_d = holdings_q[0]
            holdings = holdings_d['holdings']
            balance_id = holdings_d['balance_id']
            new_balance = holdings+shares
            db.execute("UPDATE balance SET holdings = :new_balance WHERE balance_id = :balance_id"
            ,new_balance=new_balance, balance_id=balance_id)
            # UPDATE "balance" SET "balance_id"='1', "user_id"='7', "symbol"='GOOGL', "holdings"='10' WHERE "rowid" = 1
            
        
            
        
        #to do: register transaction, update cash
        
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")
    

@app.route("/history")
@login_required
def history():
    #--------------------------------
      # query database for transactions
    id = session["user_id"]
    trans = db.execute("SELECT * FROM transactions WHERE user_id = :id", id=id)
    print("trans son {}".format(trans))
    return render_template("history.html", trans = trans)
    #-------------------------------

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")
        
        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
        username = request.form.get("username")
        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))
        
        
    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        
        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("Please provide a symbol")
            
        # extract quote
        result = lookup(request.form.get("symbol"))
        # alert if symbol is incorrect
        if not result:
            return apology("invalid symbol")
        name = result["name"]
        price = result["price"]
        return render_template("quoted.html",price=price, name=name)

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    """ copiando de login --------------------------"""
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("Please provide a username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # check if username exists, ask for login
        if len(rows) == 1:
            return apology("Username has alredy been taken")
        # Register user
        else:
            db.execute("INSERT INTO 'users' ('username','hash') VALUES (:username,:password)"
            ,username=request.form.get("username"), password=pwd_context.hash(request.form.get("password")))

        # redirect user to home page
            return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")
        
        
        

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    #-------------------
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        
        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("Please provide a symbol")
        # ensure shares was submitted
        if not request.form.get("shares"):
            return apology("Please provide a number of shares to sell")
        # ensure shares is an int
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Please provide a number of shares")
        if not shares>0:
            return apology("Please provide a positive number of shares")
       
        # extract quote, check if symbol is valid
        result = lookup(request.form.get("symbol"))
        # alert if symbol is incorrect
        if not result:
            return apology("Can't find symbol in the market")
        name = result["name"]
        price = result["price"]
        symbol = result["symbol"]
        price_int = int(price)
        value = price_int*shares
        id = session["user_id"]
        # check if user has shares
        holdings_q = db.execute("SELECT * FROM balance WHERE user_id = :id and symbol = :symbol", id = id, symbol = symbol)
         # check if balance exists
        if len(holdings_q) == 0:
            return apology("no shares found in holdings")
        holdings_t = holdings_q[0]
        holdings = holdings_t['holdings']
        balance_id = holdings_t['balance_id']
               

        if holdings < shares:
            return apology("not enough shares")
        
        #register the transaction in transactions
        db.execute("INSERT INTO 'transactions' ('user_id','symbol','price','stock_ammount','spent') VALUES (:id,:symbol,:price_int,:shares,:cost)"
        , id=id,symbol=symbol,price_int=price_int,shares=-shares,cost=-value)
        
         #update user's cash
        cash_q = db.execute("SELECT cash FROM users WHERE id = :id", id = id)
        cash_d = cash_q[0]
        cash = cash_d['cash']
        new_cash_balance = cash+value
        db.execute("UPDATE users SET cash = :new_cash_balance WHERE id = :id"
        , new_cash_balance=new_cash_balance, id=id)
        

        # update holdings
        new_balance = holdings-shares
        db.execute("UPDATE balance SET holdings = :new_balance WHERE balance_id = :balance_id"
        ,new_balance=new_balance, balance_id=balance_id)
        # UPDATE "balance" SET "balance_id"='1', "user_id"='7', "symbol"='GOOGL', "holdings"='10' WHERE "rowid" = 1
        
        #to do: register transaction, update cash
        
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html")

@app.route("/funds", methods=["GET", "POST"])
@login_required
def funds():
    """Buy shares of stock."""
    id = session["user_id"]
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        
        # ensure cash was submitted
        if not request.form.get("cash"):
            return apology("Please provide cash ammount")
        try:
            cash = int(request.form.get("cash"))
        except:
            return apology("Please provide a number of shares")
        if not cash>0:
            return apology("Please provide a positive number of shares")
    
        #check existing cash
        cash_q = db.execute("SELECT cash FROM users WHERE id = :id", id = id)
        cash_d = cash_q[0]
        ex_cash = cash_d['cash']
        
         #update user's cash
        new_cash_balance = cash+ex_cash
        print("new cash =",new_cash_balance)
        db.execute("UPDATE users SET cash = :new_cash_balance  WHERE id = :id"
        , new_cash_balance=new_cash_balance, id=id)
       
        
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("funds.html")    
    
    