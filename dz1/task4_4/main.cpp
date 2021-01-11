#include <iostream>
#include <assert.h>

using namespace std;

template <class T>
bool is_less(const T& l, const T& r) {
    return l > r;
}

template <class T>
class Heap {
public:
    Heap() : size(0), capacity(10) {
        arr = new T[capacity];
    }
    ~Heap() {
        delete[] arr;
    }

    void insert(T element, bool (*comp)(const T& l, const T& r)) {
        if (size == capacity) {
            resize();
        }

        arr[size] = element;
        sift_up(size, comp);
        size++;
    }
    T extract_max(bool (*comp)(const T& l, const T& r)) {
        assert(size != 0);

        T result = arr[0];

        arr[0] = arr[size - 1];
        size--;

        if (size != 0) {
            sift_down(0, comp);
        }

        return result;
    }

    T peek_max() const {
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
    void sift_down(int i, bool (*comp)(const T& l, const T& r)) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        int least = i;
        if (left < size && comp(arr[left], arr[i]))
            least = left;
        if (right < size && comp(arr[right], arr[least]))
            least = right;

        if (least != i) {
            std::swap(arr[i], arr[least]);
            sift_down(least, comp);
        }
    }
    void sift_up(int i, bool (*comp)(const T& l, const T& r)) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (!comp(arr[i], arr[parent])) {
                return;
            }
            std::swap(arr[i], arr[parent]);
            i = parent;
        }
    }
    void resize() {
        capacity *= 2;
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
};

void Moving_high(pair<int, int> *data, int n, int k) {
    Heap<pair<int, int>> arr;
    for (int i = 0; i < k; ++i) {
        arr.insert(data[i], is_less);
    }
    cout << arr.peek_max().first << " ";

    for (int i = k; i < n; ++i) {
        arr.insert(data[i], is_less);
        while (i - arr.peek_max().second >= k) {
            arr.extract_max(is_less);
        }
        cout << arr.peek_max().first << " ";
    }
    cout << endl;
}

void test1() {
    int n = 5;
    int data1[] = {5, 2, 3, 4, 6};
    int k = 1;
    pair<int, int> data[n];

    for (int i = 0; i < n; ++i) {
        data[i].first = data1[i];
        data[i].second = i;
    }

    Moving_high(data, n, k);
}
void test2() {
    int n = 10;
    int data1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 5;
    pair<int, int> data[n];

    for (int i = 0; i < n; ++i) {
        data[i].first = data1[i];
        data[i].second = i;
    }

    Moving_high(data, n, k);
}
void test3() {
    int n = 5;
    int data1[] = {7, 2, 3, 1, 5};
    int k = 4;
    pair<int, int> data[n];

    for (int i = 0; i < n; ++i) {
        data[i].first = data1[i];
        data[i].second = i;
    }

    Moving_high(data, n, k);
}
void test4() {
    int n = 9;
    int data1[] = {0, 7, 3, 8, 4, 5, 10, 4, 6};
    int k = 4;
    pair<int, int> data[n];

    for (int i = 0; i < n; ++i) {
        data[i].first = data1[i];
        data[i].second = i;
    }

    Moving_high(data, n, k);
}
void test5() {
    int n = 9;
    int data1[] = {0, 7, 3, 8, 4, 5, 10, 4, 6};
    int k = 9;
    pair<int, int> data[n];

    for (int i = 0; i < n; ++i) {
        data[i].first = data1[i];
        data[i].second = i;
    }

    Moving_high(data, n, k);
}
void test6() {
    int n = 6;
    int data1[] = {7, 7, 3, 8, 4, 5, 10, 4, 6};
    int k = 2;
    pair<int, int> data[n];

    for (int i = 0; i < n; ++i) {
        data[i].first = data1[i];
        data[i].second = i;
    }

    Moving_high(data, n, k);
}


int main() {
    /*int n;
    cin >> n;
    pair<int, int> data[n];
    for (int i = 0; i < n; ++i) {
        cin >> data[i].first;
        data[i].second = i;
    }
    int k;
    cin >> k;

    Moving_high(data, n, k);*/

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();

    return 0;
}
