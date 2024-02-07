-- CREATE TABLE Users
-- Defines a table for storing user information
CREATE TABLE Users (
    UserID INTEGER PRIMARY KEY AUTOINCREMENT, -- Unique identifier for each user
    Username TEXT NOT NULL UNIQUE, -- User's username, must be unique
    Password TEXT NOT NULL, -- User's password
    Email TEXT NOT NULL UNIQUE, -- User's email, must be unique
    Role TEXT CHECK(Role IN ('ADMIN', 'COORDINATOR', 'STUDENT')), -- User's role, checked against a set of allowed values
    ApprovalStatus TEXT CHECK(ApprovalStatus IN ('approved', 'pending', 'rejected')), -- Status of user's approval
    CreatedTimestamp DATETIME, -- Timestamp of user creation
    UpdatedTimestamp DATETIME -- Timestamp of user information update
);

-- ===========================

-- CREATE TABLE login
-- Defines a table for user login information
CREATE TABLE login(
    UserID INTEGER, -- Foreign key referencing Users table
    PhoneNumber TEXT, -- User's phone number
    FOREIGN KEY (UserID) REFERENCES Users(UserID) -- Reference to Users table
);

-- ----------------------------
-- CREATE TABLE Clubs
-- Defines a table for storing information about clubs
CREATE TABLE Clubs (
    ClubID INTEGER PRIMARY KEY AUTOINCREMENT, -- Unique identifier for each club
    Name TEXT NOT NULL, -- Club name, cannot be null
    CoordinatorID INTEGER, -- Foreign key referencing Users table for club coordinator
    Description TEXT, -- Club description
    ValidityStatus TEXT NOT NULL CHECK(ValidityStatus IN ('approved', 'pending', 'rejected')), -- Status of club's validity
    CreatedTimestamp DATETIME, -- Timestamp of club creation
    UpdatedTimestamp DATETIME, -- Timestamp of club information update
    FOREIGN KEY (CoordinatorID) REFERENCES Users(UserID) -- Reference to Users table for coordinator
);

-- --------------------
-- CREATE TABLE ClubMemberships
-- Defines a table for storing information about club memberships
CREATE TABLE ClubMemberships (
    MembershipID INTEGER PRIMARY KEY AUTOINCREMENT, -- Unique identifier for each club membership
    UserID INTEGER, -- Foreign key referencing Users table for user
    ClubID INTEGER, -- Foreign key referencing Clubs table for club
    ApprovalStatus TEXT CHECK(ApprovalStatus IN ('approved', 'pending', 'rejected')), -- Status of membership approval
    CreatedTimestamp DATETIME, -- Timestamp of membership creation
    UpdatedTimestamp DATETIME, -- Timestamp of membership information update
    FOREIGN KEY (UserID) REFERENCES Users(UserID), -- Reference to Users table for user
    FOREIGN KEY (ClubID) REFERENCES Clubs(ClubID) -- Reference to Clubs table for club
);

-- ----------------------------
-- CREATE TABLE PhoneNumber
-- Defines a table for storing user phone numbers
CREATE TABLE PhoneNumber (
    UserID INTEGER, -- Foreign key referencing Users table
    PhoneNumber TEXT, -- User's phone number
    FOREIGN KEY (UserID) REFERENCES Users(UserID) -- Reference to Users table
);

-- ----------------------
-- CREATE TRIGGER MaxClubsPerUser
-- Defines a trigger to enforce a maximum number of clubs per user
CREATE TRIGGER MaxClubsPerUser
BEFORE INSERT ON ClubMemberships
FOR EACH ROW
WHEN (
    SELECT COUNT(*)
    FROM ClubMemberships
    WHERE UserID = NEW.UserID
) >= 3
BEGIN
    SELECT RAISE(ABORT, 'Maximum number of clubs joined reached'); -- Raises an error if the maximum number of clubs is reached
END;
-- --------------------------


/*Events///////////////////////////////////////////////////////////////*/
CREATE TABLE Events (
    Event_id INTEGER PRIMARY KEY AUTOINCREMENT,
    Club_id INTEGER,
    Title VARCHAR(20) NOT NULL,
    Description VARCHAR(30),
    Date_ DATE NOT NULL,
    Time_ TIME NOT NULL,
    Venue_id NOT NULL,
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
    ApprovalStatus TEXT CHECK(ApprovalStatus IN ('approved', 'pending', 'rejected')),
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




