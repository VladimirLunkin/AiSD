#include <iostream>
#include <assert.h>

using namespace std;


int required_amount(const int *mas1, const int *mas2, int num1, int num2, int k) {
    int count = 0;
    for (int i = 0; i < num1; ++i) {
        for (int j = num2 - 1; j >= 0; --j) {
            if (mas1[i] + mas2[j] == k) {
                count++;
                num2 = j;
            } else if (mas1[i] + mas2[j] < k) {
                break;
            }
        }
    }

    return count;
}

void test1() {
    int num1 = 4;
    int mas1[] = {-5, 0, 3, 18};
    int num2 = 5;
    int mas2[] = {-10, -2, 4, 7, 12};
    int k = 7;

    assert(3 == required_amount(mas1, mas2, num1, num2, k));
}
void test2() {
    int num1 = 4;
    int mas1[] = {-5, 0, 3, 18};
    int num2 = 5;
    int mas2[] = {-10, -2, 4, 7, 12};
    int k = 7;

    assert(3 == required_amount(mas1, mas2, num1, num2, k));
}

int main() {
    test1();
    cout << "test1 - OK" << endl;
    test2();
    cout << "test2 - OK" << endl;

    /*int num1 = 0;
    cin >> num1;
    int *mas1 = new int[num1];
    for (int i = 0; i < num1; ++i) {
        cin >> mas1[i];
    }

    int num2 = 0;
    cin >> num2;
    int *mas2 = new int[num2];
    for (int i = 0; i < num2; ++i) {
        cin >> mas2[i];
    }

    int k = 0;
    cin >> k;
    cout << required_amount(mas1, mas2, num1, num2, k) << endl;

    delete [] mas1;
    delete [] mas2;*/

    return 0;
}
