/*
P2575: 高手过招
https://www.luogu.com.cn/problem/P2575
*/
#include <iostream>
using namespace std;

inline void solve() {
    register int n, m, i, j, x, odd, con, sg = 0, cnt[21] = {0};
    cin >> n;
    for (i = 0; i < n; ++i) {
        cin >> m;
        while (m--) {
            cin >> x;
            cnt[x] = 1;
        }
        odd = con = 0;
        for (j = 20; j > 0; --j) {
            if (cnt[j]) {
                if (odd) ++con;
                --cnt[j];
                continue;
            }
            sg ^= con;;
            con = 0;
            odd ^= 1;
        }
        // 不同行相互影响
        sg ^= con;
    }
    cout << (sg? "YES": "NO") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}