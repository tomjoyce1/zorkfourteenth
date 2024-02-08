import sqlite3

#connecting to database
conn = sqlite3.connect('MiniEpic.db')
cursor = conn.cursor()


######################################################################################################################################################################################
#Club Management
######################################################################################################################################################################################

#Verifying if club creator is a coordinator
def verify_role(UserID):
    cursor.execute("SELECT Role, ApprovalStatus FROM Users WHERE UserID=?", (UserID,)) #checks role of user from Users table
    row = cursor.fetchone() #returns first row of database
    role = row[0]
    approval_status = row[1]


    if (role == "COORDINATOR" or role == "ADMIN") and approval_status == "approved":
        print("Role Approved")
        return True
    else:
        print("Role Denied")
        return False
    
def verify_clubs_coordinated(UserID):
    cursor.execute("SELECT COUNT(*) FROM Clubs WHERE CoordinatorID=?", (UserID,))
    row = cursor.fetchone()
    clubs_coordinated = row[0]
    return (clubs_coordinated < 1)
    

#Creating a new club
def creating_club(Name, CoordinatorID, Description): 
    if verify_role(CoordinatorID) and verify_clubs_coordinated(CoordinatorID): 
        cursor.execute("INSERT INTO Clubs (Name, CoordinatorID, Description) VALUES (?,?,?)", (Name, CoordinatorID, Description))
        conn.commit()
        print("Club Created")
    else:
        print("Club Creation Denied")


def verify_clubs_joined(UserID):
    cursor.execute("SELECT COUNT(*) FROM ClubMemberships WHERE UserID=?", (UserID,))
    row = cursor.fetchone()
    clubs_joined = row[0]
    return clubs_joined

def club_registration(UserID, ClubName):
    if verify_clubs_joined(UserID) < 3:
        cursor.execute("SELECT ClubID FROM Clubs WHERE Name=?", (ClubName,))
        row = cursor.fetchone()

        if row is None:
            print("Club does not exist")
        else:
            clubID = row[0]
            cursor.execute("INSERT INTO ClubMemberships (UserID, ClubID) VALUES (?,?)", (UserID, clubID))
            conn.commit()
            print("Club Registration Successful")
    else:
        print("Club Registration Denied")
        print("Too many clubs joined")






################################################################################################################################
    


#Userid = 5  #Data stored from login page
#verify_clubs_joined(Userid)
        
#user = 6     
#print(verify_clubs_coordinated(user))
    

#ClubName = "Baking Club" #
#CoordinatorID = 5 #Data stored from login page
#Description = "Bake cakes and deserts"
#creating_club(ClubName, CoordinatorID, Description)


#Userid = 9 #Data stored from login page
#ClubName = "Baking Club"
#club_registration(Userid, ClubName)
        

