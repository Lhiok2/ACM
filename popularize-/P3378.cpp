/*
P3378: [模板]堆
https://www.luogu.com.cn/problem/P3378
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int arr_size = 1e6 + 5;
int a[arr_size], si = 0;

inline void swap(int& x, int& y) {
    if (&x == &y) return;
    x ^= y;
    y ^= x;
    x ^= y;
}

inline void push(int x) {
    a[++si] = x;
    for (int i = si; i > 1 && a[i] < a[i>>1]; i >>= 1) swap(a[i], a[i>>1]);
}

inline void print() {
    cout << a[1] << endl;
}

inline void remove() {
    a[1] = a[si--];
    int i = 1, lef = 2, rig = 3;
    while (rig <= si) {
        if (a[i] > a[lef] && a[lef] <= a[rig]) {
            swap(a[i], a[lef]);
            i = lef;
        } else if (a[i] > a[rig] && a[rig] < a[lef]) {
            swap(a[i], a[rig]);
            i = rig;
        } else break;
        lef = i << 1;
        rig = lef + 1;
    }
    if (lef == si && a[i] > a[lef]) swap(a[i], a[lef]);
}

int main() {
    int t, q, x;
    cin >> t;
    while (t--) {
        cin >> q;
        if (q == 1) {
            cin >> x;
            push(x);
        } else if (q == 2) print();
        else remove();
    }
    return 0;
}