/*
P3379: [模板]最近公共祖先(LCA)
https://www.luogu.com.cn/problem/P3379
*/
#include <iostream>
#define max_n 500005
#define max_m 1000005
using namespace std;

int cnt, lca[max_n][20], depth[max_n], fir[max_n], nex[max_m], link_node[max_m];

void dfs(int p, int fa) {
    depth[p] = depth[lca[p][0] = fa] + 1;
    for (int i = 0; i < 19; ++i) lca[p][i+1] = lca[lca[p][i]][i];
    for (int i = fir[p]; i; i = nex[i]) {
        if (link_node[i] == fa) continue;
        dfs(link_node[i], p);
    }
}

inline void addEdge(int u, int v) {
	nex[++cnt] = fir[u];
	fir[u] = cnt;
	link_node[cnt] = v;
}

inline void build(int n, int root) {
    register int i, j, u, v;
    for (i = 1, j = max_n; i < n; ++i, ++j) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(root, 0);
}

inline int query(int x, int y) {
	if (depth[x] > depth[y]) swap(x, y);
    for (int i = 19; ~i; --i) if (depth[lca[y][i]] >= depth[x]) y = lca[y][i];
    if (x == y) return x;
    for (int i = 19; ~i; --i) {
        if (lca[x][i] == lca[y][i]) continue;
        x = lca[x][i];
        y = lca[y][i];
    }
    return lca[x][0];
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