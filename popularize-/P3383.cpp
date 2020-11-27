/*
P3383: [模板]线性筛素数
https://www.luogu.com.cn/problem/P3383
*/
#include <bitset>
#include <iostream>
#include <algorithm>
using namespace std;

const int arr_size = 5800000;
const int max_n = 1e8 + 5;
int pri[arr_size];
bitset<max_n> vis;

inline void build(int n) {
    int i, j, si = 0;
    for (i = 2; i <= n; ++i) {
        if(!vis[i]) pri[++si] = i;
        for (j = 1; j <= si && i * pri[j] <= n; ++j) {
            vis[i * pri[j]] = true;
            if (i % pri[j]) continue;
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, q;
    cin >> n >> m;
    build(n);
    while (m--) {
        cin >> q;
        // endl输出速度过慢 换成'\n'
        cout << pri[q] << "\n";
    }
    return 0;
}