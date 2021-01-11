#include <iostream>

using namespace std;


template <class T>
class Queue {
    struct Node {
        T value;
        Node *next;

        Node(const T &val) : value(val), next(nullptr) {}
    };
public:
    Queue() : head(nullptr), tail(nullptr), current(nullptr) {}
    ~Queue() {
        while (!is_empty()) {
            pop();
        }
    }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    Queue(Queue&&) = delete;
    Queue& operator=(Queue&&) = delete;

    bool is_empty() const {
        return head == tail && head == nullptr;
    }
    void push(const T &elem) {
        Node *node = new Node(elem);
        if (is_empty()) {
            head = current = tail = node;
            return;
        }
        tail->next = node;
        tail = node;
        tail->next = head;  // закольцевать список
    }
    void pop() {
        if (is_empty()) {
            return;
        }

        Node *node = head;
        if (head != head->next) {
            head = head->next;
            tail->next = head;
            if (current == head) {
                current = head;
            }
        } else {
            head = nullptr;
            current = head;
            tail = head;
        }

        delete node;
    }
    void pop_next() {
        if (current->next == head) {
            pop();
            return;
        }

        Node *node = current->next;
        if (node == tail) {
            current->next = head;
            tail = current;
        } else {
            current->next = current->next->next;
        }

        delete node;
    }
    T& top() {
        return head->value;
    }
    void shift() {
        if (current->next != nullptr) {
            current = current->next;
        }
    }
private:
    Node *head;
    Node *tail;
    Node *current;
};

int counting(const int n, int k) {
    Queue<int> a;
    for (int i = 1; i <= n; ++i) {
        a.push(i);
    }
    for (int j = 0; j < k - 2; ++j) {
        a.shift();
    }

    for (int i = 0; i < n - 1; ++i) {
        a.pop_next();
        for (int j = 0; j < k - 1; ++j) {
            a.shift();
        }
    }
    return a.top();
}

int main() {
    int n = 0;
    int k = 0;
    cin >> n >> k;

    cout << counting(n, k) << endl;

    return 0;
}
