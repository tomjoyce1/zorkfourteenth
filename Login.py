import sqlite3
import Clubs
import re

conn = sqlite3.connect('MiniEpic.db')
cursor = conn.cursor()
######################################################################################################################################################################################
#Login page
######################################################################################################################################################################################

######################################################################################################################################################################################
#Inserts


#function to verify user credentials
def validate_user(username, password):
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    #checks if record with username and password exists in database
    cursor.execute("SELECT * FROM Login WHERE username=? AND password=?", (username, password)) #checks login table for provided username and password
    row = cursor.fetchone() #returns first row of database
    #if exists returns true
    if row is not None:
        return True
    else:
        #if not returns false
        return False
    
def validate_reg(email):
     #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    #checks if record with email exists in database
    cursor.execute("SELECT Email FROM Users WHERE Email=?", (email,)) #checks User table for email
    row = cursor.fetchone() #returns first row of database

    if row is None:
        return True
    else:
        return False
    
def login(username, password):
    roleCheck = 0
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()

    #gets user ID from database
    cursor.execute("SELECT UserID FROM Login WHERE Username=? AND Password=?", (username, password)) #checks login table for provided username and password
    row = cursor.fetchone() #returns first row of database
    user_id = row[0] #gets user ID from database
    cursor.execute("SELECT Role FROM Users WHERE UserID=?", (user_id,)) #checks Users table for UserID
    row = cursor.fetchone() #returns first row of database
    role = row[0] #assigns role from database to name variable
    print("Role:", role)
    if role == "COORDINATOR":
        roleCheck = 1
    if role == "ADMIN":
        roleCheck = 2
    if role == "STUDENT":
        roleCheck = 3

    return roleCheck

def create_account(username, password, name, surname, email, phone):
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    #inserts new record into users table
    cursor.execute("INSERT INTO Users (Name, Surname, Email) VALUES (?,?,?)", (name, surname, email)) #creates new record in Users table with provided data
    conn.commit() #commits attributes to database

    #gets auto generated user ID from Users table
    cursor.execute("SELECT UserID FROM Users WHERE Name=? AND Surname=? AND Email=?", (name, surname, email)) #checks Users table for provided name, surname and email
    row = cursor.fetchone() #returns first row of database
    user_id = int(row[0]) #gets user ID from database

    #inserts new record into login table
    cursor.execute("INSERT INTO Login (UserID, username, password) VALUES (?,?,?)", (user_id, username, password)) #creates new record in login table with provided username and password
   
    #inserts new record into PhoneNumber table
    cursor.execute("INSERT INTO PhoneNumber (UserID, PhoneNumber) VALUES (?,?)", (user_id, phone)) #creates new record in PhoneNumber table with user ID and provided phone number
    conn.commit() #commits attributes to database
    print("Registration Succesful")


  

def verify_role(user_id):
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    #gets role of user from Users table
    cursor.execute("SELECT Role, ApprovalStatus FROM Users WHERE UserID=?", (user_id)) #checks role of user from Users table
    row = cursor.fetchone() #returns first row of database
    role = row[0]
    approval_status = row[1]

    #checks what role is and returns it
    if approval_status != "approved":
        print("You're approval status is", approval_status)
   
   
    if role == "ADMIN":
        return "ADMIN"

    elif role == "COORDINATOR":
        return "COORDINATOR"
    
    elif role == "STUDENT":
        return "STUDENT"
    
    else:
        print("ERROR: Invalid role")


def verify_username(username):
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()

    cursor.execute("SELECT * FROM Login WHERE Username=?", (username,)) #checks if username exists in Login table
    row = cursor.fetchone() #returns first row of database
    if row is not None:
        return False
    else:
        return True
    

def verify_phone(phone):
    return len(phone) == 10

def verify_approval_status(user_id):
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    #gets approval status of user from Users table
    cursor.execute("SELECT * FROM Users WHERE UserID=? AND WHERE ApprovalStatus='approved'", (user_id,)) #checks approval status of user from Users table
    row = cursor.fetchone() #returns first row of database
    if row is not None:
        return True
    else:
        return False
    

def is_valid_email(email):
    pattern = r'^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$'
    return bool(re.match(pattern, email))





######################################################################################################################################################################
#Views
def admin_view_accounts():
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()

    #gets all records from AdminAccountView
    cursor.execute("SELECT * FROM AdminAccountView")
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    return result

def admin_view_accounts_pending():
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    #gets all records from AdminAccountView with pending approval status
    cursor.execute("SELECT * FROM AdminAccountView WHERE ApprovalStatus = 'pending'")
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    return result

def get_user_id(Username):
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("SELECT UserID FROM Login WHERE Username=?",(Username,))
    row = cursor.fetchone ()
    user_id = row[0]
    return user_id
    

