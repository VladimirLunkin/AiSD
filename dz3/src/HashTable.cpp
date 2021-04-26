#include "HashTable.h"

#include <iostream>

template<class Key, class Hash1, class Hash2>
HashTable<Key, Hash1, Hash2>::HashTableNode::HashTableNode()
        : state(CellType::Empty) {}

//template<class Key, class Hash1, class Hash2>
//HashTable<Key, Hash1, Hash2>::HashTable(const Hash1 &hasher1, const Hash2 &hasher2)
//        : table_(), itemsCount_(0), hasher1_(hasher1), hasher2_(hasher2) {}
/*
template<class Key, class Hash1, class Hash2>
bool HashTable<Key, Hash1, Hash2>::insert(const Key &key) {
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
}*/

template<class Key, class Hash1, class Hash2>
bool HashTable<Key, Hash1, Hash2>::find(const Key &key) const {
    size_t hash1 = hasher1_(key);
    size_t hash2 = 2 * hasher2_(key) + 1;
    for (int i = 0; i < table_.size(); ++i) {
        size_t j = (hash1 + i * hash2) % table_.size();

        if (table_[j].state == CellType::Empty) {
            return false;
        }

        if (table_[j].state == CellType::Occupied && table_[j].key == key) {
            return true;
        }
    }

    return false;
}

template<class Key, class Hash1, class Hash2>
bool HashTable<Key, Hash1, Hash2>::erase(const Key &key) {
    size_t hash1 = hasher1_(key);
    size_t hash2 = 2 * hasher2_(key) + 1;
    for (int i = 0; i < table_.size(); ++i) {
        size_t j = (hash1 + i * hash2) % table_.size();

        if (table_[j].state == CellType::Empty) {
            return false;
        }

        if (table_[j].state == CellType::Occupied && table_[j].key == key) {
            table_[j].state = CellType::Del;
            itemsCount_--;
            return true;
        }
    }

    return false;
}

template<class Key, class Hash1, class Hash2>
void HashTable<Key, Hash1, Hash2>::print() {
    std::cout << "Размер таблицы: " << table_.size() << std::endl;
    std::cout << "Количество элементов: " << itemsCount_ << std::endl;
    for (int i = 0; i < table_.size(); ++i) {
        if (table_[i].state != CellType::Empty)
            std::cout << i+1 << ". " << ((static_cast<int>(table_[i].state) == 1) ? "key: " : "del: ") << table_[i].key << " " << std::endl;
        else
            std::cout << i+1 << ". " << 0 << std::endl;
    }
    std::cout << std::endl;
}

template<class Key, class Hash1, class Hash2>
HashTable<Key, Hash1, Hash2>::HashTable(size_t size)
        : table_(size), itemsCount_(0) {}

template<class Key, class Hash1, class Hash2>
void HashTable<Key, Hash1, Hash2>::growTable() {
    size_t new_size = (table_.empty()) ? start_size : table_.size() * 2;
    HashTable new_table(new_size);
    for (int i = 0; i < table_.size(); ++i) {
        if (table_[i].state == CellType::Occupied) {
            new_table.insert(table_[i].key);
        }
    }
    table_.resize(new_size);
    for (int i = 0; i < table_.size(); ++i) {
        table_[i].state = new_table.table_[i].state;
        if (table_[i].state == CellType::Occupied) {
            table_[i].key = new_table.table_[i].key;
        }
    }
}
