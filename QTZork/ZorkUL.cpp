#include <iostream>
#include "ZorkUL.h"
#include <map>
#include <string>

//tue
#include "ConcreteItem.h"
#include "MainWindow.h"
#include "keyvaluestore.h"





ZorkUL::ZorkUL(MainWindow &mainWindow) : mainWindow(mainWindow) {
    parser = new Parser();
    printWelcome(); // works up to here
    createRooms();
    // createItems();
}

void ZorkUL::printWelcome() {
    mainWindow.setOutputText("Welcome to Zork.  You find yourself in the depths of Antartica as you embark on a magical journey.  Where will you go next? ");
}

void ZorkUL::createRooms() {
    Room *Antartica, *London, *Mineland, *Mars, *Moonscape, *Farmville, *Wastelandia, *Paradise, *Alienscape;

    Antartica = new Room("Antartica", "You are in the icy wasteland of Antartica. The cold bites at your skin.");
    Antartica->addItem(new ConcreteItem("Snowshoes", 1, 11));
    Antartica->addItem(new ConcreteItem("Chisel", 2, 22));

    London = new Room("London", "You are in the bustling city of London. The streets are full of life.");
    London->addItem(new ConcreteItem("Umbrella", 3, 33));
    London->addItem(new ConcreteItem("Map", 4, 44));

    Mineland = new Room("Mineland", "You are in a mine. The air is thick with dust and the sound of pickaxes.");
    Mineland->addItem(new ConcreteItem("Pickaxe", 5, 55));
    Mineland->addItem(new ConcreteItem("Lantern", 6, 66));

    Mars = new Room("Mars", "You are on the red planet Mars. The landscape is barren and rocky.");
    Mars->addItem(new ConcreteItem("Helmet", 7, 77));
    Mars->addItem(new ConcreteItem("Asteroid", 8, 88));

    Moonscape = new Room("Moonscape", "You are on the surface of the Moon. The earth is a distant blue sphere.");
    Moonscape->addItem(new ConcreteItem("Dust", 9, 99));
    Moonscape->addItem(new ConcreteItem("Spacegun", 10, 100));

    Farmville = new Room("Farmville", "You are in a peaceful farmland. The smell of fresh crops fills the air.");
    Farmville->addItem(new ConcreteItem("Hoe", 11, 111));
    Farmville->addItem(new ConcreteItem("Seeds", 12, 122));

    Wastelandia = new Room("Wastelandia", "You are in a post-apocalyptic wasteland. The ground is scorched and barren.");
    Wastelandia->addItem(new ConcreteItem("Barometer", 13, 133));
    Wastelandia->addItem(new ConcreteItem("Safety-suit", 14, 144));

    Paradise = new Room("Paradise", "You are in a lush paradise. The air is sweet with the scent of flowers.");
    Paradise->addItem(new ConcreteItem("Pipseeds", 15, 155));
    Paradise->addItem(new ConcreteItem("Orchid", 16, 166));

    Alienscape = new Room("Alienscape", "You are in an alien landscape. Strange plants and creatures surround you.");
    Alienscape->addItem(new ConcreteItem("Blowtorch", 17, 177));
    Alienscape->addItem(new ConcreteItem("Marblefruit", 18, 188));

    // Set exits for rooms
    Antartica->setExits(Moonscape, London, Mars, Wastelandia);
    London->setExits(Mineland, Mars, Antartica, Paradise);
    Mineland->setExits(Mars, Antartica, Alienscape, London);
    Mars->setExits(Alienscape, London, Paradise, Mineland);
    Moonscape->setExits(Farmville, Antartica, Wastelandia, Paradise);
    Farmville->setExits(Wastelandia, Moonscape, Alienscape, Paradise);
    Wastelandia->setExits(London, Moonscape, Paradise, Farmville);
    Paradise->setExits(Moonscape, Wastelandia, London, Mars);
    Alienscape->setExits(Mineland, Mars, Farmville, Wastelandia);

    currentRoom = Antartica;
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



// std::map<std::string, std::string> itemInteractions = {

KeyValueStore<std::string, std::string> itemInteractionsStore = {
    std::make_pair("Snowshoes", "You can traverse icy terrain more easily. That'll come in handy as you sense polar bears in the distance."),
    std::make_pair("Chisel", "You can use the chisel to carve through ice or stone. Pity that it's time to go"),
    std::make_pair("Umbrella", "The umbrella keeps you dry in the rain."),
    std::make_pair("Map", "The map helps you navigate through unfamiliar territory."),
    std::make_pair("Pickaxe", "Use the pickaxe to mine for resources."),
    std::make_pair("Lantern", "The lantern provides light in dark areas."),
    std::make_pair("Helmet", "The helmet protects your head from impacts."),
    std::make_pair("Asteroid", "A fragment of an asteroid. It might have some value."),
    std::make_pair("Dust", "Moon dust. It's lightweight and powdery."),
    std::make_pair("Spacegun", "A futuristic weapon. Handle with care."),
    std::make_pair("Hoe", "Use the hoe to cultivate the soil."),
    std::make_pair("Seeds", "Plant these seeds to grow crops."),
    std::make_pair("Barometer", "Measures atmospheric pressure."),
    std::make_pair("Safety-suit", "Provides protection from hazardous environments."),
    std::make_pair("Pipseeds", "Seeds of exotic plants. Handle with care."),
    std::make_pair("Orchid", "A beautiful flower with a pleasant fragrance."),
    std::make_pair("Blowtorch", "Emits a hot flame. Useful for cutting or welding."),
    std::make_pair("Marblefruit", "A rare fruit with a marble-like texture.")
    // Add more items and interactions here if needed
};




void ZorkUL::addItemToInventory(const Item& item) {
    playerInventory.push_back(item);
}


void ZorkUL::removeItemFromInventory(const std::string& itemName) {
    for (auto iter = playerInventory.begin(); iter != playerInventory.end(); ++iter) {
        if (iter->getShortDescription() == itemName) {
            playerInventory.erase(iter);
            break; // Exit the loop once the item is removed
        }
    }
}

bool ZorkUL::playerHasItem(const std::string& itemName) const {
    for (const auto& item : playerInventory) {
        if (item.getShortDescription() == itemName) {
            return true;
        }
    }
    return false;
}


void ZorkUL::processItemInteraction(const std::string& itemName) {


    std::string interaction = itemInteractionsStore.getValue(itemName); // Use KeyValueStore to get item interaction

//    auto it = itemInteractions.find(itemName);
    if (!interaction.empty()) {        // Item interaction found, display the corresponding message
        mainWindow.setOutputText(interaction);        // Implement additional logic as needed (e.g., enemy attack)
    } else {
        // No specific interaction defined for this item
        mainWindow.setOutputText("You took the item.  Time to scarper to a new area.");    }
}

bool ZorkUL::processCommand(Command command) {
    // Check if the command is unknown
    if (command.isUnknown()) {
        mainWindow.setOutputText("Invalid input");
        return false;
    }



    std::string commandWord = command.getCommandWord();

    if(commandWord.compare("go") == 0)
        goRoom(command);
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


    else if (commandWord.compare("take") == 0) {
        // Handle taking an item
        if (!command.hasSecondWord()) {
            mainWindow.setOutputText("Incomplete input");
        } else {
            std::string itemName = command.getSecondWord();
            int location = currentRoom->isItemInRoom(itemName);
            if (location < 0) {
                mainWindow.setOutputText("Item is not in this place. Better luck next time chump.");
            } else {
                // Item found in the room
                mainWindow.setOutputText("You've taken " + itemName);
                currentRoom->removeItem(location); // Remove the item from the room
                // Process the item interaction
                processItemInteraction(itemName);
            }
        }
    }

    else if (commandWord.compare("show") == 0 && command.hasSecondWord() && command.getSecondWord() == "items") {
        // Handle the "show items" command
        std::string itemList;
        if (playerInventory.empty()) {
            mainWindow.setOutputText("Your inventory is empty.");
        } else {
            for (const auto& item : playerInventory) {
                itemList += item.getShortDescription() + "\n";
            }
            mainWindow.setOutputText("Items in your inventory:\n" + itemList);
        }
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
        mainWindow.setOutputText("Don't think you can escape that way!");
    //cout << "underdefined input"<< endl;
    else {
        currentRoom = nextRoom;
        //cout << currentRoom->longDescription() << endl;
        mainWindow.setOutputText(currentRoom->longDescription());

        emit roomChanged(currentRoom->longDescription());

        //3pm
        emit roomChangedImage(currentRoom->shortDescription());

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
