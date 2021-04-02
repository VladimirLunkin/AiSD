#include <iostream>

using namespace std;

template <class T>
int binary_search(T *arr, T key, int left, int right) {
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

template <class T>
int exponential_search(T *arr, int size, T key) {
    int bound = 0;
    while (bound < size && arr[bound] < key) {
        if (bound == 0) {
            bound = 1;
        }
        bound *= 2;
    }
    bound++;

    return binary_search(arr, key, bound / 2, (bound < size) ? bound : size);
}

int main() {
    size_t n = 0;
    cin >> n;

    int *arr = new int[n];
    for (size_t i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int k = 0;
    cin >> k;

    cout << exponential_search(arr, n, k) << endl;

    delete [] arr;

    return 0;
}
