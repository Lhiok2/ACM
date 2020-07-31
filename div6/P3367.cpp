/*
P3367: 并查集
https://www.luogu.com.cn/problem/P3367
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int arr_size = 1e4 + 5;
int fa[arr_size];

int getFa(int x) {
    return fa[x] == x? x: fa[x] = getFa(fa[x]);
}

inline void merge(int x, int y) {
    x = getFa(x);
    y = getFa(y);
    fa[max(x, y)] = min(x, y);
}

inline void reply(int x, int y) {
    cout << (getFa(x) == getFa(y)? 'Y': 'N') << endl;
}

int main() {
    int n, m, t, x, y;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    while (m--) {
        cin >> t >> x >> y;
        if (t == 1) merge(x, y);
        else reply(x, y);
    } 
    return 0;
}