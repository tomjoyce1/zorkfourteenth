#include "Room.h"
#include "mainwindow.h"



Room::Room(std::string description, std::string settingDescription) : description(description), settingDescription(settingDescription), commandInstance(Command("", "")) {}
// setExits implementation
void Room::setExits(Room* north, Room* east, Room* south, Room* west) {
    exits["north"] = north;
    exits["east"] = east;
    exits["south"] = south;
    exits["west"] = west;
}

string Room::shortDescription() {
	return description;
}

string Room::longDescription() {
    return "🌍" + description + " 🗺️ " + settingDescription + " 📌 " + displayItem() + " 🧭 " + exitString();
}

string Room::exitString() {
	string returnString = "\nexits =";
	for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
		// Loop through map
		returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
	return returnString;
}

void Room::removeItem(int index) {
    if (index >= 0 && index < itemsInRoom.size()) {
        itemsInRoom.erase(itemsInRoom.begin() + index);
    }
}

Room* Room::nextRoom(string direction) {
	map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
	if (next == exits.end())
		return NULL; // if exits.end() was returned, there's no room in that direction.
	return next->second; // If there is a room, remove the "second" (Room*)
				// part of the "pair" (<string, Room*>) and return it.
}

 void Room::addItem(Item *inItem) {
     itemsInRoom.push_back(*inItem); // Add the item to the vector
 }





string Room::displayItem() {
    string tempString = "The loot you discovered = ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "Unlucky! No items in the area.";
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x].getShortDescription() + "  " ;
            x++;
            }
        }
    return tempString;
    }

int Room::numberOfItems() {
    return itemsInRoom.size();
}

int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        return false;
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[x].getShortDescription());
            if (tempFlag == 0) {
                itemsInRoom.erase(itemsInRoom.begin()+x);
                return x;
            }
            x++;
            }
        }
    return -1;
}

