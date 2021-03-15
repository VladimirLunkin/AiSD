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
    int num1 = 0;
    int num2 = 0;

    cin >> num1;
    cin >> num2;

    int *A = new int[num1];
    int *B = new int[num2];

    for (int i = 0; i < num1; ++i) {
        cin >> A[i];
    }
    for (int i = 0; i < num2; ++i) {
        cin >> B[i];
    }

    for (int i = 0; i < num2; ++i) {
        cout << exponential_search(A, num1, B[i]) << " ";
    }

    delete [] A;
    delete [] B;

    return 0;
}
