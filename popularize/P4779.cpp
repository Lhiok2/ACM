/*
P4779: [模板]单源最短路径(标准版)
https://www.luogu.com.cn/problem/P4779
*/
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

struct cmp {
    bool operator() (pair<int, long long> x, pair<int, long long> y) {
        return x.second > y.second;
    }
};

const int max_n = 1e5 + 5;
const int max_m = 2e5 + 5;
const long long inf = 0x3f3f3f3f3f3f3f;
int fir[max_n], nex[max_m];
long long dis[max_n];
pair<int, long long> road[max_m];
priority_queue< pair<int, long long>, vector< pair<int, long long> >, cmp> que;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, s, u, i, v;
    long long distance;
    pair<int, long long> p;
    cin >> n >> m >> s;
    for (i = 1; i <= m; ++i) {
        cin >> u >> road[i].first >> road[i].second;
        nex[i] = fir[u];
        fir[u] = i;
    }
    for (i = 1; i <= n; ++i) dis[i] = inf;
    dis[s] = 0;
    que.push({ s, 0 });
    while (!que.empty()) {
        p = que.top();
        que.pop();
        if (dis[p.first] < p.second) continue;
        for (u = fir[p.first]; u; u = nex[u]) {
            v = road[u].first;
            distance = road[u].second + p.second;
            if (distance < dis[v]) {
                dis[v] = distance;
                que.push({ v, distance });
            }
        }
    }
    for (i = 1; i <= n; ++i) cout << dis[i] << " ";
    cout << endl;
    return 0;
}