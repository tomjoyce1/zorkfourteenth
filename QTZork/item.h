#ifndef ITEM_H_
#define ITEM_H_

#include <string>

// Forward declaration of MainWindow
class MainWindow;

class Item {
private:
    std::string description;
    int weightGrams;
    float value;
    bool weaponCheck;
    MainWindow* mainWindowInstance; // Pointer to MainWindow
public:
    Item(std::string description, int weightGrams, float value);
    Item(std::string description, MainWindow* mainWindow);
    std::string getShortDescription() const;
    std::string getLongDescription();
    int getWeight();
    void setWeight(int weightGrams);
    float getValue();
    void setValue(float value);
    int getWeaponCheck();
    void setWeaponCheck(int weaponCheck);
};

#endif /* ITEM_H_ */
