/*
P3374: 树状数组1
https://www.luogu.com.cn/problem/P3374
*/
#include <iostream>
#include <algorithm>
#define lowbit(x) (x & -x)
using namespace std;

const int arr_size = 1050000;
long long arr[arr_size];

inline void update(int index, int val) {
    for ( ; index < arr_size; index += lowbit(index)) arr[index] += val;
}

inline void build(int n) {
    long long val;
    for (int i = 1; i <= n; ++i) {
        cin >> val;
        update(i, val);
    }
}

inline long long get(int index) {
    long long val = 0;
    for ( ; index; index ^= lowbit(index)) val += arr[index];
    return val;
}

inline long long get(int lef, int rig) {
    return get(rig) - get(lef - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q, x, y;
    cin >> n >> m;
    build(n);
    while (m--) {
        cin >> q >> x >> y;
        if (q == 1) update(x, y);
        else cout << get(x, y) << "\n";
    }
    return 0;
}