#include <iostream>
#include <assert.h>

using namespace std;


void max_sum(const int *mas1, const int *mas2, int length, int &i0, int &j0) {
    int i_max = 0;  // индекс максимального элемента на текующий момент в массиве mas1

    for (int i = 1; i < length; ++i) {
        if (mas1[i] > mas1[i0]) {
            i_max = (mas1[i] > mas1[i_max]) ? i : i_max;
        }
        if (mas1[i_max] + mas2[i] > mas1[i0] + mas2[j0]) {
            i0 = i_max;
            j0 = i;
        }
    }
}

void test1() {
    int length = 4;
    int mas1[] = {4, -8, 6, 0};
    int mas2[] = {-10, 3, 1, 1};
    int i0 = 0;
    int j0 = 0;
    max_sum(mas1, mas2, length, i0, j0);

    bool verdict = (i0 == 0) && (j0 == 1);
    //cout << i0 << " " << j0 << endl;
    assert(verdict);
}
void test2() {
    int length = 7;
    int mas1[] = {-9, 5, 6, 0, -1, 1, 9};
    int mas2[] = {-9, -1, -2, 5, 0, 7, -5};
    int i0 = 0;
    int j0 = 0;
    max_sum(mas1, mas2, length, i0, j0);

    bool verdict = (i0 == 2) && (j0 == 5);
    assert(verdict);
}
void test3() {
    int length = 10;
    int mas1[] = {7, 25, -1, -66, -3, 87, 62, 7, 31, 30};
    int mas2[] = {83, 30, -94, 67, 95, -15, 3, -13, 49, -72};
    int i0 = 0;
    int j0 = 0;
    max_sum(mas1, mas2, length, i0, j0);

    bool verdict = (i0 == 5) && (j0 == 8);
    //cout << i0 << " " << j0 << endl;
    assert(verdict);
}
void test4() {
    int length = 15;
    int mas1[] = {-6, 5, 6, 0, -6, 9, -9, -9, 5, -5, -3, -7, 5, 4, 10};
    int mas2[] = {5, -6, -6, 9, -7, -9, 8, 0, -2, -9, 7, 8, -3, -2, -6};
    int i0 = 0;
    int j0 = 0;
    max_sum(mas1, mas2, length, i0, j0);

    bool verdict = (i0 == 5) && (j0 == 6);
    assert(verdict);
}
void test5() {
    int length = 10;
    int mas1[] = {14, 3, 11, 13, 9, 4, 17, 2, 16, 17};
    int mas2[] = {10, 7, 4, 1, 0, 13, 11, 5, 3, 0};
    int i0 = 0;
    int j0 = 0;
    max_sum(mas1, mas2, length, i0, j0);

    bool verdict = (i0 == 6) && (j0 == 6);
    //cout << i0 << " " << j0 << endl;
    assert(verdict);
}

int main() {
    test1();
    cout << "test1 - OK" << endl;
    test2();
    cout << "test2 - OK" << endl;
    test3();
    cout << "test3 - OK" << endl;
    test4();
    cout << "test4 - OK" << endl;
    test5();
    cout << "test5 - OK" << endl;

    /*int length = 0;
    cin >> length;

    int *mas1 = new int[length];
    int *mas2 = new int[length];
    for (int i = 0; i < length; ++i) {
        cin >> mas1[i];
    }
    for (int i = 0; i < length; ++i) {
        cin >> mas2[i];
    }

    int i0 = 0;
    int j0 = 0;
    max_sum(mas1, mas2, length, i0, j0);
    cout << i0 << " " << j0 << endl;

    delete [] mas1;
    delete [] mas2;*/

    return 0;
}