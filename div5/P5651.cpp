/*
P5651: 基础最短路练习题
https://www.luogu.com.cn/problem/P5651
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int max_n = 1e5 + 5;
const int max_m = 4e5 + 5;

int n, m, dis[max_n], fir[max_n], nex[max_m];
pair<int, int> road[max_m];

void dfs(int p, int w, int la) {
    if (~dis[p] && !(dis[p] ^ w)) return;
    dis[p] = w;
    while (fir[p]) {
        if (road[fir[p]].first != la) dfs(road[fir[p]].first, w ^ road[fir[p]].second, p);
        fir[p] = nex[fir[p]];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int i, u, v, q, w, cnt = 0;
    cin >> n >> m >> q;
    for (i = 1; i <= m; ++i) {
        cin >> u >> v >> w;
        road[++cnt] = { v, w };
        nex[cnt] = fir[u];
        fir[u] = cnt;
        road[++cnt] = { u, w };
        nex[cnt] = fir[v];
        fir[v] = cnt;
    }
    for (i = 1; i <= n; ++i) dis[i] = -1;
    dfs(1, 0, 0);
    while (q--) {
        cin >> u >> v;
        cout << (dis[u] ^ dis[v]) << "\n";
    }
    return 0;
}