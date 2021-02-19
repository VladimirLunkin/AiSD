#include <iostream>
#include <stack>
#include <queue>
#include <assert.h>

using namespace std;


template <class T>
struct DefaultComparator {
    int operator()(const T& lhs, const T&rhs) {
        if (lhs > rhs) {
            return -1;
        }
        else if (lhs == rhs) {
            return 0;
        }
        return 1;
    }
};

template <class Key, class Comparator = DefaultComparator<Key>>
class AVLTree {
    struct Node {
        Node* left;
        Node* right;

        Key key;

        uint8_t height;
        int weight;

        Node(const Key& _key) : left(nullptr), right(nullptr), key(_key), height(1), weight(1) {}
    };
public:
    AVLTree(Comparator _comp = Comparator()) : root(nullptr), comp(_comp) {}
    ~AVLTree() {
        delete root;
    }

    void insert(const Key& key) {
        root = insert_aux(key, root);
    }
    Key operator[](const int& ind) {
        assert(root != nullptr && root->weight > ind);
        return find_aux(ind, root);
    }
    void del(const Key& key) {
        root = del_aux(key, root);
    }

    void TraverseBFS() {
        cout << "Size: " << get_size() << "\tHeight: " << (int)get_height() << endl;
        if (root == nullptr) {
            return;
        }
        queue<Node*> row;
        row.push(root);
        int pop_num = 0;            // счетчик просмотренных элементов в слое
        int push_num = 0;           // считаем количество элементов в следующем слое
        int quantity_in_layer = 1;  // количество элементов в текущем слое

        while (!row.empty()) {
            Node* current = row.front();
            row.pop();
            pop_num++;

            if (current->left != nullptr) {
                row.push(current->left);
                push_num++;
            }
            if (current->right != nullptr) {
                row.push(current->right);
                push_num++;
            }

            cout << current->key << "_" << current->weight << " ";
            if (pop_num == quantity_in_layer) { // если просмотрели все элементы слоя
                cout << endl;
                quantity_in_layer = push_num;
                push_num = 0;
                pop_num = 0;
            }
        }
    }
    int get_size() {
        if (root == nullptr) {
            return 0;
        }
        return root->weight;
    }
    uint8_t get_height() {
        return height(root);
    }

private:
    Node* insert_aux(const Key& key, Node* current) {
        if (current == nullptr) {
            return new Node(key);
        }

        int res = comp(key, current->key);
        if (res == 1) {
            current->left = insert_aux(key, current->left);
        } else if (res == -1) {
            current->right = insert_aux(key, current->right);
        }

        return balance(current);
    }
    Key find_aux(const int& ind, Node* current) {
        int left_weight = (current->left == nullptr) ? 0 : current->left->weight;

        if (ind == left_weight) {
            return current->key;
        }
        if (ind < left_weight) {
            return find_aux(ind, current->left);
        }
        return find_aux(ind - left_weight - 1, current->right);
    }
    Node* del_aux(const Key& key, Node* current) {
        if (current == nullptr) {
            return nullptr;
        }

        int res = comp(key, current->key);
        if (res == 1) {
            current->left = del_aux(key, current->left);
        } else if (res == -1) {
            current->right = del_aux(key, current->right);
        }
        else {
            Node* left = current->left;
            Node* right = current->right;

            delete current;

            if (right == nullptr) {
                return left;
            }

            Node* min_node = find_and_remove_min(right);
            min_node->left = left;

            return balance(min_node);
        }

        return balance(current);
    }
    Node* find_and_remove_min(Node* right) {
        Node* parent = nullptr;
        Node* current = right;
        stack<Node*> nodes;
        while (current->left != nullptr) {
            parent = current;
            current = current->left;
            nodes.push(parent);
        }

        if (parent != nullptr) {
            parent->left = current->right;
            current->right = right;

            Node* current_balance = nodes.top();
            nodes.pop();
            while (!nodes.empty()) {
                Node* parent_balance = nodes.top();
                nodes.pop();
                parent_balance->left = balance(current_balance);
                current_balance = parent_balance;
            }
            current->right = balance(current->right);
        }

        return current;
    }

