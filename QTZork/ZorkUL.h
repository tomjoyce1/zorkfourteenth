#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
#include "mainwindow.h"

class ZorkUL : public QObject { // Add QObject as base class
    Q_OBJECT // Add Q_OBJECT macro

signals:
    void roomChanged(const std::string &description);
    //3pm
    void roomChangedImage(const std::string &imgName);

private:
    Parser* parser;
    Room *currentRoom;
    void createRooms();
    void printWelcome(); // Remove the parameter
    bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);
    void createItems();
    void displayItems();
    void displayDestinations();
    std::vector<Item> playerInventory; // Vector to store the player's items

public:
    ZorkUL(MainWindow &mainWindow);

    void addItemToInventory(const Item& item);

    // Function to remove an item from the player's inventory
    void removeItemFromInventory(const std::string& itemName);

    // Function to check if the player has a specific item
    bool playerHasItem(const std::string& itemName) const;



    ~ZorkUL();
    bool update(std::string buffer);
    string go(string direction);

    MainWindow &mainWindow;

    void processItemInteraction(const std::string& itemName);


};




#endif /*ZORKUL_H_*/
