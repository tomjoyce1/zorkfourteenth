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
    union Weight {
        int weightGrams;
        float weightKilos;

        Weight() : weightGrams(0) {}
        ~Weight() {}
    } weight;

    float value;

public:
    ConcreteItem(std::string description, int weightGrams, float value);
    ConcreteItem(std::string description, MainWindow* mainWindow);

    ConcreteItem(const ConcreteItem& other);

    int getWeightGrams() const;
    float getWeightKilos() const;
    float getValue() const;

    bool operator==(const ConcreteItem& other) const;
    bool operator!=(const ConcreteItem& other) const;
    bool operator<(const ConcreteItem& other) const;
    bool operator<=(const ConcreteItem& other) const;
    bool operator>(const ConcreteItem& other) const;
    bool operator>=(const ConcreteItem& other) const;

    friend std::ostream& operator<<(std::ostream& os, const ConcreteItem& item);
};

} // namespace ConcreteItemNamespace

#endif // CONCRETEITEM_H
