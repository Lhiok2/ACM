/*
P3384: 轻重链剖分
https://www.luogu.com.cn/problem/P3384
*/
#pragma GCC optimize(3, "Ofast", "inline")
#include <stack>
#include <iostream>
#include <algorithm>
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define modp(x) ((x) % p)
#define num(x) (tree[x].hash_num)
#define top_fa(x) (tree[tree[x].top].fa)
#define top_dep(x) (tree[tree[x].top].dep)
using namespace std;

const int max_n = 1e5 + 5;
int N, cnt, fir[max_n], nex[max_n << 1], road[max_n << 1];
long long p;

struct NODE {
    int w;
    int si;
    int fa;
    int son;
    int dep;
    int top;
    int hash_num;
} tree[max_n];

struct NODE2 {
    int si;
    long long sum;
    long long lazy;
} zkw[max_n << 2];

void dfs1(int u, int fa) {
    tree[u].si = 1;
    tree[u].fa = fa;
    tree[u].dep = tree[fa].dep + 1;
    int max_si = 0;
    for (int i = fir[u], v; i; i = nex[i]) {
        v = road[i];
        if (v == fa) continue;
        dfs1(v, u);
        tree[u].si += tree[v].si;
        if (tree[v].si > max_si) {
            tree[u].son = v;
            max_si = tree[v].si;
        }
    }
}

void dfs2(int u, int top) {
    tree[u].top = top;
    tree[u].hash_num = ++cnt;
    zkw[cnt].si = 1;
    zkw[cnt].sum = modp(tree[u].w);
    if (!tree[u].son) return;
    dfs2 (tree[u].son, top);
    for (int i = fir[u], v; i; i = nex[i]) {
        v = road[i];
        if (v == tree[u].fa || v == tree[u].son) continue;
        dfs2(v, v);
    }
}

inline void build(int n, int root) {
    register int i, j, u, v;
    for (i = 1; i <= n; ++i) cin >> tree[i].w;
    for (i = 1, j = max_n; i < n; ++i, ++j) {
        cin >> u >> v;
        nex[i] = fir[u];
        fir[u] = i;
        road[i] = v;
        nex[j] = fir[v];
        fir[v] = j;
        road[j] = u;
    }

    for (N = 1, i = n + 2; N < i; N <<= 1);

    cnt = N;
    tree[0].dep = -1;
    dfs1(root, 0);
    dfs2(root, root);

    for (i = N - 1; i; --i) {
        u = ls(i), v = rs(i);
        zkw[i].si = zkw[u].si + zkw[v].si;
        zkw[i].sum = modp(zkw[u].sum + zkw[v].sum);
    }
}

inline void spread(int x) {
    if (!zkw[x].lazy || zkw[x].si == 1) return;
    register int u = ls(x), v = rs(x);
    zkw[u].lazy = modp(zkw[u].lazy + zkw[x].lazy);
    zkw[u].sum = modp(zkw[u].sum + zkw[u].si * zkw[x].lazy);
    zkw[v].lazy = modp(zkw[v].lazy + zkw[x].lazy);
    zkw[v].sum = modp(zkw[v].sum + zkw[v].si * zkw[x].lazy);
    zkw[x].lazy = 0ll;
}

inline void applyTags(int x) {
    stack<int> heap;
    for ( ; x; x >>= 1) heap.push(x);
    while (!heap.empty()) {
        spread(heap.top());
        heap.pop();
    }
}

inline void update(int lef, int rig, long long val) {
    register int i, j, l, r, x;
    register bool tl = false, tr = false;
    for (i = lef - 1, j = rig + 1; i ^ j ^ 1; i >>= 1, j >>= 1) {
        if (~i & 1) {
            x = i ^ 1;
            if (!tl) {
                l = x;
                tl = true;
                applyTags(x);
            }
            zkw[x].lazy = modp(zkw[x].lazy + val);
            zkw[x].sum = modp(zkw[x].sum + zkw[x].si * val);
        }
        if (j & 1) {
            x = j ^ 1;
            if (!tr) {
                r = x;
                tr = true;
                applyTags(x);
            }
            zkw[x].lazy = modp(zkw[x].lazy + val);
            zkw[x].sum = modp(zkw[x].sum + zkw[x].si * val);
        }
    }
    if (tl) for (i = l >> 1; i; i >>= 1) zkw[i].sum = modp(zkw[ls(i)].sum + zkw[rs(i)].sum);
    if (tr) for (i = r >> 1; i; i >>= 1) zkw[i].sum = modp(zkw[ls(i)].sum + zkw[rs(i)].sum);
}

inline long long query(int lef, int rig) {
    register int i, j, x;
    register long long ans = 0;
    register bool tl = false, tr = false;
    for (i = lef - 1, j = rig + 1; i ^ j ^ 1; i >>= 1, j >>= 1) {
        if (~i & 1) {
            x = i ^ 1;
            if (!tl) {
                tl = true;
                applyTags(x);
            }
            ans = modp(ans + zkw[x].sum);
        }
        if (j & 1) {
            x = j ^ 1;
            if (!tr) {
                tr = true;
                applyTags(x);
            }
            ans = modp(ans + zkw[x].sum);
        }
    }
    return ans;
}

inline void swap(int& x, int& y) {
    if (&x == &y) return;
    x ^= y;
    y ^= x;
    x ^= y;
}

inline void op1() {
    register int x, y;
    register long long val;
    cin >> x >> y >> val;
    while (tree[x].top != tree[y].top) {
        if (top_dep(y) < top_dep(x)) swap(x, y);
        update(num(tree[y].top), num(y), val);
        y = top_fa(y);
    }
    if (tree[y].dep < tree[x].dep) swap(x, y);
    update(num(x), num(y), val);
}

inline void op2() {
    register int x, y;
    register long long ans = 0ll;
    cin >> x >> y;
    while (tree[x].top != tree[y].top) {
        if (top_dep(y) < top_dep(x)) swap(x, y);
        ans = modp(ans + query(num(tree[y].top), num(y)));
        y = top_fa(y);
    }
    if (tree[y].dep < tree[x].dep) swap(x, y);
    ans = modp(ans + query(num(x), num(y)));
    cout << ans << "\n";
}

inline void op3() {
    register int x;
    register long long val;
    cin >> x >> val;
    update(num(x), num(x) + tree[x].si - 1, val);
}

inline void op4() {
    register int x;
    cin >> x;
    cout << query(num(x), num(x) + tree[x].si - 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, r, q;
    cin >> n >> m >> r >> p;
    build(n, r);
    while (m--) {
        cin >> q;
        if (q == 1) op1();
        else if (q == 2) op2();
        else if (q == 3) op3();
        else op4();
    }
    return 0;
}