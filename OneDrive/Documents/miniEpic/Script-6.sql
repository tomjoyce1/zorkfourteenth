
CREATE TABLE Users (
    UserID INTEGER PRIMARY KEY AUTOINCREMENT,
    Name TEXT NOT NULL,
    Surname TEXT NOT NULL,
    Email TEXT NOT NULL UNIQUE,
    Role TEXT DEFAULT 'STUDENT' NOT NULL CHECK(Role IN ('ADMIN', 'COORDINATOR', 'STUDENT')),
    ApprovalStatus TEXT DEFAULT 'pending' NOT NULL CHECK(ApprovalStatus IN ('approved', 'pending', 'rejected')),
    CreatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    UpdatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE TRIGGER IF NOT EXISTS users_insert_trigger
AFTER INSERT ON Users
FOR EACH ROW
BEGIN
    UPDATE Users SET CreatedTimestamp = NEW.CreatedTimestamp WHERE UserID = NEW.UserID;
END;

CREATE TRIGGER IF NOT EXISTS users_update_trigger
AFTER UPDATE ON Users
FOR EACH ROW
BEGIN
    UPDATE Users SET UpdatedTimestamp = CURRENT_TIMESTAMP WHERE UserID = NEW.UserID;
END;


-===========================

CREATE TABLE login(
UserID INTEGER PRIMARY KEY,
Username TEXT NOT NULL UNIQUE,
Password TEXT NOT NULL,
CreatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
UpdatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
FOREIGN KEY (UserID) REFERENCES Users(UserID)
)

CREATE TRIGGER IF NOT EXISTS login_insert_trigger
AFTER INSERT ON login
FOR EACH ROW
BEGIN
    UPDATE login SET CreatedTimestamp = NEW.CreatedTimestamp WHERE UserID = NEW.UserID;
END;

CREATE TRIGGER IF NOT EXISTS login_update_trigger
AFTER UPDATE ON Login
FOR EACH ROW
BEGIN
    UPDATE Login SET UpdatedTimestamp = CURRENT_TIMESTAMP WHERE UserID = NEW.UserID;
END;

-------------------------------

CREATE TABLE Clubs (
    ClubID INTEGER PRIMARY KEY AUTOINCREMENT,
    Name TEXT NOT NULL,
    CoordinatorID INTEGER,
    Description TEXT,
    ValidityStatus TEXT DEFAULT 'pending' NOT NULL CHECK(ValidityStatus IN ('approved', 'pending', 'rejected')),
    CreatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    UpdatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (CoordinatorID) REFERENCES Users(UserID)
);

CREATE TRIGGER IF NOT EXISTS clubs_insert_trigger
AFTER INSERT ON Clubs
FOR EACH ROW
BEGIN
    UPDATE Clubs SET CreatedTimestamp = NEW.CreatedTimestamp WHERE ClubID = NEW.ClubID;
END;

CREATE TRIGGER IF NOT EXISTS clubs_update_trigger
AFTER UPDATE ON Clubs
FOR EACH ROW
BEGIN
    UPDATE Clubs SET UpdatedTimestamp = CURRENT_TIMESTAMP WHERE ClubID = NEW.ClubID;
END;

--------------------

CREATE TABLE ClubMemberships (
    MembershipID INTEGER PRIMARY KEY autoincrement,
    UserID INTEGER,
    ClubID INTEGER,
    ApprovalStatus TEXT DEFAULT 'pending' NOT NULL CHECK(ApprovalStatus IN ('approved', 'pending', 'rejected')),
    CreatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    UpdatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (UserID) REFERENCES Users(UserID),
    FOREIGN KEY (ClubID) REFERENCES Clubs(ClubID)
);

CREATE TRIGGER IF NOT EXISTS clubmemberships_insert_trigger
AFTER INSERT ON ClubMemberships
FOR EACH ROW
BEGIN
    UPDATE ClubMemberships SET CreatedTimestamp = NEW.CreatedTimestamp WHERE MembershipID = NEW.MembershipID;
END;

CREATE TRIGGER IF NOT EXISTS clubmemberships_update_trigger
AFTER UPDATE ON ClubMemberships
FOR EACH ROW
BEGIN
    UPDATE ClubMemberships SET UpdatedTimestamp = CURRENT_TIMESTAMP WHERE MembershipID = NEW.MembershipID;
END;

----------------------------

CREATE TABLE PhoneNumber (
    UserID INTEGER PRIMARY KEY,
    PhoneNumber TEXT NOT NULL,
     CreatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    UpdatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);

CREATE TRIGGER IF NOT EXISTS phonenumber_insert_trigger
AFTER INSERT ON PhoneNumber
FOR EACH ROW
BEGIN
    UPDATE PhoneNumber SET CreatedTimestamp = NEW.CreatedTimestamp WHERE UserID = NEW.UserID;
END;

CREATE TRIGGER IF NOT EXISTS phonenumber_update_trigger
AFTER UPDATE ON PhoneNumber
FOR EACH ROW
BEGIN
    UPDATE PhoneNumber SET UpdatedTimestamp = CURRENT_TIMESTAMP WHERE UserID = NEW.UserID;
END;

----------------------

CREATE TRIGGER MaxClubsPerUser
BEFORE INSERT ON ClubMemberships
FOR EACH ROW
WHEN (
    SELECT COUNT(*)
    FROM ClubMemberships
    WHERE UserID = NEW.UserID
) >= 3
BEGIN
    SELECT RAISE(ABORT, 'Maximum number of clubs joined reached');
END;
--------------------------

/*Events///////////////////////////////////////////////////////////////*/
CREATE TABLE Events (
    Event_id INTEGER PRIMARY KEY AUTOINCREMENT,
    Club_id INTEGER,
    Title VARCHAR(20) NOT NULL,
    Description VARCHAR(30),
    Date_ DATE NOT NULL,
    Time_ TIME NOT NULL,
    Venue_id INTEGER NOT NULL,
    created_timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (Venue_id) REFERENCES Venues(Venue_id),
    FOREIGN KEY (Club_id) REFERENCES Clubs(ClubID)
);


CREATE TRIGGER IF NOT EXISTS insert_timestamp_trigger
AFTER INSERT ON Events
FOR EACH ROW
BEGIN
    UPDATE Events SET created_timestamp = IFNULL(NEW.created_timestamp, CURRENT_TIMESTAMP) WHERE Event_id = NEW.Event_id;
END;


CREATE TRIGGER IF NOT EXISTS update_timestamp_trigger
BEFORE UPDATE ON Events
FOR EACH ROW
BEGIN
    UPDATE Events SET updated_timestamp = CURRENT_TIMESTAMP WHERE Event_id = NEW.Event_id;
END;



/*Venues///////////////////////////////////////////////////////////////////*/

CREATE TABLE Venues(
Venue_id INTEGER PRIMARY KEY AUTOINCREMENT,
Venue_name VARCHAR(20),
created_timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
updated_timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
)


CREATE TRIGGER IF NOT EXISTS insert_timestamp_trigger
AFTER INSERT ON Venues
FOR EACH ROW
BEGIN
    UPDATE Venues SET created_timestamp = IFNULL(NEW.created_timestamp, CURRENT_TIMESTAMP) WHERE Venue_id = NEW.Venue_id;
END;

CREATE TRIGGER IF NOT EXISTS update_timestamp_trigger
BEFORE UPDATE ON Venues
FOR EACH ROW
BEGIN
    UPDATE Venues SET updated_timestamp = CURRENT_TIMESTAMP WHERE Venue_id = NEW.Venue_id;
END;


/*Event Registration/////////////////////////////////////////////////////////////////////*/

CREATE TABLE Event_Registration (
    Registration_id INTEGER PRIMARY KEY AUTOINCREMENT,
    Event_id INTEGER NOT NULL,
    User_id INTEGER NOT NULL,
    ApprovalStatus TEXT DEFAULT 'pending' NOT NULL CHECK(ApprovalStatus IN ('approved', 'pending', 'rejected')),
    created_timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (Event_id) REFERENCES Events(Event_id),
    FOREIGN KEY (User_id) REFERENCES Users(UserID)
);


CREATE TRIGGER IF NOT EXISTS insert_timestamp_trigger
AFTER INSERT ON Event_Registration
FOR EACH ROW
BEGIN
    UPDATE Event_Registration SET created_timestamp = IFNULL(NEW.created_timestamp, CURRENT_TIMESTAMP) WHERE Registration_id = NEW.Registration_id;
END;


CREATE TRIGGER IF NOT EXISTS update_timestamp_trigger
BEFORE UPDATE ON Event_Registration
FOR EACH ROW
BEGIN
    UPDATE Event_Registration SET updated_timestamp = CURRENT_TIMESTAMP WHERE Registration_id = NEW.Registration_id;
END;

------------------------------------------
/*Sample Queries*/
INSERT INTO Users (Name, Surname, Email) VALUES ('Dawid', 'Jakubowski', 'dawijak@gmail.com'), ('James', 'Bond', 'jb.mi6@gmail.com'), ('Mike', 'Ryan', 'mryan@gmail.com'), ('Jacob', 'Stanely', 'jacobstan@gmail.com'), ('Adam', 'Murphy', 'smurf@gmail.com')
UPDATE Users SET Role = 'COORDINATOR' WHERE UserID = 2
UPDATE Users SET ApprovalStatus = 'approved'

INSERT INTO login (UserID, Username, Password) VALUES (1, 'dawijak', 'ISE123'), (2, 'Bond', 'moneypenny'), (3, 'Michael', 'Portlaoise04'), (4, 'JacStan20', 'Biscuits29'), (5, 'Murpher35', 'icecream82')

INSERT INTO PhoneNumber (UserID, PhoneNumber) VALUES (1, '0872838474'), (2, '0864240572'), (3, '0892849291'), (4, '0892936471'), (5, '0862846208')

SELECT * FROM login
SELECT * FROM Users 
SELECT * FROM PhoneNumber
