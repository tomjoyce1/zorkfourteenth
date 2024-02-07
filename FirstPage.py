# all imports
from flask import Flask, redirect, url_for, render_template, request, session, flash
# importing real time to create permanent session for perios of time
from datetime import timedelta 
app = Flask(__name__)
app.secret_key = "hello"
app.permanent_session_lifetime = timedelta(days=5)
isCoordinator = False
isAdmin = False

@app.route("/")
@app.route("/home")
def home():
    return render_template("home.html", user=session.get("user", None), isCoordinator=isCoordinator, isAdmin=isAdmin)

@app.route("/login", methods=["POST", "GET"])
def login():
    global isCoordinator, isAdmin  # Declare as global variables
    if request.method == "POST":
        session.permanent = True
        user = request.form["nm"]
        email = request.form["em"]    
        session["user"] = user
        session["email"] = email
        if user == "coord":
            isCoordinator = True
        if user == "admin":
            isAdmin = True
        return redirect(url_for("home"))
    else:
        if "user" in session:
            return redirect(url_for("home"))

        return render_template("login.html", user=session.get("user", None), isCoordinator=isCoordinator, isAdmin=isAdmin)
    
@app.route("/register")
def register():
    return render_template("register.html")

@app.route("/logout")
def logout():
    if "user" in session:
        user = session["user"]
        flash(f"You have been logged out, {user}", "info")
    session.pop("user", None)
    session.pop("email", None)
    return redirect(url_for("login"))

if __name__ == "__main__":
    app.run(debug=True)
