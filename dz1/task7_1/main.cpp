#include <iostream>
#include <string>
#include <vector>

static const int alphabet_size(256);

template <class T>
class Arr {
public:
    Arr() : size(0), capacity(0), arr(nullptr) {}
    Arr(int _capacity) : size(0), capacity(_capacity) {
        arr = new T[capacity];
    }
    ~Arr() {
        delete [] arr;
    }

    void push(T element) {
        if (capacity == size) {
            resize((capacity == 0) ? 1 : 2 * capacity);
        }
        arr[size++] = element;
    }
    void pop() {
        size--;

        if (size < capacity / 2) {
            resize(capacity / 2);
        }
    }
    int get_size() {
        return size;
    }
    T *data() {
        return arr;
    }
    T &operator[](int index) {
        if (index < capacity && index >= size) {
            size = index + 1;
        }
        return arr[index];
    }
private:
    void resize(int _capacity) {
        capacity = _capacity;
        T *new_arr = new T[capacity];

        for (int i = 0; i < size; ++i) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
    }

    T *arr;
    int size;
    int capacity;
};

template <class T>
void msd_sort(T *arr, int size, int i_symbol = 0) {
    int counters[alphabet_size];
    int counters_group[alphabet_size];

    for (int i = 0; i < alphabet_size; ++i) {
        counters[i] = 0;
        counters_group[i] = 0;
    }

    for (int i = 0; i < size; ++i) {
        int index = static_cast<int>(arr[i][i_symbol]);
        if (arr[i][i_symbol] == '\0') {
            index = 0;
        }
        counters[index]++;
        counters_group[index]++;
    }

    for (int i = 1; i < alphabet_size; ++i) {
        counters[i] += counters[i - 1];
    }

    T *new_arr = new T[size];
    for (int i = size - 1; i >= 0; --i) {
        int index = static_cast<int>(arr[i][i_symbol]);
        if (arr[i][i_symbol] == '\0') {
            index = 0;
        }
        new_arr[--counters[index]] = arr[i];
    }

    for (int i = 0; i < size; ++i) {
        arr[i] = new_arr[i];
    }

    delete [] new_arr;

    int start = 0;
    for (int i = 0; i < alphabet_size - 1; ++i) {
        if (counters_group[i] > 1 && (arr + start)[0][i_symbol] != '\0') {
            std::cout << counters_group[i] << (arr + start)[0][i_symbol + 1] << '\n';
            msd_sort(arr + start, counters_group[i], i_symbol + 1);
        }
        start += counters_group[i];
    }
}

void test() {
    std::string s[] = {"a", "a", "a", "a"};
    Arr<std::string> arr(4);
    for (int i = 0; i < 4; ++i) {
        arr[i] = s[i];
    }

    msd_sort(arr.data(), arr.get_size());

    for (int i = 0; i < arr.get_size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}
void test1() {
    std::string s[] = {"f", "g", "ag", "a"};
    Arr<std::string> arr(4);
    for (int i = 0; i < 4; ++i) {
        arr[i] = s[i];
    }

    msd_sort(arr.data(), arr.get_size());

    for (int i = 0; i < arr.get_size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}
void test3() {
    std::string s[] = {"aaaa", "aaa", "aa", "a"};
    Arr<std::string> arr(4);
    for (int i = 0; i < 4; ++i) {
        arr[i] = s[i];
    }

    msd_sort(arr.data(), arr.get_size());

    for (int i = 0; i < arr.get_size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}
void test4() {
    std::string s[] = {"ag", "ag0", "ag", "a"};
    Arr<std::string> arr(4);
    for (int i = 0; i < 4; ++i) {
        arr[i] = s[i];
    }

    msd_sort(arr.data(), arr.get_size());

    for (int i = 0; i < arr.get_size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}
void test5() {
    std::string s[] = {"ag", "ag6", "ag", "a"};
    Arr<std::string> arr(4);
    for (int i = 0; i < 4; ++i) {
        arr[i] = s[i];
    }

    msd_sort(arr.data(), arr.get_size());

    for (int i = 0; i < arr.get_size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

int main() {
    test();
    test1();
    test3();
    test4();
    test5();
//    Arr<std::string> arr;
//
//    while (std::cin >> temp) {
//        arr.push(temp);
//    }
//
//    msd_sort(arr.data(), arr.get_size());
//
//    for (int i = 0; i < arr.get_size(); ++i) {
//        std::cout << arr[i] << std::endl;
//    }

    return 0;
}
