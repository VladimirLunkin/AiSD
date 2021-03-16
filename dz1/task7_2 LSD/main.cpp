#include <iostream>

using namespace std;

static const int byte_in_number = 8;
static const int number_of_bits = 256;

static inline uint8_t get_byte(uint64_t num, int rank) {
    return (num >> (rank * byte_in_number)) & 0xFF;
}

void lsd_sort(uint64_t *arr, ssize_t size) {
    for (int rank = 0; rank < byte_in_number; ++rank) {
        auto *counters = new int[number_of_bits];
        fill_n(counters, number_of_bits, 0);

        for (ssize_t i = 0; i < size; ++i) {
            uint8_t index = get_byte(arr[i], rank);
            counters[index]++;
        }

        for (int i = 1; i < number_of_bits; ++i) {
            counters[i] += counters[i - 1];
        }

        auto *tmp_arr = new uint64_t[size];
        for (ssize_t i = size - 1; i >= 0; --i) {
            uint8_t index = get_byte(arr[i], rank);
            tmp_arr[--counters[index]] = arr[i];
        }

        for (ssize_t i = 0; i < size; ++i) {
            arr[i] = tmp_arr[i];
        }

        delete [] tmp_arr;
        delete [] counters;
    }
}
typedef void (*Tests)();

void test1() {
    ssize_t size = 5;
    uint64_t arr[] = {39284, 1234, 1395470, 1234, 123};

    lsd_sort(arr, size);

    for (ssize_t i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void test2() {
    ssize_t size = 1;
    uint64_t arr[] = {2};

    lsd_sort(arr, size);

    for (ssize_t i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void test3() {
    ssize_t size = 0;
    uint64_t arr[] = {};

    lsd_sort(arr, size);

    for (ssize_t i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void test4() {
    ssize_t size = 9;
    uint64_t arr[] = {3, 2, 1, 3, 2, 1, 1, 3, 2};

    lsd_sort(arr, size);

    for (ssize_t i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void test5() {
    ssize_t size = 9;
    uint64_t arr[] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE, 1, 3, 0xFFFFFFFFFFFFFFFF, 1, 1, 3, 2};

    lsd_sort(arr, size);

    for (ssize_t i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    Tests tests[] = {test1, test2, test3, test4, test5};//, test6};

    for (int i = 0; i < 5; ++i) {
        tests[i]();
        cout << "test" << i + 1 << " - OK" << endl << endl;
    }

    return 0;
}
