#include <iostream>
#include <queue>
#include <stack>


using namespace std;


template <class T>
class Comparator {
public:
    int operator()(const T& lhs, const T& rhs) {
        if (lhs == rhs) {
            return 0;
        }
        if (lhs < rhs) {
            return 1;
        }
        return -1;
    }
};

template <class T, class Comparator>
class CartesianTree {
    struct Node {
        T key;
        int priority;
        Node* left;
        Node* right;

        Node(const T& _key, const int& _priority): key(_key), priority(_priority), left(nullptr), right(nullptr) {}
    };

public:
    explicit CartesianTree(Comparator _comp): root(nullptr), comp(_comp) {}
    CartesianTree(const CartesianTree&) = delete;
    CartesianTree& operator=(const CartesianTree&) = delete;
    ~CartesianTree() {
        if (root == nullptr) {
            return;
        }
        stack<Node*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            Node* current = nodes.top();

            if (current->left == nullptr && current->right == nullptr) {
                nodes.pop();
                delete current;
                continue;
            }

            if (current->left != nullptr) {
                nodes.push(current->left);
                current->left = nullptr;
            }
            if (current->right != nullptr) {
                nodes.push(current->right);
                current->right = nullptr;
            }
        }
    }

    void insert(const T& key, const int& priority) {
        Node* new_node = new Node(key, priority);

        if (root == nullptr) {
            root = new_node;
            return;
        }

        Node* parent = nullptr;
        Node* current = root;
        while (current != nullptr && current->priority > priority) {
            parent = current;
            if (comp(key, current->key) == 1) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        split(current, key, new_node->left, new_node->right);
        if (root->priority < priority) {
            root = new_node;
        } else {
            ((parent->left == current) ? parent->left : parent->right) = new_node;
        }
    }
    /*void insert(const T& key, const int& priority) {
        Node* current = root;
        Node* new_node = new Node(key, priority);
        while (current != nullptr && current->priority > priority) {
            if (comp(key, current->key) == 1) {
                if (current->left == nullptr || current->left->priority > priority) {
                    split((current->left), key, new_node->left, new_node->right);
                    current->left = new_node;
                    return;
                }
                current = current->left;
            } else {
                if (current->right == nullptr || current->left->priority > priority) {
                    split((current->right), key, new_node->left, new_node->right);
                    current->right = new_node;
                    return;
                }
                current = current->right;
            }
        }

        split(current, key, new_node->left, new_node->right);
        root = new_node;
    }*/

    void TraverseBFS() {
        if (root == nullptr) {
            return;
        }
        queue<Node*> row;
        row.push(root);
        int pop_count = 0, s = 1, push_count = 0;
        while (!row.empty()) {
            Node* current = row.front();
            row.pop();

            pop_count++;

            cout << current->key << " ";

            if (current->left != nullptr) {
                row.push(current->left);
                push_count++;
            }
            if (current->right != nullptr) {
                row.push(current->right);
                push_count++;
            }

            if (pop_count == s) {
                cout << endl;
                s = push_count;
                push_count = 0;
                pop_count = 0;
            }
        }
    }
    int depth_bfs() {
        if (root == nullptr) {
            return 0;
        }
        queue<Node*> row;
        row.push(root);

        int depth = 0;              // прошли слой увеличили счетчик глубины
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

            if (pop_num == quantity_in_layer) { // если просмотрели все элементы слоя
                depth++;
                quantity_in_layer = push_num;
                push_num = 0;
                pop_num = 0;
            }
        }

        return depth;
    }

private:
    void split(Node* current, const T& key, Node*& left, Node*& right) {
        if (current == nullptr) {
            left = nullptr;
            right = nullptr;
        }
        else if (comp(key, current->key) == 1) {
            split(current->left, key, left, current->left);
            right = current;
        }
        else {
            split(current->right, key, current->right, right);
            left = current;
        }
    }
    Node* merge(Node* left, Node* right) {
        if (left == nullptr || right == nullptr) {
            return (left == nullptr) ? right : left;
        }
        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            return left;
        }
        else {
            right->left = merge(left, right->left);
            return right;
        }
    }

    Node* root;
    Comparator comp;

};

template <class T, class Comparator>
class Tree {
    struct Node {
        T key;
        Node* left;
        Node* right;

