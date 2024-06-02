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

public:
    ZorkUL(MainWindow &mainWindow);

    ~ZorkUL();
    bool update(std::string buffer);
    string go(string direction);

    MainWindow &mainWindow;


};




#endif /*ZORKUL_H_*/
