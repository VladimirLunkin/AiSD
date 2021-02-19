#include <iostream>


template <class T1, class T2>
class pair {
public:
    T1 first;
    T2 second;
};

bool comp_pair(const pair<int, int> &l, const pair<int, int> &r) {
    return l.first < r.first || l.first == r.first && l.second < r.second;
}

template <class T>
void merge(T *first_arr, int first_size, T *second_arr, int second_size,
           T *merge_arr, bool (*comp)(const T& l, const T& r)) {
    for (int current = 0, i = 0, j = 0; i < first_size + second_size; ++current) {
        if (comp(first_arr[i], second_arr[j])) {
            merge_arr[current] = first_arr[i];
            i++;
            if (i >= first_size) {
                current++;
                std::copy(second_arr + j, second_arr + second_size, merge_arr + current);
                break;
            }
        } else {
            merge_arr[current] = second_arr[j];
            j++;
            if (j >= second_size) {
                current++;
                std::copy(first_arr + i, first_arr + first_size, merge_arr + current);
                break;
            }
        }
    }
}

template <class T>
void merge_sort(T *arr, int size, bool (*comp)(const T& l, const T& r)) {
    if (size <= 1) {
        return;
    }

    int first_size = size / 2;
    int second_size = size - first_size;

    merge_sort(arr, first_size, comp);
    merge_sort(arr + first_size, second_size, comp);

    T *temp = new T[size];
    merge(arr, first_size, arr + first_size, second_size, temp, comp);
    std::copy(temp, temp + size, arr);

    delete[] temp;
}

int solve(pair<int, int> *pairs, int n) {
    merge_sort(pairs, n, comp_pair);

    int result = pairs[0].second - pairs[0].first;

    for (int i = 1; i < n; ++i) {
        if (pairs[i].first < pairs[i - 1].second &&
            pairs[i].second > pairs[i - 1].second) {
            result += pairs[i].second - pairs[i - 1].second;
        }
        else if (pairs[i].second > pairs[i - 1].second) {
            result += pairs[i].second - pairs[i].first;
        }
        else {
            pairs[i] = pairs[i - 1];
        }
    }

    return result;
}

int main() {
    int n = 0;
    std::cin >> n;

    pair<int, int> pairs[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> pairs[i].first >> pairs[i].second;
    }

    std::cout << solve(pairs, n);

    return 0;
}
