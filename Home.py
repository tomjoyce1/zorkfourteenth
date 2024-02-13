import sqlite3, os

from flask import Flask, redirect, url_for, render_template, jsonify, request, session, flash, g
# importing real time to create permanent session for perios of time
from datetime import timedelta
app = Flask(__name__)
current_dir = os.path.dirname(os.path.abspath(__file__))

# Construct the path relative to the MiniWebsite directory
database_path = os.path.join(current_dir, 'MiniEpic.db')

# Set the database path in your app config
app.config['DATABASE'] = database_path

app.secret_key = "hello"
app.permanent_session_lifetime = timedelta(days=5)
validLogin = False

def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(app.config['DATABASE'])
    return db

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()

@app.route("/")
@app.route("/home")
def home():
    return render_template("home.html")

@app.route("/login", methods=["POST", "GET"])
def login():
    if request.method == "POST":
        session.permanent = True
        username = request.form["username"]
        password = request.form["password"]

        conn = get_db()  # Open a database connection
        cursor = conn.cursor()
        cursor.execute("SELECT UserID FROM Login WHERE username=? AND password=?", (username, password)) #checks login table for provided username and password
        row = cursor.fetchone() #returns first row of database

        if row is not None:
            validLogin = True
        if validLogin:
            cursor.execute("SELECT UserID FROM Login WHERE Username=? AND Pass word=?", (username, password)) #checks login table for provided username and password
            row = cursor.fetchone() #returns first row of database
            user_id = int(row[0]) #gets user ID from database
            cursor.execute("SELECT Name FROM Users WHERE UserID=?", (user_id,)) #checks Users table for UserID
            row = cursor.fetchone() #returns first row of database
            username = row[0] #assigns name from database to name variable

        return redirect(url_for("home"))
    else:
        if "user" in session:
            return redirect(url_for("home"))

        return render_template("login.html")
    
@app.route("/register", methods=["POST", "GET"])
def register():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        name = request.form["name"]
        surname = request.form["surname"]
        email = request.form["email"]
        phone = request.form["phone"]

        conn = get_db()  # Open a database connection
        cursor = conn.cursor()
        
        cursor.execute("SELECT * FROM Users WHERE Email = ?", (email,))
        row = cursor.fetchone()
        if row is not None:
            print("Email already exists")
            conn.close()  # Close the connection
            return "Error"
        
        cursor.execute("INSERT INTO Users (Name, Surname, Email) VALUES (?,?,?)", (name, surname, email)) #creates new record in Users table with provided data
        conn.commit() #commits attributes to database

        cursor.execute("SELECT UserID FROM Users WHERE Name=? AND Surname=? AND Email=?", (name, surname, email)) #checks Users table for provided name, surname and email
        row = cursor.fetchone() #returns first row of database
        user_id = int(row[0]) #gets user ID from database

        cursor.execute("INSERT INTO Login (UserID, username, password) VALUES (?,?,?)", (user_id, username, password)) #creates new record in login table with provided username and password
        cursor.execute("INSERT INTO PhoneNumber (UserID, PhoneNumber) VALUES (?,?)", (user_id, phone)) #creates new record in PhoneNumber table with user ID and provided phone number
        conn.commit() #commits attributes to database
        conn.close()

        return redirect(url_for("home"))
    else:
        if "user" in session:
            return redirect(url_for("home")) 
            
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
    conn = get_db()
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM ClubsView")
    rows = cursor.fetchall()
    clubList = [list(row) for row in rows]
    conn.close()
    return render_template("clubs.html",clubList=clubList)

@app.template_filter('enumerate')
def jinja2_enumerate(iterable):
    return enumerate(iterable)

if __name__ == "__main__":
    app.run(debug=True)