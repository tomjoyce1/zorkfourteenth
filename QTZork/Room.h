#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "mainwindow.h" // Include MainWindow header
#include "Command.h"
using namespace std;

using std::vector;

class Room {

private:
    std::string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;
    MainWindow* mainWindowPtr; // Pointer to MainWindow object
    Command commandInstance; // Declare a Command instance

public:
    int numberOfItems();
    Room(std::string description);
    string shortDescription();
	string longDescription();
	Room* nextRoom(string direction);
    void setExits(Room *north, Room *east, Room *south, Room *west);
    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
};

#endif