def admin_view_user(UserID):
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    #gets records of specific user
    cursor.execute("SELECT U.UserID, U.Name || ' ' || U.Surname AS 'Name', L.Username, U.Email, P.PhoneNumber, U.Role, U.ApprovalStatus, U.CreatedTimestamp FROM Users U, Login L, PhoneNumber P WHERE U.UserID = L.UserID AND U.UserID = P.UserID AND U.UserID = ?", (UserID,))
    row = cursor.fetchone()
    if row:
        result = list(row)
        return result
    else:
        return None

def view_coordinators():
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    #gets all records from Users table with role of coordinator
    cursor.execute("SELECT * FROM ViewClubCoordinators")
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    return result


######################################################################################################################################################################
#Updates
#approves user account
def approve_user(UserID):
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    #updates approval status of user to approved
    cursor.execute("UPDATE Users SET ApprovalStatus = 'approved' WHERE UserID =?", (UserID,))
    conn.commit()
    print("User approved")  

def deny_user(UserID):
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    #updates approval status of user to rejected
    cursor.execute("UPDATE Users SET ApprovalStatus = 'rejected' WHERE UserID =?", (UserID,))
    delete_account(UserID)
    conn.commit()
    print("User denied")

def promote_user(UserID):
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()

    #approves user account
    approve_user(UserID)

    #updates role of user to coordinator
    cursor.execute("UPDATE Users SET Role = 'COORDINATOR' WHERE UserID =?", (UserID,))
    conn.commit()
    print("User promoted")   

def update_number(UserID, Phone_Number):
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()

    #updates phone number of user
    cursor.execute("UPDATE PhoneNumber SET PhoneNumber = ? WHERE UserID =?", (Phone_Number, UserID,))
    conn.commit()
    print("Number updated")  

def update_password(UserID, oldPassword, newPassword):
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()

    #verifies if old password is correct
    cursor.execute("SELECT * FROM Login WHERE UserID = ? AND Password = ?", (UserID, oldPassword,))
    row = cursor.fetchone()
    if row is not None: 
        #updates password of user
        cursor.execute("UPDATE Login SET Password = ? WHERE UserID =?", (newPassword, UserID,))
        conn.commit()
        return "valid" 
    else:
        return "invalid"



######################################################################################################################################################################
#Deletes
    
def delete_account(UserID):
    #prevents admin account from being deleted

    if UserID == 1:
        print("Cannot delete admin account")
        return "invalid"
    else: 
        #connection to database
        conn = sqlite3.connect('MiniEpic.db')
        cursor = conn.cursor()

        #deletes all records of user from database
        cursor.execute("DELETE FROM Users WHERE UserID =?", (UserID,)) #deletes user from Users table
        cursor.execute("DELETE FROM Login WHERE UserID = ?", (UserID,)) #deletes user from Login table
        cursor.execute("DELETE FROM PhoneNumber WHERE UserID =?", (UserID,)) #deletes user from PhoneNumber table
        cursor.execute("DELETE FROM ClubMemberships WHERE UserID =?", (UserID,)) #deletes user from ClubMemberships table
        cursor.execute("SELECT ClubID FROM Clubs WHERE CoordinatorID = ?", (UserID,)) #checks if user is coordinator of any clubs
        row = cursor.fetchone()
    if row is not None:
        Clubs.delete_club(row[0]) #deletes club if user is coordinator
    
    conn.commit()
    print("Account deleted")

def view_passwords(Username):
        conn = sqlite3.connect('MiniEpic.db')
        cursor = conn.cursor()

        cursor.execute("Select Password FROM Login WHERE Username =?", (Username,))
        row = cursor.fetchone()
        print(row)

##########################################################################################################################
#                                                    START OF PROGRAM                                                    #
##########################################################################################################################
#INSERTS
#Login
#username = input("Enter username:")
#password = input("Enter password:")
#login(username, password)
    
#Signup
#username = input("Enter username:")
#password = input("Enter password:")
#name = input("Enter name:")
#urname = input("Enter surname:")
#email = input("Enter email:")
#phone = input("Enter phone:")
#create_account(username, password, name, surname, email, phone)



#VIEW
#Displays all user accounts
#for record in admin_view_accounts():
# print (record)

#Displays all pending accounts    
#for record in admin_view_accounts_pending():
#    print (record)

#Displays the account of a specific user
#UserID = 7 
#print(admin_view_user(UserID))

#UserID = 7 
#print(display_user_details(UserID))
        
#Displays all coordinators
#for record in view_coordinators():
#   print (record)
    
    


#UPDATES
#Approves user account   
#UserID = 32
#approve_user(UserID)
    

#Rejects user account
#UserID = 28
#deny_user(UserID)

#Promotes user account to coordinator
#UserID = 31
#promote_user(UserID)
    
#Updates phone number
#UserID = 25
#phone = "0874635162"
#update_number(UserID, phone)

#Updates password
#UserID = 25
#oldPassword = "lowerpark"
#newPassword = "upperpark"
#update_password(UserID, oldPassword, newPassword)
    



#DELETES
#Deletes account
#UserID = 25
#delete_account(UserID)
    