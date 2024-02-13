from flask import Flask, redirect, url_for, render_template, request, session, flash
# importing real time to create permanent session for perios of time
from datetime import timedelta 
app = Flask(__name__)
app.secret_key = "hello"
app.permanent_session_lifetime = timedelta(days=5)
isAdmin = False
isCoordinator = False

@app.route("/")
@app.route("/home")
def home():
    return render_template("home.html")

@app.route("/login", methods=["POST", "GET"])
def login():
    global isCoordinator, isAdmin  # Declare as global variables
    if request.method == "POST":
        session.permanent = True
        user = request.form["username"]
        session["user"] = user
        if user == "coord":
            isCoordinator = True
        if user == "admin":
            isAdmin = True
        return redirect(url_for("home"))
    else:
        if "user" in session:
            return redirect(url_for("home"))

        return render_template("login.html")
    
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

@app.route("/clubs")
def clubs():
    return render_template("clubs.html",clubList=clubList)

@app.route("/testing")
def test():
    return render_template("test.html",var=clubList)

if __name__ == "__main__":
    app.run(debug=True)
