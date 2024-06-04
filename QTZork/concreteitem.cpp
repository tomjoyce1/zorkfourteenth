#include "ConcreteItem.h"
#include "CustomException.h"

namespace ConcreteItemNamespace {

ConcreteItem::ConcreteItem(std::string description, int weightGrams, float value)
    : Item(description, weightGrams, value) {
    if (weightGrams <= 0) {
        throw CustomException("Weight must be positive");
    }
}

ConcreteItem::ConcreteItem(std::string description, MainWindow* mainWindow)
    : Item(description, mainWindow), weightGrams(0), value(0.0f) {}

int ConcreteItem::getWeightGrams() const {
    return weightGrams;
}

float ConcreteItem::getValue() const {
    return value;
}

bool ConcreteItem::operator==(const ConcreteItem& other) const {
    return weightGrams == other.weightGrams && value == other.value;
}

bool ConcreteItem::operator!=(const ConcreteItem& other) const {
    return !(*this == other);
}

bool ConcreteItem::operator<(const ConcreteItem& other) const {
    return weightGrams < other.weightGrams;
}

bool ConcreteItem::operator<=(const ConcreteItem& other) const {
    return weightGrams <= other.weightGrams;
}

bool ConcreteItem::operator>(const ConcreteItem& other) const {
    return weightGrams > other.weightGrams;
}

bool ConcreteItem::operator>=(const ConcreteItem& other) const {
    return weightGrams >= other.weightGrams;
}

std::ostream& operator<<(std::ostream& os, const ConcreteItem& item) {
    os << "Weight: " << item.weightGrams << "g, Value: " << item.value;
    return os;
}


ConcreteItem::ConcreteItem(const ConcreteItem& other)
    : Item(other), weightGrams(other.weightGrams), value(other.value) {
}



} // namespace ConcreteItemNamespace
