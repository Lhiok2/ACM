/*
P5905: 全源最短路 (Johnson)
https://www.luogu.com.cn/problem/P5905
*/
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;

struct cmp {
    bool operator() (pair<int, long long> x, pair<int, long long> y) {
        return x.second > y.second;
    }
};

const int max_n = 3005;
const int max_m = 6005;
const long long inf = 1e9;
int n, vis[max_n], fir[max_n], nex[max_m];
long long h[max_n], dis[max_n];
bool exist[max_n];
queue<int> que;
pair<int, long long> road[max_m];
priority_queue< pair<int, long long>, vector< pair<int, long long> >, cmp> pri_que;

inline bool spfa() {
    register int i, u, v;
    register long long w;
    for (i = 1; i <= n; ++i) {
        que.push(i);
        exist[i] = true;
    }
    while (!que.empty()) {
        u = que.front();
        que.pop();
        exist[u] = false;
        for (i = fir[u]; i; i = nex[i]) {
            v = road[i].first;
            w = road[i].second + h[u];
            if (w < h[v]) {
                h[v] = w;
                if (!exist[v]) {
                    if (++vis[v] == n) return false;
                    que.push(v);
                    exist[v] = true;
                }
            }
        }
    }
    return true;
}

inline void dijkstra(int origin) {
    register int i, u, v;
    register long long w;
    pair<int, long long> p;
    for (i = 1; i <= n; ++i) dis[i] = inf;
    pri_que.push({ origin, 0 });
    dis[origin] = 0;
    while (!pri_que.empty()) {
        p = pri_que.top();
        pri_que.pop();
        u = p.first;
        if (dis[u] < p.second) continue;
        for (i = fir[u]; i; i = nex[i]) {
            v = road[i].first;
            w = p.second + road[i].second;
            if (w < dis[v]) {
                dis[v] = w;
                pri_que.push({ v, w });
            }
        }
    }
}

int main() {
    register int m, i, j, u, v;
    register long long w, ans;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %lld", &u, &v, &w);
        nex[i] = fir[u];
        fir[u] = i;
        road[i] = { v, w };
    }
    if (!spfa()) {
        printf("-1\n");
        return 0;
    }
    for (u = 1; u <= n; ++u) {
        for (i = fir[u]; i; i = nex[i]) {
            v = road[i].first;
            road[i].second += h[u] - h[v];
        }
    }
    for (i = 1; i <= n; ++i) {
        dijkstra(i);
        for (j = 1, ans = 0ll; j <= n; ++j) {
            if (dis[j] == inf) ans += j * inf;
            else ans += j * (dis[j] - h[i] + h[j]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}