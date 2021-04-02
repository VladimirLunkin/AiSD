#include <iostream>

using namespace std;

template <class T>
class Stack {
    struct Node {
        T value;
        Node *next;

        explicit Node(const T &val) : value(val), next(nullptr) {}
    };
public:
    Stack() : top(nullptr) {}
    ~Stack() {
        while (!is_empty()) {
            pop();
        }
    }

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    Stack(Stack&&) = delete;
    Stack& operator=(Stack&&) = delete;

    void push(const T &elem) {
        Node *node = new Node(elem);
        node->next = top;
        top = node;
    }
    T pop() {
        if (is_empty()) {
            return -1;
        }

        T val = top->value;

        Node *node = top;
        top = top->next;
        delete node;

        return val;
    }
    bool is_empty() const {
        return top == nullptr;
    }

    T get_top() {
        if (is_empty()) {
            return -1;
        }

        return top->value;
    }

private:
    Node *top;
};


bool is_stack_anagram(const string& line1, const string& line2) {
    if (line1.length() != line2.length()) {
        return false;
    }

    Stack<char> stack;

    string anagram;
    for (int i = 0, j = 0; i < line1.length(); ++i) {
        if (line1[i] == line2[j]) {
            anagram += line1[i];
            j++;
        } else {
            stack.push(line1[i]);
        }
        while (line2[j] == stack.get_top()) {
                anagram += stack.pop();
                j++;
        }
    }
    while (!stack.is_empty()) {
        anagram += stack.pop();
    }

    return line2 == anagram;
}

int main() {
    string line1;
    cin >> line1;

    string line2;
    cin >> line2;

    cout << (is_stack_anagram(line1, line2) ? "YES" : "NO") << endl;

    return 0;
}
