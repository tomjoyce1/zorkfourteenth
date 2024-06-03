#include "Command.h"



Command::Command(string firstWord, string secondWord) {
	this->commandWord = firstWord;
	this->secondWord = secondWord;
}

/**
 * Return the command word (the first word) of this command. If the
 * command was not understood, the result is null.
 */
string Command::getCommandWord() {
	return this->commandWord;
}

/**
 * Return the second word of this command. Returns null if there was no
 * second word.
 */
string Command::getSecondWord() {
	return this->secondWord;
}

/**
 * Return true if this command was not understood.
 */
bool Command::isUnknown() {
	return (commandWord.empty());
}

/**
 * Return true if the command has a second word.
 */
bool Command::hasSecondWord() {
	return (!secondWord.empty());
}

