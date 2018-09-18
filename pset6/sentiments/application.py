#importo flask y librerias relevantes
from flask import Flask, redirect, render_template, request, url_for
import os
#importo archivos de los que me cuelgo
import helpers
from analyzer import Analyzer
import sys
import helpers
import application
from termcolor import colored

#declaro flask
app = Flask(__name__)

#declaro en route "/" qué va a pasar si alguien entra al sitio
@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name,50)

    # TODO.
     # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)


    # import tweets using helpers.py (get_user_timeline) and then check if successful (public account with tweets)
    # alert user if successful or failed attempt
    
    if float(len(tweets)) < 50:
        print("User has less than 50 tweets made public")
        
    positive = 0; negative = 0; neutral = 0
    
    for j in tweets:
        # analyze tweet
        score = analyzer.analyze(j)
        if score > 0.0:
            positive = positive+1
        elif score < 0.0:
            negative = negative+1
        else:
            neutral = neutral+1

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)



"""IMPORTANTE REVISAR QUÉ FUNCIONES DE ESTA TAREA SON NUEVAS, COPIARLAS AL ACORDEON"""