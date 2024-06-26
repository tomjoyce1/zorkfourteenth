#ifndef DESCRIBABLE_H_
#define DESCRIBABLE_H_

#include <string>
//abstract base class, can't be instantiated directly
class Describable {
public:
    //virt destructor
    virtual ~Describable() = default;
    virtual std::string getShortDescription() const = 0;
    virtual std::string getLongDescription() const = 0;
};

#endif /* DESCRIBABLE_H_ */
