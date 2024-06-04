#include "ConcreteItem.h"
#include "CustomException.h"

namespace ConcreteItemNamespace {

ConcreteItem::ConcreteItem(std::string description, int weightGrams, float value)
    : Item(description, weightGrams, value) {
    if (weightGrams <= 0) {
        throw CustomException("Weight must be positive");
    }
    weight.weightGrams = weightGrams;

}



ConcreteItem::ConcreteItem(std::string description, MainWindow* mainWindow)
    : Item(description, mainWindow), value(0.0f) {
    weight.weightGrams = 0;
}

ConcreteItem::ConcreteItem(const ConcreteItem& other)
    : Item(other), value(other.value) {
    weight = other.weight;
}

int ConcreteItem::getWeightGrams() const {
    return weight.weightGrams;
}

float ConcreteItem::getWeightKilos() const {
    return weight.weightKilos;
}

float ConcreteItem::getValue() const {
    return value;
}

bool ConcreteItem::operator==(const ConcreteItem& other) const {
    return weight.weightGrams == other.weight.weightGrams && value == other.value;
}

bool ConcreteItem::operator!=(const ConcreteItem& other) const {
    return !(*this == other);
}

bool ConcreteItem::operator<(const ConcreteItem& other) const {
    return weight.weightGrams < other.weight.weightGrams;
}

bool ConcreteItem::operator<=(const ConcreteItem& other) const {
    return !(*this > other);
}

bool ConcreteItem::operator>(const ConcreteItem& other) const {
    return weight.weightGrams > other.weight.weightGrams;
}

bool ConcreteItem::operator>=(const ConcreteItem& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const ConcreteItem& item) {
    os << "Weight: " << item.getWeightGrams() << "g, Value: " << item.getValue();
    return os;
}

} // namespace ConcreteItemNamespace
