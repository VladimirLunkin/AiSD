#include <iostream>
#include <assert.h>

using namespace std;


template <class T>
struct is_less {
    bool operator()(const T &l, const T &r) {
        return l > r;
    }
};
//bool is_less(const int &l, const int &r) {
//    return l < r;
//}

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
    Heap(ssize_t _capacity, Comparator _comp = Comparator()) : size(0), capacity(_capacity), comp(_comp) {
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
//    bool (*comp)(const T &l, const T &r);
};

int fast_sum(Heap<int, is_less<int>> &arr) {
    int sum = 0;

    while (arr.get_size() > 1) {
        int tmp = arr.extract_min() + arr.extract_min();
        arr.insert(tmp);
        sum += tmp;
    }

    return sum;
}

//void test1() {
//    int size = 5;
//    int element[] = {5, 2, 3, 4, 6};
//    int ans = 45;
//
//    Heap<int> arr;
//    for (int i = 0; i < size; ++i) {
//        arr.insert(element[i]);
//    }
//    assert(ans == fast_sum(arr));
//}
//void test2() {
//    int size = 5;
//    int element[] = {3, 7, 6, 1, 9};
//    int ans = 56;
//
//    Heap<int> arr;
//    for (int i = 0; i < size; ++i) {
//        arr.insert(element[i]);
//    }
//    assert(ans == fast_sum(arr));
//}
//void test3() {
//    int size = 3;
//    int element[] = {3, 2, 1};
//    int ans = 9;
//
//    Heap<int> arr;
//    for (int i = 0; i < size; ++i) {
//        arr.insert(element[i]);
//    }
//    assert(ans == fast_sum(arr));
//}
//void test4() {
//    int size = 4;
//    int element[] = {5, 3, 1, 4};
//    int ans = 25;
//
//    Heap<int> arr;
//    for (int i = 0; i < size; ++i) {
//        arr.insert(element[i]);
//    }
//    assert(ans == fast_sum(arr));
//}
//void test5() {
//    int size = 3;
//    int element[] = {3, 2, 1};
//    int ans = 9;
//
//    Heap<int> arr;
//    for (int i = 0; i < size; ++i) {
//        arr.insert(element[i]);
//    }
//    assert(ans == fast_sum(arr));
//}


int main() {
    int size;
    cin >> size;

    Heap<int, is_less<int>> arr(0, is_less<int>());
    for (int i = 0; i < size; ++i) {
        int element;
        cin >> element;
        arr.insert(element);
    }

    cout << fast_sum(arr) << endl;
//    test1();
//    cout << "test1 - OK" << endl;
//    test2();
//    cout << "test2 - OK" << endl;
//    test3();
//    cout << "test3 - OK" << endl;
//    test4();
//    cout << "test4 - OK" << endl;
//    test5();
//    cout << "test5 - OK" << endl;
    return 0;
}
