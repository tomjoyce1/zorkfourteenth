#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
#include "mainwindow.h"

class ZorkUL : public QObject { // QObject is base class
    Q_OBJECT

signals:
    void roomChanged(const std::string &description);

    void roomChangedImage(const std::string &imgName);

private:

    Parser* parser;
    Room *currentRoom;
    void createRooms();
    void printWelcome();
    bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);
    void createItems();
    void displayItems();
    void displayDestinations();
    std::vector<Item> playerInventory;

public:
    ZorkUL(MainWindow &mainWindow);

    void addItemToInventory(const Item& item);

    void removeItemFromInventory(const std::string& itemName);

    bool playerHasItem(const std::string& itemName) const;



    ~ZorkUL();
    bool update(std::string buffer);
    string go(string direction);

    MainWindow &mainWindow;

    void processItemInteraction(const std::string& itemName);


};




#endif /*ZORKUL_H_*/
