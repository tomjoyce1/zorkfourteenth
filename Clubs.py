import sqlite3

#connecting to database
conn = sqlite3.connect('MiniEpic.db')
cursor = conn.cursor()


######################################################################################################################################################################################
#Club Management
######################################################################################################################################################################################

################################################################################################################################################################################################################
#Inserts
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


################################################################################################################################################################################################################
#Views
def user_view_clubs():
    cursor.execute("SELECT * FROM ClubsView")     
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    
    return result

def user_views_memberships(userID):
    cursor.execute("SELECT * FROM ViewClubMemberships WHERE UserID =?", (userID,))
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    
    return result



def coordinator_view_club_memberships(CoordinatorID):
    cursor.execute("SELECT * FROM ViewClubMemberships WHERE CoordinatorID = ?", (CoordinatorID,))
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    
    return result

def coordinator_view_club_pending_memberships(CoordinatorID):
    cursor.execute("SELECT * FROM ViewClubMemberships WHERE CoordinatorID = ? AND ApprovalStatus = 'pending'", (CoordinatorID,))
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    
    return result


def admin_view_clubs():
    cursor.execute("SELECT * FROM AdminClubsView")     
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    
    return result

def admin_view_clubs_pending():
    cursor.execute("SELECT * FROM AdminClubsView WHERE ValidityStatus = 'pending'")     
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    
    return result

def admin_view_club_memberships():
    cursor.execute("SELECT * FROM AdminClubMembershipView")
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    
    return result

################################################################################################################################################################################################################
#Update
def approve_club_membership(membershipID, CoordinatorID):
    cursor.execute("SELECT * FROM ClubMemberships WHERE MembershipID = ?", (membershipID,))
    membership_row = cursor.fetchone()

    if membership_row is not None:
        cursor.execute("SELECT * FROM ClubMemberships M, Clubs C WHERE M.MembershipID = ? AND M.ApprovalStatus = 'pending' AND (C.ClubID = (SELECT ClubID FROM Clubs WHERE CoordinatorID = ?) OR ? = 1)", (membershipID, CoordinatorID, CoordinatorID))
        membership_row = cursor.fetchone()

        if membership_row is not None or CoordinatorID == 1:
            cursor.execute("UPDATE ClubMemberships SET ApprovalStatus = 'approved' WHERE MembershipID = ?", (membershipID,))
            conn.commit()
            print("Club Membership Approved")
        else:
            print("Club Membership Denied")
    else:
        print("Membership not found")

def approve_club(UserID, ClubID):
    cursor.execute("SELECT Role FROM Users WHERE UserID = ?", (UserID,))
    row = cursor.fetchone()
    role = row[0]
    if role == 'ADMIN':
        cursor.execute("SELECT * FROM Clubs WHERE ClubID = ?", (ClubID,))
        club_row = cursor.fetchone()
        if club_row is not None:
            cursor.execute("UPDATE Clubs SET ValidityStatus = 'approved' WHERE ClubID = ?", (ClubID,))
            conn.commit()
            print("Club approved")

        else:
            print("Club not found")
    else:
        print("Access Denied")

def reject_club(UserID, ClubID):
    cursor.execute("SELECT Role FROM Users WHERE UserID = ?", (UserID,))
    row = cursor.fetchone()
    role = row[0]
    if role == 'ADMIN':
        cursor.execute("SELECT * FROM Clubs WHERE ClubID = ?", (ClubID,))
        club_row = cursor.fetchone()
        if club_row is not None:
            cursor.execute("UPDATE Clubs SET ValidityStatus = 'rejected' WHERE ClubID = ?", (ClubID,))
            conn.commit()
            print("Club approved")

        else:
            print("Club not found")
    else:
        print("Access Denied")







################################################################################################################################
    
#INSERTS
#Creating a new club
#ClubName = "Hockey" 
#CoordinatorID = 8 #Data stored from login page
#Description = "Fun on ice"
#creating_club(ClubName, CoordinatorID, Description)

#Registering for a new club     
#Userid = 9 #Data stored from login page
#ClubName = "Baking Club"
#club_registration(Userid, ClubName)



#VIEWS
#Displays all approved clubs
#for record in user_view_clubs():
#    print(record)     

#Displaying all memberships of a specific user
#UserID = 8
#for record in user_views_memberships(UserID):
#    print(record)
        
#Displaying all memberships of a specific club
#CoordinatorID = 2
#for record in coordinator_view_club_memberships(CoordinatorID):
#    print(record)

#Display all pending memberships of a specific club
#CoordinatorID = 2
#for record in coordinator_view_club_pending_memberships(CoordinatorID):
#    print(record)

#Displays all clubs including not approved
#for record in admin_view_clubs():
#    print(record)

#Displays only pending clubs
#for record in admin_view_clubs_pending():
#    print(record)
        
#Displays all memberships
#for record in admin_view_club_memberships():
#    print(record)



#UPDATES
#Approves club memberships
#MembershipID = 8
#CoordinatorID = 5
#approve_club_membership(MembershipID, CoordinatorID) 

#Approves clubs
#userID = 1 #Data from login
#clubID = 5
#approve_club(userID, clubID)

#Rejects clubs
#userID = 1 
#clubID = 6
#reject_club(userID, clubID) 





      



conn.close()#closes connection to database