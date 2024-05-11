#ifndef PARSER_H_
#define PARSER_H_
#include "mainwindow.h"


#include "Command.h"
#include "CommandWords.h"

class Parser {
private:
    MainWindow* mainWindow; // Pointer to MainWindow
	CommandWords *commands;

public:
    Parser();
    Parser(MainWindow* mainWindow); // Constructor with MainWindow parameter

    Command* getCommand(std::string buffer);
	void showCommands();
};

#endif /*PARSER_H_*/
