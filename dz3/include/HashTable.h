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


template <class Key, class Hash1 = DefaultHash1<Key>, class Hash2 = DefaultHash2<Key>>
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
    HashTable() : table_(), itemsCount_(0), hasher1_(), hasher2_() {}
//    explicit HashTable(const Hash1 &hasher1 = Hash1(), const Hash2 &hasher2 = Hash2());

    HashTable(const HashTable &) = delete;
    HashTable(HashTable &&) = delete;
    HashTable& operator=(const HashTable &) = delete;
    HashTable& operator=(HashTable &&) = delete;

    ~HashTable() = default;
    void growTable();
    bool insert(const Key& key) {
        if (itemsCount_ * 4 >= table_.size() * 3) {
            growTable();
        }

        size_t hash1 = hasher1_(key);
        size_t hash2 = 2 * hasher2_(key) + 1;
        ssize_t first_del = -1;
        for (int i = 0; i < table_.size(); ++i) {
            size_t j = (hash1 + i * hash2) % table_.size();

            if (table_[j].state == CellType::Empty) {
                if (first_del != -1) {
                    j = first_del;
                }
                table_[j].key = key;
                table_[j].state = CellType::Occupied;
                itemsCount_++;
                return true;
            }

            if (table_[j].state == CellType::Occupied && table_[j].key == key) {
                return false;
            }

            if (table_[j].state == CellType::Del && first_del == -1) {
                first_del = j;
            }
        }

        table_[first_del].key = key;
        table_[first_del].state = CellType::Occupied;
        itemsCount_++;
        return true;
    }
//    bool insert(const Key& key);
    bool find(const Key& key) const;
    bool erase(const Key& key);

    void print();

private:
    explicit HashTable(size_t size);
//    void growTable();

    std::vector<HashTableNode> table_;
    size_t itemsCount_;
    Hash1 hasher1_;
    Hash2 hasher2_;
};


#endif //DZ3_HASHTABLE_H
