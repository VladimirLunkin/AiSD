#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Hash1 {
public:
    unsigned int operator()(const string& key) const {
        unsigned int hash = 0;
        for (char i : key) {
            hash = hash * 73 + i;
        }
        return hash;
    }
};

class Hash2 {
public:
    unsigned int operator()(const string& key) const {
        unsigned int hash = 0;
        for (char i : key) {
            hash = hash * 37 + i;
        }
        return hash;
    }
};

static const int start_size = 8;

enum class CellType {
    Empty,
    Key,
    Del,
};

template <class Key, class H1, class H2>
class HashTable {
    struct HashTableNode {
        Key key;
        CellType state;

        HashTableNode(): state(CellType::Empty) {}
    };

public:
    HashTable(H1& _hasher1, H2& _hasher2): table(0), items_count(0), hasher1(_hasher1), hasher2(_hasher2) {}
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    ~HashTable() = default;

    bool insert(const Key& key) {
        if (items_count * 4 >= table.size() * 3) {
            grow_table();
        }

        size_t hash1 = hasher1(key);
        size_t hash2 = 2 * hasher2(key) + 1;
        ssize_t first_del = -1;
        for (int i = 0; i < table.size(); ++i) {
            size_t j = (hash1 + i * hash2) % table.size();

            if (table[j].state == CellType::Empty) {
                if (first_del != -1) {
                    j = first_del;
                }
                table[j].key = key;
                table[j].state = CellType::Key;
                items_count++;
                return true;
            }

            if (table[j].state == CellType::Key && table[j].key == key) {
                return false;
            }

            if (table[j].state == CellType::Del && first_del == -1) {
                first_del = j;
            }
        }

        table[first_del].key = key;
        table[first_del].state = CellType::Key;
        items_count++;
        return true;
    }
    bool find(const Key& key) const {
        size_t hash1 = hasher1(key);
        size_t hash2 = 2 * hasher2(key) + 1;
        for (int i = 0; i < table.size(); ++i) {
            size_t j = (hash1 + i * hash2) % table.size();

            if (table[j].state == CellType::Empty) {
                return false;
            }

            if (table[j].state == CellType::Key && table[j].key == key) {
                return true;
            }
        }

        return false;
    }
    bool erase(const Key& key) {
        size_t hash1 = hasher1(key);
        size_t hash2 = 2 * hasher2(key) + 1;
        for (int i = 0; i < table.size(); ++i) {
            size_t j = (hash1 + i * hash2) % table.size();

            if (table[j].state == CellType::Empty) {
                return false;
            }

            if (table[j].state == CellType::Key && table[j].key == key) {
                table[j].state = CellType::Del;
                items_count--;
                return true;
            }
        }

        return false;
    }

    void print() {
        cout << "Размер таблицы: " << table.size() << endl;
        cout << "Количество элементов: " << items_count << endl;
        for (int i = 0; i < table.size(); ++i) {
            if (table[i].state != CellType::Empty)
                cout << i+1 << ". " << ((static_cast<int>(table[i].state) == 1) ? "key: " : "del: ") << table[i].key << " " << endl;
            else
                cout << i+1 << ". " << 0 << endl;
        }
        cout << endl;
    }

private:
    HashTable(size_t size): table(size), items_count(0) {}
    void grow_table() {
        size_t new_size = (table.size() == 0) ? start_size : table.size() * 2;
        HashTable new_table(new_size);
        for (int i = 0; i < table.size(); ++i) {
            if (table[i].state == CellType::Key) {
                new_table.insert(table[i].key);
            }
        }
        table.resize(new_size);
        for (int i = 0; i < table.size(); ++i) {
            table[i].state = new_table.table[i].state;
            if (table[i].state == CellType::Key) {
                table[i].key = new_table.table[i].key;
            }
        }
    }

    vector<HashTableNode> table;
    size_t items_count;
    H1 hasher1;
    H2 hasher2;
};


int main() {
    Hash1 hasher1;
    Hash2 hasher2;
    HashTable<string, Hash1, Hash2> many_lines(hasher1, hasher2);

    char cmd;
    string key;
    bool res = false;

    while (cin >> cmd >> key) {
        switch (cmd) {
            case '+':
                res = many_lines.insert(key);
                break;
            case '-':
                res = many_lines.erase(key);
                break;
            case '?':
                res = many_lines.find(key);
                break;
            default:
                return 0;
        }

        cout << ((res) ? "OK" : "FAIL") << endl;
    }

    return 0;
}
