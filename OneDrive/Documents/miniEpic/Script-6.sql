
CREATE TABLE Users (
    UserID INTEGER PRIMARY KEY AUTOINCREMENT,
    Email TEXT NOT NULL UNIQUE,
    Role TEXT DEFAULT 'STUDENT' CHECK(Role IN ('ADMIN', 'COORDINATOR', 'STUDENT')),
    ApprovalStatus TEXT CHECK(ApprovalStatus IN ('approved', 'pending', 'rejected')),
    CreatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    UpdatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);


-===========================

CREATE TABLE login(
UserID INTEGER,
Username TEXT NOT NULL UNIQUE,
Password TEXT NOT NULL,
FOREIGN KEY (UserID) references Users(UserID)


)

-------------------------------
CREATE TABLE Clubs (
    ClubID INTEGER PRIMARY KEY AUTOINCREMENT,
    Name TEXT NOT NULL,
    CoordinatorID INTEGER,
    Description TEXT,
    ValidityStatus TEXT NOT NULL CHECK(ValidityStatus IN ('approved', 'pending', 'rejected')),
    CreatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    UpdatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (CoordinatorID) REFERENCES Users(UserID)
);

--------------------

CREATE TABLE ClubMemberships (
    MembershipID INTEGER PRIMARY KEY autoincrement,
    UserID INTEGER,
    ClubID INTEGER,
    ApprovalStatus TEXT CHECK(ApprovalStatus IN ('approved', 'pending', 'rejected')),
    CreatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    UpdatedTimestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (UserID) REFERENCES Users(UserID),
    FOREIGN KEY (ClubID) REFERENCES Clubs(ClubID)
);

----------------------------

CREATE TABLE PhoneNumber (
    UserID INTEGER,
    PhoneNumber TEXT NOT NULL,
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);
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


-- Triggers for each of my tables

-----------------------
-- Users Table Trigger
CREATE TRIGGER IF NOT EXISTS users_update_trigger
AFTER UPDATE ON Users
FOR EACH ROW
BEGIN
    UPDATE Users SET UpdatedTimestamp = CURRENT_TIMESTAMP WHERE UserID = NEW.UserID;
END;

-- Clubs Table Trigger
CREATE TRIGGER IF NOT EXISTS clubs_update_trigger
AFTER UPDATE ON Clubs
FOR EACH ROW
BEGIN
    UPDATE Clubs SET UpdatedTimestamp = CURRENT_TIMESTAMP WHERE ClubID = NEW.ClubID;
END;

-- ClubMemberships Table Trigger
CREATE TRIGGER IF NOT EXISTS clubmemberships_update_trigger
AFTER UPDATE ON ClubMemberships
FOR EACH ROW
BEGIN
    UPDATE ClubMemberships SET UpdatedTimestamp = CURRENT_TIMESTAMP WHERE MembershipID = NEW.MembershipID;
END;

-- PhoneNumber Table Trigger
CREATE TRIGGER IF NOT EXISTS phonenumber_update_trigger
AFTER UPDATE ON PhoneNumber
FOR EACH ROW
BEGIN
    UPDATE PhoneNumber SET UpdatedTimestamp = CURRENT_TIMESTAMP WHERE UserID = NEW.UserID;
END;


