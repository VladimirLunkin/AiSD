#include <iostream>
#include <cstring>

using namespace std;

void merge(int *first_arr, ssize_t first_size, int *second_arr, ssize_t second_size, int *merge_arr) {
    for (ssize_t current = 0, i = 0, j = 0; i < first_size + second_size; ++current) {
        if (first_arr[i] < second_arr[j]) {
            merge_arr[current] = first_arr[i];
            i++;
            if (i >= first_size) {
                current++;
                memcpy(merge_arr + current, second_arr + j, (second_size - j) * sizeof(int));
                break;
            }
        } else {
            merge_arr[current] = second_arr[j];
            j++;
            if (j >= second_size) {
                current++;
                memcpy(merge_arr + current, first_arr + i, (first_size - i) * sizeof(int));
                break;
            }
        }
    }
}
void merge_sort(int *arr, ssize_t size) {
    if (size <= 1) {
        return;
    }

    ssize_t first_size = size / 2;
    ssize_t second_size = size - first_size;

    merge_sort(arr, first_size);
    merge_sort(arr + first_size, second_size);

    int *temp = new int[size];
    merge(arr, first_size, arr + first_size, second_size, temp);
    memcpy(arr, temp, size * sizeof(int));

    delete[] temp;
}

void bubble_sort(int *arr, ssize_t size) {
    for (ssize_t i = 0; i < size - 1; ++i) {
        bool f = true;
        for (ssize_t j = 0; j < size - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                f = false;
            }
        }
        if (f) {
            break;
        }
    }
}

int fast_sum(int *arr, ssize_t size) {
    int sum = 0;


    int min[] = {arr[0], arr[0]};

    int arr_sum[size / 2 + 1];

    ssize_t min_ind = 0;
    for (ssize_t i = 1; i < size; ++ i) {
        if (arr[i] < min[1]) {
            if (arr[i] < min[0]) {
                min[1] = min[0];
                min[0] = arr[i];
            } else {
                min[1] = arr[i];
            }
        }
    }

    arr[0] = 1;

    return sum;
}
