from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request

app = Flask(__name__)
app.secret_key = "abcdefghijk"

db = SQL("sqlite:///oscar.db")



@app.route("/")
def index():
    flash("Welcome to The Oscars Page! Choose year and find out who gets the Oscars!")
    return render_template("index.html")



@app.route("/list", methods=["POST", "GET"])
def greeter():

    flash ("In the year " + str(request.form['year']) + ", Oscars went to...")

    winneronly = request.form.get('winner')

    if winneronly:
        UserYear = request.form['year']
        movies = db.execute(
        "SELECT category, winner, entity FROM oscars WHERE year = ? AND winner = 'Winner' ", (UserYear,) )
        return render_template("index.html", movies=movies)

    else:
        UserYear = request.form['year']
        movies = db.execute(
        "SELECT category, winner, entity FROM oscars WHERE year = ? ", (UserYear,) )
        return render_template("index.html", movies=movies)