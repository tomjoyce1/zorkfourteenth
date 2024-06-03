// ConcreteItem.h
#ifndef CONCRETEITEM_H
#define CONCRETEITEM_H

#include "Item.h"
#include "CustomException.h"
#include <string>
#include <iostream>

namespace ConcreteItemNamespace {
class ConcreteItem : public Item {
private:
    int weightGrams;
    float value;

public:
    ConcreteItem(std::string description, int weightGrams, float value);
    ConcreteItem(std::string description, MainWindow* mainWindow);

    int getWeightGrams() const;
    float getValue() const;

    bool operator==(const ConcreteItem& other) const;
    bool operator!=(const ConcreteItem& other) const;
    bool operator<(const ConcreteItem& other) const;
    bool operator<=(const ConcreteItem& other) const;
    bool operator>(const ConcreteItem& other) const;
    bool operator>=(const ConcreteItem& other) const;

    friend std::ostream& operator<<(std::ostream& os, const ConcreteItem& item);
};
}

#endif // CONCRETEITEM_H
