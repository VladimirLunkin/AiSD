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

    void push(const T &elem) {
        Node *node = new Node(elem);
        if (is_empty()) {
            head = current = tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    }
    void pop() {
        Node *node = head;
        if (head == current) {
            current = head->next;
        }
        head = head->next;

        if (head == nullptr || head == tail) {
            head = nullptr;
            tail = nullptr;
            current = nullptr;
        }

        delete node;
    }
    void pop_next() {
        if (current->next == head) {
            pop();
            return;
        }

        Node *node = current->next;
        if (node == tail || node == nullptr) {
            current->next = nullptr;
            tail = current;
        } else {
            current->next = current->next->next;
        }
        delete node;
    }
    T& top() {
        return head->value;
    }
    T& next_elem() {
        if (current->next == nullptr) {
            return current->value;
        }
        return current->next->value;
    }
    void shift() {
        if (current->next != nullptr) {
            current = current->next;
        }
    }
    bool is_empty() const {
        return head == tail && head == nullptr;
    }
    void ring() {
        tail->next = head;
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
    a.ring();
    for (int j = 0; j < k - 2; ++j) {
        a.shift();
    }

    for (int i = 0; i < n - 1; ++i) {
        a.pop_next();
        a.ring();
        for (int j = 0; j < k - 1; ++j) {
            a.shift();
        }
    }
    cout << "";
    return a.top();
}

int main() {
    int n = 0;
    int k = 0;
    cin >> n >> k;

    cout << counting(n, k) << endl;

    return 0;
}
