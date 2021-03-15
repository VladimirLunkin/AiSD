#include <iostream>
#include <cassert>

using namespace std;


template <class T>
struct DefaultComparator {
    bool operator()(const T &l, const T &r) {
        return l < r;
    }
};

template <class T, class Comparator = DefaultComparator<T>>
class Heap {
public:
    Heap() : size(0), capacity(0), arr(nullptr), comp(Comparator()) {}
    explicit Heap(Comparator _comp)
            : size(0), capacity(0), arr(nullptr), comp(_comp) {}
    Heap(ssize_t _capacity, Comparator _comp = Comparator())
            : size(0), capacity(_capacity), comp(_comp) {
        arr = new T[capacity];
    }
    ~Heap() {
        delete[] arr;
    }

    void insert(T element) {
        if (size == capacity) {
            resize((capacity == 0) ? 1 : 2 * capacity);
        }

        arr[size] = element;
        sift_up(size);
        size++;
    }
    T extract_min() {
        assert(size != 0);

        T result = arr[0];

        arr[0] = arr[size - 1];
        size--;

        if (size != 0) {
            sift_down(0);
        }

        return result;
    }
    T peek_min() const {
        return arr[0];
    }
    ssize_t get_size() {
        return size;
    }

private:
    void build_heap() {
        for (int i = size / 2 - 1; i >= 0; --i) {
            sift_down(i);
        }
    }
    void sift_down(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        int least = i;
        if (left < size && comp(arr[left], arr[i]))
            least = left;
        if (right < size && comp(arr[right], arr[least]))
            least = right;

        if (least != i) {
            std::swap(arr[i], arr[least]);
            sift_down(least);
        }
    }
    void sift_up(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (!comp(arr[i], arr[parent])) {
                return;
            }
            std::swap(arr[i], arr[parent]);
            i = parent;
        }
    }
    void resize(ssize_t _capacity) {
        capacity = _capacity;
        T *new_arr = new T[capacity];

        for (int i = 0; i < size; ++i) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
    }

    T *arr;
    ssize_t size;
    ssize_t capacity;

    Comparator comp;
};


template <class T1, class T2>
struct PairComparator {
    bool operator()(const pair<T1, T2> &l, const pair<T1, T2> &r) {
        return l.second < r.second;
    }
};


int main() {
    int n;
    cin >> n;

    PairComparator<int, int> comp;
    Heap<pair<int, int>, PairComparator<int, int>> arr(comp);

    ssize_t m = 0;
    pair<int, int> train;
    for (int i = 0; i < n; ++i) {
        cin >> train.first >> train.second;

        while (arr.get_size() != 0 && train.first > arr.peek_min().second) {
            arr.extract_min();
        }

        arr.insert(train);
        m = (m > arr.get_size()) ? m : arr.get_size();
    }

    cout << m << endl;
}
