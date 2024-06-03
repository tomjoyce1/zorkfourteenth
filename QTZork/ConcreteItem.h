#ifndef CONCRETEITEM_H_
#define CONCRETEITEM_H_

#include "Item.h"

class ConcreteItem : public Item {
public:
    ConcreteItem(std::string description, int weightGrams, float value);
    ConcreteItem(std::string description, MainWindow* mainWindow);
};

#endif /* CONCRETEITEM_H_ */
