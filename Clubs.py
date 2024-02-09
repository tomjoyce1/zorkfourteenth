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

def user_view_clubs():
    cursor.execute("SELECT * FROM ClubsView")     
    row = cursor.fetchall
    for row in cursor.fetchall():
        print(row)


def admin_view_clubs():
    cursor.execute("SELECT * FROM AdminClubsView")     
    row = cursor.fetchall
    for row in cursor.fetchall():
        print(row)

def coordinator_view_club_memberships(CoordinatorID):
    cursor.execute("SELECT M.MembershipID, U.Name || ' ' || U.Surname AS 'User Name', M.ApprovalStatus, M.CreatedTimestamp, M.UpdatedTimestamp FROM Clubs C, Users U, ClubMemberships M WHERE M.UserID = U.UserID AND M.ClubID = C.ClubID AND C.CoordinatorID = ? ORDER BY M.CreatedTimestamp DESC", (CoordinatorID,))
    rows = cursor.fetchall()
    for row in rows:
        print(row)

def coordinator_view_club_pending_memberships(CoordinatorID):
    cursor.execute("SELECT M.MembershipID, U.Name || ' ' || U.Surname AS 'User Name', M.ApprovalStatus, M.CreatedTimestamp, M.UpdatedTimestamp FROM Clubs C, Users U, ClubMemberships M WHERE M.UserID = U.UserID AND M.ClubID = C.ClubID AND C.CoordinatorID = ? AND M.ApprovalStatus = 'pending' ORDER BY M.CreatedTimestamp DESC", (CoordinatorID,))
    rows = cursor.fetchall()
    for row in rows:
        print(row)


def admin_view_club_memberships():
    cursor.execute("SELECT * FROM AdminClubMembershipView")
    rows = cursor.fetchall()
    for row in rows:
        print(row)



def approve_club_membership(membershipID, CoordinatorID):
    cursor.execute("SELECT * FROM ClubMemberships WHERE MembershipID = ?", (membershipID,))
    membership_row = cursor.fetchone()

    if membership_row is not None:
        cursor.execute("SELECT * FROM ClubMemberships M, Clubs C WHERE M.MembershipID = ? AND M.ApprovalStatus = 'pending' AND C.ClubID = (SELECT ClubID FROM Clubs WHERE CoordinatorID = ?)", (membershipID, CoordinatorID))
        membership_row = cursor.fetchone()

        if membership_row is not None or CoordinatorID == 1:
            cursor.execute("UPDATE ClubMemberships SET ApprovalStatus = 'approved' WHERE MembershipID = ?", (membershipID,))
            conn.commit()
            print("Club Membership Approved")
        else:
            print("Club Membership Denied")
    else:
        print("Membership not found")






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
        

#user_view_clubs() #displays all the approved clubs
        
admin_view_clubs()    
