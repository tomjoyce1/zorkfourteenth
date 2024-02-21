import sqlite3,Login

# Function to make a connection with the database, Dawid needs this to avoid the duplicate code
def connect_to_database():
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    return conn, cursor


# temp function to verify whether someone is a coordinator
def is_coordinator(user_id):
    conn, cursor = connect_to_database()
    cursor.execute("SELECT Role FROM Users WHERE UserID=?", (user_id,))
    role = cursor.fetchone()[0]
    conn.close()
    return role == "COORDINATOR"


#Verifying if event creator is a coordinator 
def verify_role(UserID):
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
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
    


# Function to create a new event in the database
def create_event(club_id, title, description, date_, time_, venue_id):
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO Events (Club_id, Title, Description, Date_, Time_, Venue_id) VALUES (?, ?, ?, ?, ?, ?)",
                   (club_id, title, description, date_, time_, venue_id))
    conn.commit()
   
    print("Event Created")
    conn.close()

# Function to register a user for a specific event
def register_for_event(event_id, user_id):
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO Event_Registration (Event_id, User_id) VALUES (?, ?)", (event_id, user_id))
    conn.commit()

#views             
    
def view_events(): 
    conn, cursor = connect_to_database()
    cursor.execute("SELECT * FROM View_Events")
    events = cursor.fetchall()
    result = [list(row) for row in events]
    return events
    conn.close()




# Function to retrieve details of events user is registered for
def fetch_event_registrations(userID): #CHANGE THIS TO A VIEW AND ONLY SELECT THE RELEVANT DATA. AVOID SHOWING THE ID OF THE VENUE OR EVENT, SHOW THE NAME OF IT BY JOINING TABLES OR USING A SUB QUERY
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM Event_Registration WHERE User_id = ?", (userID,))
    rows = cursor.fetchall()
    registered_events = [list(row) for row in rows]
    conn.close()
    return registered_events

# Function to retrieve events coordinated by a specific user
def coordinator_view_events(CoordinatorID): #AGAIN, USE THE VIEW FROM THE VIEW_EVENTS() FUNCTION AND JUST ADD A WHERE CONDITION TO SELECT THE RECORD WITH THE CORRECT COORDINATOR ID
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM Events WHERE Club_id IN (SELECT Club_id FROM Clubs WHERE CoordinatorID = ?)", (CoordinatorID,))
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    conn.close()
    return result

# Function to retrieve events coordinated by a specific user with pending approvals
def coordinator_view_events_pending(CoordinatorID):#USE THE VIEW FROM THE ABOVE FUNCTION AND JUST ADD "APPROVALSTATUS = 'PENDING'" TO THE WHERE CONDITION"
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM Events WHERE Club_id IN (SELECT Club_id FROM Clubs WHERE CoordinatorID = ?) AND ApprovalStatus = 'pending'", (CoordinatorID,))
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    conn.close()
    return result

# Function to retrieve all events for admin view
def admin_view_events(): #CREATE A VIEW FOR THIS OR ATLEAST CHANGE IT SO THAT RELEVANT DATA IS DISPLAYED (I.E. DONT SHOW THE ID OF THE VENUE OR EVENT, SHOW THE NAME OF IT)
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM Events")
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    conn.close()
    return result

# Function to retrieve events with pending approvals for admin view
def admin_view_events_pending():#TRY USING THE SAME VIEW FOR THE ADMIN AND COORDINATOR FUNCTIONS BUT DISTINGUISHED BETWEEN THEM BY USING THE WHERE CONDITION
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM Event_Registration WHERE ApprovalStatus = 'pending'")
    rows = cursor.fetchall()
    result = [list(row) for row in rows]
    return result

