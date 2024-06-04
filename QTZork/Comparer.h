#ifndef COMPARER_H
#define COMPARER_H

namespace ComparerNamespace {
class Comparer {
public:
    virtual bool operator==(const Comparer& other) const { return false; }
    virtual bool operator!=(const Comparer& other) const { return !(*this == other); }
    virtual bool operator<(const Comparer& other) const { return false; }
    virtual bool operator<=(const Comparer& other) const { return !(*this > other); }
    virtual bool operator>(const Comparer& other) const { return false; }
    virtual bool operator>=(const Comparer& other) const { return !(*this < other); }
};
}

#endif // COMPARER_H
