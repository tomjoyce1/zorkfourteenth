template<typename KeyType, typename ValueType>

//template of key-value store using a std::map

class KeyValueStore {
private:
    std::map<KeyType, ValueType> data;
public:

    //constructor intitializes data with key value pairs
    KeyValueStore(std::initializer_list<std::pair<const KeyType, ValueType>> list) : data(list) {}

    void addItem(const KeyType& key, const ValueType& value) {
        data[key] = value;
    }

    ValueType getValue(const KeyType& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        } else {
            // if key not found
            return ValueType();
        }
    }
};
