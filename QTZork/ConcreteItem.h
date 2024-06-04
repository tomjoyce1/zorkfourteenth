#ifndef CONCRETEITEM_H
#define CONCRETEITEM_H

#include "Item.h"
#include "CustomException.h"
#include <string>
#include <iostream>
#include "Comparer.h"

namespace ConcreteItemNamespace {
class ConcreteItem : public Item, public ComparerNamespace::Comparer {
private:
    int weightGrams;
    float value;

public:
    //2 constructors, diff parameters
    ConcreteItem(std::string description, int weightGrams, float value);
    ConcreteItem(std::string description, MainWindow* mainWindow);

    // Copy constructor for deep copy
    ConcreteItem(const ConcreteItem& other);

    int getWeightGrams() const;
    float getValue() const;

    bool operator==(const ConcreteItem& other) const;
    bool operator!=(const ConcreteItem& other) const;
    bool operator<(const ConcreteItem& other) const;
    bool operator<=(const ConcreteItem& other) const;
    bool operator>(const ConcreteItem& other) const;
    bool operator>=(const ConcreteItem& other) const;


    //parameters=object os + ConcreteItem object, outputs ConcreteItem objects to console.
    friend std::ostream& operator<<(std::ostream& os, const ConcreteItem& item);
};
}

#endif // CONCRETEITEM_H
