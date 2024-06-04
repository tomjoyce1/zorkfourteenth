#ifndef COMMANDWORDS_H_
#define COMMANDWORDS_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CommandWords {
private:
    //vector to store commands
	static vector<string> validCommands;

public:
	CommandWords();
	bool isCommand(string aString);
	void showAll();
};


#endif /*COMMANDWORDS_H_*/
