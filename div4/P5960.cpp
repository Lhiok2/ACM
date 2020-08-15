/*
P5960: 差分约束算法
https://www.luogu.com.cn/problem/P5960
*/
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

const int max_n = 5005;
bool exists[max_n];
int vis[max_n], fir[max_n], nex[max_n], road[max_n];
long long dis[max_n], w[max_n];
queue<int> que;

inline int spfa(int n) {
    register int i, u, v;
    for (i = 1; i <= n; ++i) {
        que.push(i);
        exists[i] = true;
    }
    while (!que.empty()) {
        u = que.front();
        que.pop();
        if (++vis[u] > n) return -1;
        exists[u] = false;
        for (i = fir[u]; i; i = nex[i]) {
            v = road[i];
            if (dis[u] + w[i] < dis[v]) {
                dis[v] = dis[u] + w[i];
                if (!exists[v]) {
                    exists[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    register int n, m, i, v;
    cin >> n >> m;
    for (i = 1; i <= m; ++i) {
        cin >> road[i] >> v >> w[i];
        nex[i] = fir[v];
        fir[v] = i;
    }
    if (~spfa(n)) {
        for (i = 1; i <= n; ++i) cout << dis[i] << ' ';
        cout << '\n';
    } else cout << "NO\n";
    return 0;
}