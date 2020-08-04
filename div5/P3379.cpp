/*
P3379: 最近公共祖先
https://www.luogu.com.cn/problem/P3379
*/
#include <iostream>
using namespace std;

inline void swap(int& x, int& y) {
    x ^= y;
    y ^= x;
    x ^= y;
}

const int max_n = 5e5 + 5;
const int max_m = 1e6 + 5;
int lca[max_n][20], depth[max_n], fir[max_n], nex[max_m], link_node[max_m];

void dfs(int p, int dep, int fa) {
    int i;
    depth[p] = dep;
    lca[p][0] = fa;
    for (i = 1; i < 20; ++i) 
        lca[p][i] = lca[lca[p][i-1]][i-1];
    for (i = fir[p]; i; i = nex[i]) {
        if (link_node[i] == fa) continue;
        dfs(link_node[i], dep + 1, p);
    }
}

inline void build(int n, int root) {
    int i, j, u, v;
    for (i = 1, j = max_n; i < n; ++i, ++j) {
        cin >> u >> v;
        nex[i] = fir[u];
        fir[u] = i;
        link_node[i] = v;
        nex[j] = fir[v];
        fir[v] = j;
        link_node[j] = u;
    }
    dfs(root, 0, 0);
}

inline int query(int x, int y) {
    int i, j, mid;
    int dep = depth[x] - depth[y];
    if (dep < 0) {
        swap(x, y);
        dep = -dep;
    }
    for (i = 0; dep; ++i) {
        if (dep & 1) x = lca[x][i];
        dep >>= 1;
    }
    if (x == y) return x;
    for (j = 19; j;) {
        if (lca[x][j] != lca[y][j]) {
            x = lca[x][j];
            y = lca[y][j];
        } else j >>= 1;
    }
    return lca[x][0] == lca[y][0]? lca[x][0]: lca[x][1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, root, x, y;
    cin >> n >> m >> root;
    build(n, root);
    while (m--) {
        cin >> x >> y;
        cout << query(x, y) << endl;
    }
    return 0;
}