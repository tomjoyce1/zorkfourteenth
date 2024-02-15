import sqlite3, os,Login,Clubs

from flask import Flask, redirect, url_for, render_template, request, session, flash, g

# importing real time to create permanent session for perios of time
from datetime import timedelta
app = Flask(__name__)

current_dir = os.path.dirname(os.path.abspath(__file__))
miniwebsite_dir = os.path.join(current_dir, '..')
database_path = os.path.join(miniwebsite_dir, 'MiniWebsite', 'MiniEpic.db')
app.config['DATABASE'] = database_path

app.secret_key = "hello"
app.permanent_session_lifetime = timedelta(days=5)

@app.route("/")
@app.route("/home")
def home():

    return render_template("home.html")

@app.route("/login", methods=["POST", "GET"])
def login():
    error_message = None
    isCoord = False 
    isAdmin = False
    if request.method == "POST":
        session.permanent = True
        username = request.form["username"]
        password = request.form["password"]
        session["user"] = username 

        if Login.validate_user(username, password):
            isCoord, isAdmin = Login.login(username, password)
            return redirect(url_for("home", isCoord=isCoord, isAdmin=isAdmin))
        else:
            error_message = "Invalid username or password. Please try again."
            session.pop("user", None)
            session.pop("email", None)
    else:
        if "user" in session:
            return redirect(url_for("home", isCoord=isCoord, isAdmin=isAdmin))

    return render_template("login.html", isCoord=isCoord, isAdmin=isAdmin, error_message=error_message)


@app.route("/register", methods=["POST", "GET"])
def register():
    error_message2 = None
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        name = request.form["name"]
        surname = request.form["surname"]
        email = request.form["email"]
        phone = request.form["phone"]

        if Login.validate_reg(email):
            Login.create_account(username,password,name,surname,email,phone)
            return redirect(url_for("home"))
        else:
             error_message2 = "Email Taken"
    else:
        if "user" in session:
            return redirect(url_for("home")) 
            
    return render_template("register.html",error_message2=error_message2)

@app.route("/logout")
def logout():
    if "user" in session:
        user = session["user"]
        flash(f"You have been logged out, {user}", "info")
    session.pop("user", None)
    session.pop("email", None)
    return redirect(url_for("login"))

@app.route("/clubs")
def clubs():
    clubList = []
    for item in Clubs.user_view_clubs():
        clubList.append(item)
    return render_template("clubs.html",clubList=clubList)

#allows me to go through clubList
@app.template_filter('enumerate')
def jinja2_enumerate(iterable):
    return enumerate(iterable)

if __name__ == "__main__":
    app.run(debug=True)