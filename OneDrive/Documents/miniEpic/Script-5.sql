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
