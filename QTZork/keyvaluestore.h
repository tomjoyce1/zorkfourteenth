template<typename KeyType, typename ValueType>
class KeyValueStore {
private:
    std::map<KeyType, ValueType> data;
public:
    // Constructor accepting brace-enclosed initializer list
    KeyValueStore(std::initializer_list<std::pair<const KeyType, ValueType>> list) : data(list) {}

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