    uint8_t height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
    void fix_height(Node* node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }
    int8_t bfactor(Node* node) {
        return height(node->right) - height(node->left);
    }

    int weight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->weight;
    }
    int fix_weight(Node* node) {
        node->weight = weight(node->left) + weight(node->right) + 1;
    }

    Node* balance(Node* node) {
        fix_height(node);
        fix_weight(node);

        int8_t bf = bfactor(node);
        if (bf == 2) {
            if (bfactor(node->right) < 0) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        }
        else if (bf == -2) {
            if (bfactor(node->left) > 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        return node;
    }

    Node* rotate_left(Node* a) {
        Node* b = a->right;
        a->right = b->left;
        b->left = a;

        fix_height(a);
        fix_height(b);

        fix_weight(a);
        fix_weight(b);

        return b;
    }
    Node* rotate_right(Node* a) {
        Node* b = a->left;
        a->left = b->right;
        b->right = a;

        fix_height(a);
        fix_height(b);

        fix_weight(a);
        fix_weight(b);

        return b;
    }

    Node* root;
    Comparator comp;

};

typedef void (*Tests)();

void test1() {
    DefaultComparator<int> comp;
    AVLTree<int, DefaultComparator<int>> tree(comp);

    for (int i = 0; i < 15; ++i) {
        tree.insert(i);
    }

    tree.TraverseBFS();
    for (int i = 0; i < tree.get_size(); ++i) {
        cout << tree[i] << " ";
    } cout << endl;

    tree.del(7);
    tree.del(14);
    tree.del(2);
    tree.del(5);
    tree.TraverseBFS();

    for (int i = 0; i < tree.get_size(); ++i) {
        cout << tree[i] << " ";
    } cout << endl;


    for (int i = 0; i < tree.get_size() - 4; ++i) {
        cout << "Delete: " << tree[0] << endl;
        tree.del(tree[0]);
    }
    tree.TraverseBFS();
}
void test2() {
    DefaultComparator<int> comp;
    AVLTree<int, DefaultComparator<int>> tree(comp);

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(20);
    tree.insert(21);
    tree.insert(25);
    tree.insert(14);

    tree.TraverseBFS();
    cout << endl;

    while (tree.get_size()) {
        cout << "Delete: " << tree[0] << endl;
        tree.del(tree[0]);
    }
    tree.TraverseBFS();

}
void test3() {
    DefaultComparator<int> comp;
    AVLTree<int, DefaultComparator<int>> tree(comp);

    tree.insert(5);
    tree.insert(3);
    tree.insert(1);
    tree.insert(9);
    tree.insert(7);
    tree.insert(10);
    tree.insert(6);

    tree.TraverseBFS();
    tree.del(1);
    tree.TraverseBFS();
}
void test4() {
    DefaultComparator<int> comp;
    AVLTree<int, DefaultComparator<int>> tree(comp);

    tree.insert(3);
    tree.insert(1);
    tree.insert(2);
    tree.insert(0);

    tree.TraverseBFS();
}
void test5() {
    DefaultComparator<int> comp;
    AVLTree<int, DefaultComparator<int>> tree(comp);

    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    tree.insert(2);

    tree.TraverseBFS();
}
void test6() {
    DefaultComparator<int> comp;
    AVLTree<int, DefaultComparator<int>> tree(comp);

    tree.insert(1);
    tree.insert(1);
    tree.insert(4);
    tree.insert(2);
    tree.insert(4);

    tree.TraverseBFS();
}


int main() {
//    Tests tests[] = {test1, test2, test3, test4, test5, test6};
//
//    for (int i = 0; i < 6; ++i) {
//        tests[i]();
//        cout << "test" << i + 1 << " - OK" << endl << endl;
//    }

    int n;
    cin >> n;

    DefaultComparator<int> comp;
    AVLTree<int, DefaultComparator<int>> tree(comp);

    for (int i = 0; i < n; ++i) {
        int key, index;
        cin >> key >> index;

        if (key >= 0) {
            tree.insert(key);
        } else {
            tree.del(-key);
        }

        cout << tree[index] << endl;
    }

    return 0;
}
