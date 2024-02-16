
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

CREATE TABLE Login(
UserID INTEGER PRIMARY KEY,
Username TEXT NOT NULL UNIQUE,
Password TEXT NOT NULL,
CreatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
UpdatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
FOREIGN KEY (UserID) REFERENCES Users(UserID)
)

CREATE TRIGGER IF NOT EXISTS login_insert_trigger
AFTER INSERT ON Login
FOR EACH ROW
BEGIN
    UPDATE Login SET CreatedTimestamp = NEW.CreatedTimestamp WHERE UserID = NEW.UserID;
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
    CoordinatorID INTEGER NOT NULL UNIQUE,
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
    MembershipID INTEGER PRIMARY KEY AUTOINCREMENT,
    UserID INTEGER NOT NULL,
    ClubID INTEGER NOT NULL,
    ApprovalStatus TEXT DEFAULT 'pending' NOT NULL CHECK(ApprovalStatus IN ('approved', 'pending', 'rejected')),
    CreatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    UpdatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (UserID) REFERENCES Users(UserID),
    FOREIGN KEY (ClubID) REFERENCES Clubs(ClubID)
    CONSTRAINT UniqueUserClubID UNIQUE (UserID, ClubID)
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

CREATE TABLE Phone_Number (
    UserID INTEGER PRIMARY KEY,
    Phone_Number TEXT NOT NULL UNIQUE,
    CreatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    UpdatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);

CREATE TRIGGER IF NOT EXISTS phonenumber_insert_trigger
AFTER INSERT ON Phone_Number
FOR EACH ROW
BEGIN
    UPDATE Phone_Number SET CreatedTimestamp = NEW.CreatedTimestamp WHERE UserID = NEW.UserID;
END;

CREATE TRIGGER IF NOT EXISTS phonenumber_update_trigger
AFTER UPDATE ON Phone_Number
FOR EACH ROW
BEGIN
    UPDATE Phone_Number SET UpdatedTimestamp = CURRENT_TIMESTAMP WHERE UserID = NEW.UserID;
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
    FOREIGN KEY (Club_id) REFERENCES Clubs(ClubID),
    CONSTRAINT UniqueDateTimeVenue UNIQUE (Date_, Time_, Venue_id)
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
	Venue_name VARCHAR(20) NOT NULL UNIQUE,
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
    CONSTRAINT UniqueEventUserID UNIQUE (Event_id, User_id)
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
/*Views*/
CREATE VIEW IF NOT EXISTS AdminAccountView AS
SELECT U.UserID, U.Name || ' ' || U.Surname AS 'Name', L.Username, U.Email, P.Phone_Number, U.Role, U.ApprovalStatus, U.CreatedTimestamp, U.UpdatedTimestamp 
FROM Users U, Login L, Phone_Number P
WHERE U.UserID = L.UserID AND U.UserID = P.UserID

CREATE VIEW IF NOT EXISTS AdminAccountViewPending AS
SELECT U.UserID, U.Name || ' ' || U.Surname AS 'Name', L.Username, U.Email, P.Phone_Number, U.Role, U.ApprovalStatus, U.CreatedTimestamp, U.UpdatedTimestamp 
FROM Users U, Login L, Phone_Number P
WHERE U.UserID = L.UserID AND U.UserID = P.UserID AND U.ApprovalStatus = 'pending'


CREATE VIEW IF NOT EXISTS ClubsView AS
SELECT C.Name, U.Name || " " || U.Surname AS 'Coordinator Name', C.Description
FROM Clubs C, Users U
WHERE C.ValidityStatus = 'approved' AND C.CoordinatorID = U.UserID;


CREATE VIEW IF NOT EXISTS AdminClubsView AS
SELECT C.Name, U.Name || " " || U.Surname AS 'Coordinator Name', C.Description
FROM Clubs C, Users U
WHERE C.CoordinatorID = U.UserID;


CREATE VIEW IF NOT EXISTS AdminClubMembershipView AS
SELECT M.MembershipID, U.Name || " " || U.Surname AS 'User Name', C.Name AS 'Club Name', M.ApprovalStatus, M.CreatedTimestamp, M.UpdatedTimestamp
FROM Clubs C, Users U, ClubMemberships M
WHERE M.UserID = U.UserID AND M.ClubID = C.ClubID
ORDER BY M.CreatedTimestamp DESC;

-------------------------------------------
/*Sample Queries*/
INSERT INTO Users (Name, Surname, Email) VALUES ('Dawid', 'Jakubowski', 'dawijak@gmail.com'), ('James', 'Bond', 'jb.mi6@gmail.com'), ('Mike', 'Ryan', 'mryan@gmail.com'), ('Jacob', 'Stanely', 'jacobstan@gmail.com'), ('Adam', 'Murphy', 'smurf@gmail.com')
UPDATE Users SET Role = 'COORDINATOR' WHERE UserID = 6
UPDATE Clubs SET ValidityStatus = 'approved'

INSERT INTO Login (UserID, Username, Password) VALUES (1, 'dawijak', 'ISE123'), (2, 'Bond', 'moneypenny'), (3, 'Michael', 'Portlaoise04'), (4, 'JacStan20', 'Biscuits29'), (5, 'Murpher35', 'icecream82')

INSERT INTO PhoneNumber (UserID, PhoneNumber) VALUES (1, '0872838474'), (2, '0864240572'), (3, '0892849291'), (4, '0892936471'), (5, '0862846208')


INSERT INTO Venues (Venue_name) VALUES ("Tennis Courts"), ("Swimming Pool"), ("Sports Arena"), ("McGuire Fields")

INSERT INTO Clubs (Name, CoordinatorID, Description) VALUES ("Archery", 2, "Develop archery skills by participating in weekly events"), ("Swimming", 3, "Become a professional swimmer by training in our olympic sized pool"), ("Tennis", 4, "Practice tennis in our well equipped tennis courts")
UPDATE Clubs SET ValidityStatus = 'approved'

INSERT INTO ClubMemberships (UserID, ClubID) VALUES (8, 1), (9, 2), (5, 3), (11, 1), (8, 3), (6, 2)
UPDATE ClubMemberships SET ApprovalStatus = 'approved'

INSERT INTO Events (Club_id, Title, Description, Date_, Time_, Venue_id)
VALUES
  (1, 'Archery Tryouts', 'Opportunity to try archery', '2024-03-01', '14:00', 8),
  (3, 'Tennis Championships', 'Tennis county finals', '2024-03-12', '12:00', 5),
  (2, 'AquaAerobic', 'Fitness exercises in a swimming pool', '2024-03-15', '18:00', 6);
 
 
 INSERT INTO Event_Registration (Event_id, User_id) VALUES (1, 8), (1, 11), (2, 5), (3, 9), (3, 6)
 


SELECT * FROM Login
SELECT * FROM Users 
SELECT * FROM PhoneNumber

SELECT * FROM Clubs 

SELECT * FROM AdminClubsView


