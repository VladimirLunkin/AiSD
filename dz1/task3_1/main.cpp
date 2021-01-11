#include <iostream>


using namespace std;

template <class T>
class Arr {
public:
    Arr() : start(0), size(0), capacity(0), arr(nullptr) {}
    Arr(int _capacity) : start(0), size(0), capacity(_capacity) {
        arr = new T[capacity];
    }
    ~Arr() {
        delete [] arr;
    }

    void push_back(T element) {
        if (capacity == size) {
            resize((capacity == 0) ? 1 : 2 * capacity);
        }
        arr[(start + size++) % capacity] = element;
    }
    T pop_front() {
        if (size == 0) {
            return -1;
        }

        size--;

        T tmp = arr[start];
        (++start) %= capacity;

        if (size < capacity / 2) {
            resize(capacity / 2);
        }
        return tmp;
    }
    int get_size() {
        return size;
    }
    T *data() {
        return arr;
    }
    T &operator[](int index) {
        if (index < 0) {
            index += size;
        }
        return arr[(start + index) % capacity];
    }
private:
    void resize(int _capacity) {
        if (_capacity < size) {
            size = _capacity;
        }
        T *new_arr = new T[_capacity];

        for (int i = 0; i < size; ++i) {
            new_arr[i] = arr[(start + i) % capacity];
        }

        delete[] arr;
        arr = new_arr;
        start = 0;
        capacity = _capacity;
    }

    T *arr;
    int start;
    int size;
    int capacity;
};

template <class T>
class Queue {
    struct Node {
        T value;
        Node *next;

        Node(const T &val) : value(val), next(nullptr) {}
    };
public:
    Queue() : head(nullptr), tail(nullptr) {}
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
            head = tail = node;
            ring();
            return;
        }
        tail->next = node;
        tail = node;
        ring();
    }
    T pop() {
        if (is_empty()) {
            return -1;
        }

        Node *node = head;
        T val = head->value;

        if (head == head->next) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            ring();
        }

        delete node;

        return val;
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
};

enum COMMAND {
    POP_FRONT = 2,
    PUSH_BACK,
};

bool test_queue() {
    int num;
    cin >> num;

    Arr<int> arr;
    bool f = true;

    for (int i = 0; i < num; ++i) {
        int command;
        int val;
        cin >> command >> val;

        switch (command) {
            case POP_FRONT:
                f = f && (val == arr.pop_front());
                break;
            case PUSH_BACK:
                arr.push_back(val);
                break;
            default:
                return f;
        }
    }

    return f;
}

int main() {
    Arr<int> arr;
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);
    arr.push_back(6);
    arr.push_back(7);
    cout << arr[-3] << "\n";
    for (int i = 0; i < arr.get_size(); ++i) {
        cout << arr[i] << " ";
    } cout << endl;

    arr.pop_front();
    arr.pop_front();
    for (int i = 0; i < arr.get_size(); ++i) {
        cout << arr[i] << " ";
    } cout << endl;
    arr.push_back(8);
    arr.push_back(9);
    arr.push_back(10);
    for (int i = 0; i < arr.get_size(); ++i) {
        cout << arr[i] << " ";
    } cout << endl;

    arr.pop_front();
    arr.pop_front();
    arr.pop_front();
    arr.pop_front();
    for (int i = 0; i < arr.get_size(); ++i) {
        cout << arr[i] << " ";
    } cout << endl;
    arr.push_back(11);
    arr.push_back(12);
    arr.push_back(13);
    arr.push_back(14);
    arr.push_back(15);
    for (int i = 0; i < arr.get_size(); ++i) {
        cout << arr[i] << " ";
    } cout << endl;
    cout << arr[-3] << "\n";

   cout << (2 - 5) % 10;

    if (test_queue()) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}

//10
//2 -1
//3 1
//2 1
//2 -1
//3 1
//3 2
//3 3
//2 1
//2 2
//2 3