        Node(const T& _key): key(_key), left(nullptr), right(nullptr) {}
    };

public:
    explicit Tree(Comparator _comp): root(nullptr), comp(_comp) {}
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;
    ~Tree() {
        if (root == nullptr) {
            return;
        }
        stack<Node*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            Node* current = nodes.top();

            if (current->left == nullptr && current->right == nullptr) {
                nodes.pop();
                delete current;
                continue;
            }

            if (current->left != nullptr) {
                nodes.push(current->left);
                current->left = nullptr;
            }
            if (current->right != nullptr) {
                nodes.push(current->right);
                current->right = nullptr;
            }
        }
    }

    void insert(const T& key) {
        Node* new_node = new Node(key);
        Node* current = root;
        while (current != nullptr) {
            if (comp(key, current->key) == 1) {
                if (current->left == nullptr) {
                    current->left = new_node;
                    return;
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = new_node;
                    return;
                }
                current = current->right;
            }
        }

        root = new_node;
    }

    int depth_bfs() {
        if (root == nullptr) {
            return 0;
        }
        queue<Node*> row;
        row.push(root);

        int depth = 0;              // прошли слой увеличили счетчик глубины
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

            if (pop_num == quantity_in_layer) { // если просмотрели все элементы слоя
                depth++;
                quantity_in_layer = push_num;
                push_num = 0;
                pop_num = 0;
            }
        }

        return depth;
    }

private:
    Node* root;
    Comparator comp;

};


typedef void (*Tests)();

void test1() {
    Comparator<int> comp;
    Tree<int, Comparator<int>> tree(comp);
    CartesianTree<int, Comparator<int>> ctree(comp);

    ctree.insert(5, 11);
    ctree.insert(18, 8);
    ctree.insert(25, 7);
    ctree.insert(50, 12);
    ctree.insert(30, 30);
    ctree.insert(15, 15);
    ctree.insert(20, 10);
    ctree.insert(22, 5);
    ctree.insert(40, 20);
    ctree.insert(45, 9);

    cout << "Высота декартового дерева: " << ctree.depth_bfs() << endl;
    ctree.TraverseBFS();
    cout << endl;

    tree.insert(5);
    tree.insert(18);
    tree.insert(25);
    tree.insert(50);
    tree.insert(30);
    tree.insert(15);
    tree.insert(20);
    tree.insert(22);
    tree.insert(40);
    tree.insert(45);

    cout << "Высота бинарного дерева поиска: " << tree.depth_bfs() << endl;
}

void test2() {
    Comparator<int> comp;
    CartesianTree<int, Comparator<int>> tree(comp);

    tree.insert(38, 19);
    tree.insert(37, 5);
    tree.insert(47, 15);
    tree.insert(35, 0);
    tree.insert(12, 3);
    tree.insert(0, 42);
    tree.insert(31, 37);
    tree.insert(21, 45);
    tree.insert(30, 26);
    tree.insert(41, 6);

    tree.TraverseBFS();
    cout << endl;
}
/*
void test3() {
    Comparator<int> comp;
    Tree<int, Comparator<int>> tree(comp);

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    tree.TraverseBFS();
    cout << endl;
}

void test4() {
    Comparator<int> comp;
    Tree<int, Comparator<int>> tree(comp);

    tree.insert(3);
    tree.insert(1);
    tree.insert(2);

    tree.TraverseBFS();
    cout << endl;
}

void test5() {
    Comparator<int> comp;
    Tree<int, Comparator<int>> tree(comp);

    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    tree.insert(2);

    tree.TraverseBFS();
    cout << endl;
}

void test6() {
    Comparator<int> comp;
    Tree<int, Comparator<int>> tree(comp);

    tree.insert(1);
    tree.insert(1);
    tree.insert(4);
    tree.insert(2);
    tree.insert(4);

    tree.TraverseBFS();
    cout << endl;
}
*/

int main() {
//    Tests tests[] = {test1, test2};//, test3, test4, test5, test6};
//
//    for (int i = 0; i < 1; ++i) {
//        tests[i]();
//        cout << "test" << i + 1 << " - OK" << endl;
//    }

    int n;
    cin >> n;

    Comparator<int> comp;
    Tree<int, Comparator<int>> tree(comp);
    CartesianTree<int, Comparator<int>> ctree(comp);

    for (int i = 0; i < n; ++i) {
        int key, priority;
        cin >> key >> priority;
        tree.insert(key);
        ctree.insert(key, priority);
    }

    cout << tree.depth_bfs() - ctree.depth_bfs() << endl;

    return 0;
}
