#include "CommandWords.h"

//vector of strings that'll store words
vector<string> CommandWords::validCommands;


CommandWords::CommandWords() {
	// Populate the vector if we haven't already.
	if (validCommands.empty()) {
		validCommands.push_back("go");
		validCommands.push_back("quit");
		validCommands.push_back("take");
	}
}

bool CommandWords::isCommand(string aString) {
	for (unsigned int i = 0; i < validCommands.size(); i++)
	{
		if (validCommands[i].compare(aString) == 0)
			return true;
	}
	return false;
}



void CommandWords::showAll() {
	for (unsigned int i = 0; i < validCommands.size(); i++)
	{
		cout << validCommands[i]<< "  ";
	}
	cout << endl;
}
