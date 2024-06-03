#include "ConcreteItem.h"

ConcreteItem::ConcreteItem(std::string description, int weightGrams, float value)
    : Item(description, weightGrams, value) {}

ConcreteItem::ConcreteItem(std::string description, MainWindow* mainWindow)
    : Item(description, mainWindow) {}
