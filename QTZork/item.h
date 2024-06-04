#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include "Describable.h"


class MainWindow;

class Item : public Describable {
private:
    std::string description;
    int weightGrams;
    float value;
    bool weaponCheck;
    MainWindow* mainWindowInstance;
    friend class ConcreteItem;


public:
    Item(std::string description, int weightGrams, float value);
    Item(std::string description, MainWindow* mainWindow);

    //copy cons deep copy
    Item(const Item& other);

    //virt destructor
    virtual ~Item() = default;

    virtual std::string getShortDescription() const override;
    virtual std::string getLongDescription() const override;

    int getWeight() const;
    void setWeight(int weightGrams);
    float getValue() const;
    void setValue(float value);
    int getWeaponCheck() const;
    void setWeaponCheck(int weaponCheck);
};

#endif /* ITEM_H_ */
