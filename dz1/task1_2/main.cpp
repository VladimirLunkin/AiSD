#include <iostream>
#include <assert.h>

using namespace std;

typedef struct {
    int x;
    int y;
} Point;

double polygon_area(Point *arr, int num) {
    Point max(arr[0]);
    Point min(arr[0]);

    for (int i = 1; i < num; ++i) {
        max.x = (arr[i].x > max.x) ? arr[i].x : max.x;
        max.y = (arr[i].y > max.y) ? arr[i].y : max.y;
        min.x = (arr[i].x < min.x) ? arr[i].x : min.x;
        min.y = (arr[i].y < min.y) ? arr[i].y : min.y;
    }

    double area = (max.y - min.y) * (max.x - min.x);
    for (int i = 0; i < num; ++i) {
        int j = (i + 1) % num;
        if (arr[j].x < arr[i].x) {
            int a = arr[i].y - min.y;
            int b = arr[j].y - min.y;
            int h = arr[i].x - arr[j].x;
            area -= double((a + b) * h) / 2;
        } else {
            int a = max.y - arr[i].y;
            int b = max.y - arr[j].y;
            int h = arr[j].x - arr[i].x;
            area -= double((a + b) * h) / 2;
        }
    }

    return area;
}

void test1() {
    int num = 3;
    Point arr[] = {{1, 0}, {0, 1}, {2, 2}};

    assert(1.5 == polygon_area(arr, num));
}
void test2() {
    int num = 7;
    Point arr[] = {{0, 1}, {1, 4}, {3, 4}, {4, 3}, {3, 1}, {2, 0}, {1, 0}};

    assert(11 == polygon_area(arr, num));
}

int main() {
    test1();
    cout << "test1 - OK" << endl;
    test2();
    cout << "test2 - OK" << endl;

    /*int num = 0;
    cin >> num;

    Point *arr = new Point[num];
    for (int i = 0; i < num; ++i) {
        cin >> arr[i].x >> arr[i].y;
    }

    double s = 0;
    s = polygon_area(arr, num);
    cout << s << endl;

    delete [] arr;*/
    return 0;
}
