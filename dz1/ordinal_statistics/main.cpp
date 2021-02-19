#include <iostream>


using namespace std;

template <class T>
bool is_less(const T& l, const T& r) {
    return l < r;
}

template <class T>
int median(const T *arr, int size, bool (*comp)(const T& l, const T& r)) {
    int left = 0;
    int middle = size / 2;
    int right = size - 1;

    if (comp(arr[middle], arr[left]) && comp(arr[left],arr[right]) ||
        comp(arr[right], arr[left]) && comp(left, arr[middle])) {
        return left;
    }
    if (comp(arr[middle], arr[right]) && comp(arr[right], arr[left]) ||
        comp(arr[left], arr[right]) && comp(arr[right], arr[middle])) {
        return right;
    }
    return middle;
}

template <class T>
int partition(T *arr, int size, bool (*comp)(const T& l, const T& r)) {
    T pivot = arr[size - 1];
    int i = size - 2;
    int j = size - 2;

    while (j >= 0) {
        if (comp(arr[j], pivot)) {
            j--;
        } else {
            swap(arr[i], arr[j]);
            i--;
            j--;
        }
    }
    swap(arr[++i], arr[size - 1]);

    return i;
}

template <class T>
T ordinal_statistics(T *arr, int size, int k, bool (*comp)(const T& l, const T& r)) {
    T *l = arr;      // [
    int r = size;   //   )
    int mid = 0;

    do {
        mid = median(l, r, comp);

        swap(l[r - 1], l[mid]);
        int part = partition(l, r, comp);

        if (k < part) {
            r = part;
        } else {
            l += part;
            r -= part;
            k -= part;
        }

    } while (r > 1);  // r > 1

    return l[0];
}

// quick_sort
/*template <class T>
int partition(T *arr, int size, bool (*comp)(const T& l, const T& r)) {
    if (size <= 1) {
        return 0;
    }

    T pivot = arr[size - 1];
    int i = 0;
    int j = size - 2;

    while (i <= j) {
        for (; comp(arr[i], pivot); ++i) {}
        for (; !comp(arr[j], pivot) && j >= 0; --j) {}
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i], arr[size - 1]);

    return i;
}
template <class T>
void quick_sort(T *arr, int size, bool (*comp)(const T& l, const T& r)) {
    int part = partition(arr, size, comp);
    if (part > 0) {
        quick_sort(arr, part, comp);
    }
    if (part < size - 1) {
        quick_sort(arr + part + 1, size - part - 1, comp);
    }
} */

int main() {
    int n;
    int k;
    cin >> n >> k;

    int arr[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << ordinal_statistics(arr, n, k, is_less) << endl;

    return 0;
}
