import sqlite3

#connecting to database
conn = sqlite3.connect('MiniEpic.db')
cursor = conn.cursor()


######################################################################################################################################################################################
#Login page
######################################################################################################################################################################################

#initializing variables
username = ""
password = ""
option = ""
count = 0
name = ""

#function to verify user credentials
def validate_user(username, password):
    global name
    cursor.execute("SELECT UserID FROM login WHERE username=? AND password=?", (username, password)) #checks login table for provided username and password
    row = cursor.fetchone() #returns first row of database

    if row is not None:
        user_id = int(row[0]) #assigns user ID from databse to user_id variable
        cursor.execute("SELECT Name FROM Users WHERE UserID=?", (user_id,)) #checks Users table for UserID
        row = cursor.fetchone() #returns first row of database
        name = str(row).replace('(', '').replace(')', '').replace("'", '') #assigns name from database to name variable

        return True
    else:
        return False
    
def login():
    username = input("Enter your username: ") #prompts user to enter username
    password = input("Enter your password: ") #prompts user to enter password

    if validate_user(username, password): #checks if username and password are valid

        cursor.execute("SELECT UserID FROM login WHERE Username=? AND Password=?", (username, password)) #checks login table for provided username and password
        row = cursor.fetchone() #returns first row of database
        user_id = int(row[0]) #gets user ID from database
        cursor.execute("SELECT Name FROM Users WHERE UserID=?", (user_id,)) #checks Users table for UserID
        row = cursor.fetchone() #returns first row of database
        name = str(row).replace('(', '').replace(')', '').replace("'", '') #assigns name from database to name variable

        print("Login successful")
        print("Welcome to ClubHub", name)
    else:
        print("Invalid username or password")
        print("Please try again")
        count += 1 #keeps track of login attempts
        prompt_options() #returns to option menu



def signup():
    username = input("Enter your username: ") #prompts user to enter username
    password = input("Enter your password: ") #prompts user to enter password
    name = input("Enter your name: ") #prompts user to enter name
    surname = input("Enter your surname: ") #prompts user to enter surname
    email = input("Enter your email: ") #prompts user to enter email
    phone = input("Enter your phone number: ") #prompts user to enter phone number

    cursor.execute("INSERT INTO Users (Name, Surname, Email) VALUES (?,?,?)", (name, surname, email)) #creates new record in Users table with provided data
    conn.commit() #commits attributes to database

    cursor.execute("SELECT UserID FROM Users WHERE Name=? AND Surname=? AND Email=?", (name, surname, email)) #checks Users table for provided name, surname and email
    row = cursor.fetchone() #returns first row of database
    user_id = int(row[0]) #gets user ID from database

    cursor.execute("INSERT INTO login (username, password) VALUES (?,?)", (username, password)) #creates new record in login table with provided username and password
    cursor.execute("INSERT INTO PhoneNumber (UserID, PhoneNumber) VALUES (?,?)", (user_id, phone)) #creates new record in PhoneNumber table with user ID and provided phone number
    conn.commit() #commits attributes to database

    print("Signup successful")
    print("Please Login", name)
    login() #returns to login screen






def prompt_options(): 
    global count
    global username, password
    global name

    if count >= 3: #blocks if user has reached maximum number of login attempts
        print("Too many login attempts, please try again later")
    else:
        option = input("Login or signup?(L/S)") #prompts user to enter login or signup

        if option == "L": #login option
            login()

        elif option == "S": #signup option
          signup()
            
        else:
            print("Invalid option")
            print("Please try again")
            prompt_options() #returns to option menu




##########################################################################################################################
#                                                    START OF PROGRAM                                                    #
##########################################################################################################################
prompt_options() #function to start the program

conn.close()#closes connection to database

