/*
P3366: [模板]最小生成树
https://www.luogu.com.cn/problem/P3366
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int node_size = 5005;
const int edge_size = 2e5 + 5;
int sum_cost, linked_node_num, fa[node_size];

struct EDGE {
    int u, v, w;
    
    inline void read() {
        cin >> u >> v >> w;
    }

    bool operator < (const EDGE& t) const {
        return w < t.w;
    }
} edge[edge_size];

int getFa(int x) {
    return fa[x] == x? x: fa[x] = getFa(fa[x]);
}

inline void linking(EDGE e) {
    e.u = getFa(e.u);
    e.v = getFa(e.v);
    if (e.u == e.v) return;
    sum_cost += e.w;
    ++linked_node_num;
    fa[max(e.u, e.v)] = min(e.u, e.v);
}

int main() {
    int n, m, u, v, w;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) edge[i].read();
    sort(edge+1, edge+m+1);
    for (int i = 1; i <= m; ++i) linking(edge[i]);
    if (linked_node_num + 1 != n) cout << "orz" << endl;
    else cout << sum_cost << endl;
    return 0;
}