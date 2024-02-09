from flask import Flask, render_template, url_for, request, jsonify

# Create Flask application instance
app = Flask(__name__)

@app.route('/')
def homepage():
    return render_template('homepage.html')

@app.route('/login')
def login():
    return render_template('login.html')

@app.route('/clubs')
def clubs():
    return render_template('clubs.html')

@app.route('/memberships')
def memberships():
    return render_template('memberships.html')

@app.route('/about')
def about():
    return render_template('about.html')


if __name__ == '__main__':
    app.run(debug=True)