# Function to verify if a user is registered for a specific event
def verify_event_registration(user_id, EventID): 
    conn = sqlite3.connect('MiniEpic.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM Event_Registration WHERE User_id = ? AND Event_id = ?", (user_id, EventID))
    row = cursor.fetchone()
    conn.close()
    return row is not None

#updates     #######################################
    
    # Function to update details of an existing event
def update_event(event_id, title=None, description=None, date_=None, time_=None, venue_id=None): #DO WE NEED SUCH A COMPLEX FUNCTION?
    conn, cursor = connect_to_database()
    update_query = "UPDATE Events SET"
    if title:
        update_query += " Title=?,"
    if description:
        update_query += " Description=?,"
    if date_:
        update_query += " Date_=?,"
    if time_:
        update_query += " Time_=?,"
    if venue_id:
        update_query += " Venue_id=?,"
    # Remove the last comma
    update_query = update_query[:-1]
    update_query += " WHERE Event_id=?"
    update_values = []
    if title:
        update_values.append(title)
    if description:
        update_values.append(description)
    if date_:
        update_values.append(date_)
    if time_:
        update_values.append(time_)
    if venue_id:
        update_values.append(venue_id)
    update_values.append(event_id)
    cursor.execute(update_query, tuple(update_values))
    conn.commit()
    conn.close()

    # Function to cancel a user's registration for an event
def cancel_event_registration(registration_id):
    conn, cursor = connect_to_database()
    cursor.execute("DELETE FROM Event_Registration WHERE Registration_id=?", (registration_id,))
    conn.commit()
    conn.close()

# Function to approve a user's registration for an event
def approve_registration(registration_id):
    conn, cursor = connect_to_database()
    cursor.execute("UPDATE Event_Registration SET ApprovalStatus='approved' WHERE Registration_id=?", (registration_id,))
    conn.commit()
    conn.close()

# Function to reject a user's registration for an event
def reject_registration(registration_id):#ONCE A REGISRTRATION IS REJECTED, IT SHOULD BE DELETED SO USE THE CANCEL_EVENT_REGISTRATION FUNCTION INTO THIS
    conn, cursor = connect_to_database()
    cursor.execute("UPDATE Event_Registration SET ApprovalStatus='rejected' WHERE Registration_id=?", (registration_id,))
    conn.commit()
    conn.close()

# Function to add a new venue to the database
def create_venue(venue_name):
    conn, cursor = connect_to_database()
    cursor.execute("INSERT INTO Venues (Venue_name) VALUES (?)", (venue_name,))
    conn.commit()
    conn.close()

# Function to delete a venue from the database
def delete_venue(venue_id):
    conn, cursor = connect_to_database()
    cursor.execute("DELETE FROM Venues WHERE Venue_id=?", (venue_id,))
    conn.commit()
    conn.close()

# Function to update details of an existing venue
def update_venue(venue_id, venue_name):
    conn, cursor = connect_to_database()
    cursor.execute("UPDATE Venues SET Venue_name=? WHERE Venue_id=?", (venue_name, venue_id))
    conn.commit()
    conn.close()

#deletes ##############################################
# Function to delete an event from the database
def delete_event(event_id):
    conn, cursor = connect_to_database()
    cursor.execute("DELETE FROM Events WHERE Event_id=?", (event_id,))
    conn.commit()
    conn.close()

# Function to retrieve details of a specific event
def get_event_details(event_id): 
    conn, cursor = connect_to_database()
    cursor.execute("SELECT * FROM Events WHERE Event_id=?", (event_id,))
    event_details = cursor.fetchone()
    conn.close()
    return event_details

# Function to retrieve all events a user is registered for
def get_registered_events_for_user(user_id): #CHANGE THIS TO A VIEW AND DISPLAY ONLY RELEVANT DATA (E.G. SHOW VENUE NAME NOT ID)
    conn, cursor = connect_to_database()
    cursor.execute("SELECT * FROM Event_Registration WHERE User_id=?", (user_id,))
    registered_events = cursor.fetchall()
    conn.close()
    return registered_events

# Function to retrieve details of a specific venue
def get_venue_details(venue_id):
    conn, cursor = connect_to_database()
    cursor.execute("SELECT * FROM Venues WHERE Venue_id=?", (venue_id,))
    venue_details = cursor.fetchone()
    conn.close()
    return venue_details

# Function to retrieve all venues stored in the database
def get_all_venues():
    conn, cursor = connect_to_database()
    cursor.execute("SELECT * FROM Venues")
    all_venues = cursor.fetchall()
    conn.close()