/*
P2197: nim游戏
https://www.luogu.com.cn/problem/P2197
*/
#include <iostream>
#include <algorithm>
using namespace std;

inline void solve() {
    int n, x, y = 0;
    cin >> n;
    for (register int i = 0; i < n; ++i) {
        cin >> x;
        y ^= x;
    }
    if (y) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}