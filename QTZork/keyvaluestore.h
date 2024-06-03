#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

#include <map>

template<typename KeyType, typename ValueType>
class KeyValueStore {
private:
    std::map<KeyType, ValueType> data;
public:
    void addItem(const KeyType& key, const ValueType& value) {
        data[key] = value;
    }

    ValueType getValue(const KeyType& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        } else {
            // Handle key not found
            return ValueType(); // Return default-constructed value
        }
    }
};

#endif // KEYVALUESTORE_H
