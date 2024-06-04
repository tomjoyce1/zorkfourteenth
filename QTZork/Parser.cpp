#include "Parser.h"
#include "mainwindow.h"

Parser::Parser() {
    mainWindow = nullptr; // Initialize the pointer to nullptr
    commands = new CommandWords();
}

Parser::Parser(MainWindow* mainWindow) : mainWindow(mainWindow) {
    commands = new CommandWords();
}

Command* Parser::getCommand(std::string buffer) {
    if (buffer.empty()) {
        // Handle empty buffer (return nullptr or create a default command)
        return nullptr;
    }

    string inputLine = "";
    string word1;
    string word2;
    // string buffer;
    vector<string> words;

    // Print prompt if mainWindow is not null
    if (mainWindow != nullptr) {
        mainWindow->setOutputText("> ");
    }

    string::size_type pos = 0, last_pos = 0;

    // Break "buffer" up by spaces
    bool finished = false;
    while (!finished) {
        pos = buffer.find_first_of(' ', last_pos); // finds & remember first space.
        if (pos == string::npos) { // if last word found,
            words.push_back(buffer.substr(last_pos)); // add it to vector "words"
            finished = true; // and finish searching.
        } else { // else add to vector and move on to next word.
            words.push_back(buffer.substr(last_pos, pos - last_pos));
            last_pos = pos + 1;
        }
    }

    if (words.size() == 1) //was only 1 word entered?
        word1 = words[0]; //get first word
    else if (words.size() >= 2) { //were at least 2 words entered?
        word1 = words[0]; //get first word
        word2 = words[1]; //get second word
    }

    if (commands->isCommand(word1))
        return new Command(word1, word2);
    else
        return new Command("", word2);
}

void Parser::showCommands() {
    commands->showAll();
}
