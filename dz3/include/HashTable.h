#ifndef DZ3_HASHTABLE_H
#define DZ3_HASHTABLE_H

#include <vector>
#include <string>


template <class Key>
class DefaultHash1 {
public:
    unsigned int operator()(const Key& key) const {
        std::string keyStr = std::to_string(key);
        unsigned int hash = 0;
        for (char i : keyStr) {
            hash = hash * 73 + i;
        }
        return hash;
    }
};

template <class Key>
class DefaultHash2 {
public:
    unsigned int operator()(const Key& key) const {
        std::string keyStr = std::to_string(key);
        unsigned int hash = 0;
        for (char i : keyStr) {
            hash = hash * 37 + i;
        }
        return hash;
    }
};

static const int start_size = 8;


template <class Key, class Hash1, class Hash2>
class HashTable {
    enum class CellType {
        Empty,
        Occupied,
        Del,
    };

    struct HashTableNode {
        Key key;
        CellType state;

        HashTableNode();
    };

public:
    HashTable(const Hash1 &hasher1, const Hash2 &hasher2);

    HashTable(const HashTable &) = delete;
    HashTable(HashTable &&) = delete;
    HashTable& operator=(const HashTable &) = delete;
    HashTable& operator=(HashTable &&) = delete;

    ~HashTable() = default;


    bool insert(const Key& key);
    bool find(const Key& key) const;
    bool erase(const Key& key);

    void print();

private:
    explicit HashTable(size_t size);
    void growTable();

    std::vector<HashTableNode> table_;
    size_t itemsCount_;
    Hash1 hasher1_;
    Hash2 hasher2_;
};


#endif //DZ3_HASHTABLE_H
