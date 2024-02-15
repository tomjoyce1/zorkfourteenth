import sqlite3

#connecting to database
conn = sqlite3.connect('MiniEpic.db')
cursor = conn.cursor()


######################################################################################################################################################################################
#Events
######################################################################################################################################################################################
#Creating events

#Registering for events

#Adding new venues


#################################################

# Function to create events
def create_event(club_id, title, description, date, time, venue_id):
    conn = connect_to_db()
    cursor = conn.cursor()
    cursor.execute("INSERT INTO Events (Club_id, Title, Description, Date_, Time_, Venue_id) VALUES (?, ?, ?, ?, ?, ?)", (club_id, title, description, date, time, venue_id))
    conn.commit()
    conn.close()

# Function to register for events
def register_for_event(event_id, user_id):
    conn = connect_to_db()
    cursor = conn.cursor()
    cursor.execute("INSERT INTO Event_Registration (Event_id, User_id) VALUES (?, ?)", (event_id, user_id))
    conn.commit()
    conn.close()

# Function to add new venues
def add_venue(venue_name):
    conn = connect_to_db()
    cursor = conn.cursor()
    cursor.execute("INSERT INTO Venues (Venue_name) VALUES (?)", (venue_name,))
    conn.commit()
    conn.close()

# Example usage of the functions
create_event(1, 'Archery Tryouts', 'Opportunity to try archery', '2024-03-01', '14:00', 8)
register_for_event(1, 8)
add_venue('New Venue')