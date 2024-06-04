#ifndef PARSER_H_
#define PARSER_H_
#include "mainwindow.h"

//testing
#include "Command.h"
#include "CommandWords.h"

class Parser {
private:
    MainWindow* mainWindow;
	CommandWords *commands;

public:
    Parser();
    Parser(MainWindow* mainWindow);

    Command* getCommand(std::string buffer);
	void showCommands();
};

#endif /*PARSER_H_*/
