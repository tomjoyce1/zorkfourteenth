#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "mainwindow.h"
#include "Command.h"
using namespace std;

using std::vector;

class Room {

private:
    struct RoomFlags {
        bool hasMonster : 1;    // 1 bit shows if the room has a monster
        bool addMonster : 1;    // 1 bit says if monster should be added to the room
    } flags;

    std::string description;
    std::string settingDescription;

    map<string, Room*> exits;
    string exitString();
    vector <Item> itemsInRoom;
    MainWindow* mainWindowPtr;
    Command commandInstance;

public:
    void removeItem(int index);
    int numberOfItems();
    Room(std::string description, std::string settingDescription);
    string shortDescription();
    string longDescription();
    Room* nextRoom(string direction);
    void setExits(Room *north, Room *east, Room *south, Room *west);
    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);


    void setHasMonster(bool value) { flags.hasMonster = value; }
    void setAddMonster(bool value) { flags.addMonster = value; }


    bool hasMonster() const { return flags.hasMonster; }
    bool addMonster() const { return flags.addMonster; }
};

#endif
