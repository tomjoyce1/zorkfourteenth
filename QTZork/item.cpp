#include "item.h"
#include "mainwindow.h"

Item::Item(std::string inDescription, int inWeightGrams, float inValue) {
    description = inDescription;
    setWeight(inWeightGrams);
    value = inValue;
    // weaponCheck(isWeapon);
}

Item::Item(std::string inDescription, MainWindow* mainWindow) {
    description = inDescription;
    mainWindowInstance = mainWindow;
}

void Item::setWeight(int inWeightGrams) {
    if (inWeightGrams > 9999 || inWeightGrams < 0)
        mainWindowInstance->setOutputText("Weight invalid, must be 0 < weight < 9999");
    else
        weightGrams = inWeightGrams;
}

void Item::setValue(float inValue) {
    if (inValue > 9999 || inValue < 0)
        mainWindowInstance->setOutputText("Value invalid, must be 0 < value < 9999");
    else
        value = inValue;
}

std::string Item::getShortDescription() const {
    return description;
}

std::string Item::getLongDescription() const {
    return "Item(s): " + description + ".\n";
}

int Item::getWeight() const {
    return weightGrams;
}

float Item::getValue() const {
    return value;
}

int Item::getWeaponCheck() const {
    return weaponCheck;
}

void Item::setWeaponCheck(int inWeaponCheck) {
    weaponCheck = inWeaponCheck;
}

Item::Item(const Item& other)
    : description(other.description), weightGrams(other.weightGrams),
    value(other.value), mainWindowInstance(other.mainWindowInstance) {
    // Copy constructor for deep copy
}
