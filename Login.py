import sqlite3
import Clubs

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
    user_id = int(row[0]) #gets user ID from database
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
<<<<<<< HEAD
    cursor.execute("INSERT INTO Phone_Number (UserID, Phone_Number) VALUES (?,?)", (user_id, phone)) #creates new record in Phone_Number table with user ID and provided phone number
=======
   
    #inserts new record into PhoneNumber table
    cursor.execute("INSERT INTO PhoneNumber (UserID, PhoneNumber) VALUES (?,?)", (user_id, phone)) #creates new record in PhoneNumber table with user ID and provided phone number
>>>>>>> 41aee321a9e08023186887e0abc5f6a608b53934
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



######################################################################################################################################################################
#Views
def admin_view_accounts():
    #connection to database
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM AdminAccountView")
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    return result

def admin_view_accounts_pending():
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM AdminAccountView WHERE ApprovalStatus = 'pending'")
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    return result

def admin_view_user(UserID):
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("SELECT U.UserID, U.Name || ' ' || U.Surname AS 'Name', L.Username, U.Email, P.Phone_Number, U.Role, U.ApprovalStatus, U.CreatedTimestamp, U.UpdatedTimestamp  FROM Users U, Login L, Phone_Number P WHERE U.UserID = L.UserID AND U.UserID = P.UserID AND U.UserID = ?", (UserID,))
    row = cursor.fetchone()
    if row:
        result = list(row)
        return result
    else:
        return None


######################################################################################################################################################################
#Updates
def approve_user(UserID):
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("UPDATE Users SET ApprovalStatus = 'approved' WHERE UserID =?", (UserID,))
    conn.commit()
    print("User approved")  

def deny_user(UserID):
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("UPDATE Users SET ApprovalStatus = 'rejected' WHERE UserID =?", (UserID,))
    delete_account(UserID)
    conn.commit()
    print("User denied")

def promote_user(UserID):
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    approve_user(UserID)
    cursor.execute("UPDATE Users SET Role = 'COORDINATOR' WHERE UserID =?", (UserID,))
    conn.commit()
    print("User promoted")   

def update_number(UserID, Phone_Number):
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("UPDATE Phone_Number SET Phone_Number = ? WHERE UserID =?", (Phone_Number, UserID,))
    conn.commit()
    print("Number updated")  

def update_password(UserID, oldPassword, newPassword):
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM Login WHERE UserID = ? AND Password = ?", (UserID, oldPassword,))
    row = cursor.fetchone()
    if row is not None: 
        cursor.execute("UPDATE Login SET Password = ? WHERE UserID =?", (newPassword, UserID,))
        conn.commit()
        print("Password updated") 
    else:
        print("Incorrect password")
        return "invalid"



######################################################################################################################################################################
#Deletes
    
def delete_account(UserID):
<<<<<<< HEAD
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("DELETE FROM Users WHERE UserID =?", (UserID,))
    cursor.execute("DELETE FROM Login WHERE UserID = ?", (UserID,))
    cursor.execute("DELETE FROM Phone_Number WHERE UserID =?", (UserID,))
    cursor.execute("DELETE FROM ClubMemberships WHERE UserID =?", (UserID,))
    cursor.execute("SELECT ClubID FROM Clubs WHERE CoordinatorID = ?", (UserID,))
    row = cursor.fetchone()
=======
    if UserID == 1:
        print("Cannot delete admin account")
        return "invalid"
    else: 
        conn = sqlite3.connect('MiniEpic.db')
        cursor = conn.cursor()
        cursor.execute("DELETE FROM Users WHERE UserID =?", (UserID,))
        cursor.execute("DELETE FROM Login WHERE UserID = ?", (UserID,))
        cursor.execute("DELETE FROM PhoneNumber WHERE UserID =?", (UserID,))
        cursor.execute("DELETE FROM ClubMemberships WHERE UserID =?", (UserID,))
        cursor.execute("SELECT ClubID FROM Clubs WHERE CoordinatorID = ?", (UserID,))
        row = cursor.fetchone()
>>>>>>> 41aee321a9e08023186887e0abc5f6a608b53934
    if row is not None:
        Clubs.delete_club(row[0])
    
    conn.commit()
    print("Account deleted")

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
#surname = input("Enter surname:")
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
#UserID = 2 
#print(admin_view_user(UserID))
    
    


#UPDATES
#Approves user account   
#UserID = 26
#approve_user(UserID)
    

#Rejects user account
#UserID = 28
#deny_user(UserID)

#Promotes user account to coordinator
#UserID = 26
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
    