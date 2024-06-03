#ifndef CONCRETEITEM_H_
#define CONCRETEITEM_H_

#include <string>
#include "Item.h" // Assuming Item is a base class or something you're inheriting from

namespace ConcreteItemNamespace {
class ConcreteItem : public Item {
public:
    ConcreteItem(std::string description, int weightGrams, float value);
    ConcreteItem(std::string description, MainWindow* mainWindow);
};
}

#endif /* CONCRETEITEM_H_ */
