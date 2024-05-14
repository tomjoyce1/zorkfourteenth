#include <iostream>
#include <string> // Include the string header
#include "ZorkUL.h"

ZorkUL::ZorkUL(MainWindow &mainWindow) : mainWindow(mainWindow) {
    parser = new Parser(); // Assuming Parser is the name of your parser class
    printWelcome(); // works up to here
    createRooms();
    // createItems();
}

void ZorkUL::printWelcome() {
    mainWindow.setOutputText("This part works printwelcome zorkul");
}

void ZorkUL::createRooms()  {
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i;
    string roomDescription; // Declare roomDescription as a string here

    roomDescription = "a";
    a = new Room(roomDescription);

    a->addItem(new Item("x", 1, 11));
    a->addItem(new Item("y", 2, 22));
    mainWindow.appendOutputText("room a created");

    roomDescription = "b";
    b = new Room(roomDescription);
    b->addItem(new Item("xx", 3, 33));
    b->addItem(new Item("yy", 4, 44));

    roomDescription = "c";
    c = new Room(roomDescription);
    c->addItem(new Item("xx", 3, 33));
    c->addItem(new Item("yy", 4, 44));

    roomDescription = "d";
    d = new Room(roomDescription);
    d->addItem(new Item("xx", 3, 33));
    d->addItem(new Item("yy", 4, 44));

    roomDescription = "e";
    e = new Room(roomDescription);
    e->addItem(new Item("xx", 3, 33));
    e->addItem(new Item("yy", 4, 44));

    roomDescription = "f"; // Change to std::string
    f = new Room(roomDescription);

    roomDescription = "g"; // Change to std::string
    g = new Room(roomDescription);

    roomDescription = "h"; // Change to std::string
    h = new Room(roomDescription);

    roomDescription = "i"; // Change to std::string
    i = new Room(roomDescription);

    // Set exits for rooms
    a->setExits(f, b, d, c);
    b->setExits(a, b, c, d);
    c->setExits(a, b, c, d);
    d->setExits(a, b, c, d);
    e->setExits(a, b, c, d);
    f->setExits(a, b, c, d);
    g->setExits(a, b, c, d);
    h->setExits(a, b, c, d);
    i->setExits(a, b, c, d);

    currentRoom = a;

}

bool ZorkUL::update(std::string buffer) {
    qDebug() << "Update function called with buffer: " << QString::fromStdString(buffer);

    // Check if parser is null
    if (!parser) {
        qDebug() << "Error: Parser object is null";
        return false;
    }

    qDebug() << "parser is not null";

    // Create pointer to command and give it a command.
    Command* command = parser->getCommand(buffer);

    qDebug() << "command pointer made";

    // Check if command is null
    if (!command) {
        qDebug() << "Error: Command pointer is null";
        return false;
    }

    qDebug() << "command pointer made";

    // Pass dereferenced command and check for end of game.
    qDebug() << "command is true and not !command ";
    bool finished = processCommand(*command);

    // Free the memory allocated by "parser.getCommand()"
    delete command;
    qDebug() << "command just deleted ";

    qDebug() << "Update finished: " << finished;
    return finished;
}





// outputLineEdit->append("start");
// outputLineEdit->append("info for help");
// outputLineEdit->append("");
// outputLineEdit->append(QString::fromStdString(currentRoom->longDescription()));





//original conor one
// void ZorkUL::printWelcome() {
//     cout << "start"<< endl;
//     cout << "info for help"<< endl;
//     cout << endl;
//     cout << currentRoom->longDescription() << endl;


// }

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool ZorkUL::processCommand(Command command) {
    if (command.isUnknown()) {
        mainWindow.setOutputText("invalid input");
        return false;
    }

    std::string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        printHelp();

    else if (commandWord.compare("map") == 0)
    {
        cout << "[h] --- [f] --- [g]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[c] --- [a] --- [b]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[i] --- [d] --- [e]" << endl;
    }

    else if (commandWord.compare("go") == 0)
        goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
        if (!command.hasSecondWord()) {
            mainWindow.setOutputText("Incomplete input");
        }
        else
            if (command.hasSecondWord()) {

                mainWindow.setOutputText("you're tryna take " + command.getSecondWord());

                //mainWindow.setOutputText("you're tryna take" + command.getSecondWord());
                //cout << "you're trying to take " + command.getSecondWord() << endl;
                int location = currentRoom->isItemInRoom(command.getSecondWord());
                if (location  < 0 )
                    mainWindow.setOutputText("Item is not in this place.  Better luck next time chump.");

                else
                    mainWindow.setOutputText("item is in room");

                mainWindow.appendOutputText("index number " + std::to_string(location));            //cout << "index number " << + location << endl;
                //cout << endl;
                mainWindow.setOutputText(currentRoom->longDescription());
                //cout << currentRoom->longDescription() << endl;
            }
    }

    else if (commandWord.compare("put") == 0)
    {
        // Process put command
    }

    else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord())
            mainWindow.setOutputText("overdefined input");
        else
            return true; // Signal to quit
    }
    return false;
}




/** COMMANDS **/
void ZorkUL::printHelp() {
    mainWindow.setOutputText("valid inputs are;");
    //cout << "valid inputs are; " << endl;
    // tom come back to this parser.showCommands();

}

void ZorkUL::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        mainWindow.setOutputText("Incomplete input");
        //cout << "incomplete input"<< endl;
        return;
    }

    std::string direction = command.getSecondWord();

    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        mainWindow.setOutputText("next room is null so underdefined input");
    //cout << "underdefined input"<< endl;
    else {
        currentRoom = nextRoom;
        //cout << currentRoom->longDescription() << endl;
        mainWindow.setOutputText(currentRoom->longDescription());

        emit roomChanged(currentRoom->longDescription());

    }
}

ZorkUL::~ZorkUL() {
    // Destructor implementation
    // Free any dynamically allocated memory, close any resources, etc.
}


string ZorkUL::go(string direction) {
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("direction null");
    else
    {
        currentRoom = nextRoom;
        return currentRoom->longDescription();
    }
}
