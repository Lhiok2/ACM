/*
P3373: [模板]线段树2
https://www.luogu.com.cn/problem/P3373
*/
#include <cstdio>
#include <algorithm>
#define lef_node (index << 1)
#define rig_node ((index << 1) | 1)
#define lef_son tree[index].lef
#define mid_lef tree[index].mid
#define mid_rig (tree[index].mid + 1)
#define rig_son tree[index].rig
#define modp(x) ((x) % p)
using namespace std;

const int node_num = 4e5 + 5;
long long p;

struct NODE {
    int lef, rig, mid;
    long long lazy, fact, sum;
} tree[node_num];

void build(int index, int lef, int rig) {
    lef_son = lef;
    rig_son = rig;
    mid_lef = lef + rig >> 1;
    tree[index].lazy = 0;
    tree[index].fact = 1;
    if (lef == rig) {
        scanf("%lld", &tree[index].sum);
        return;
    }
    build(lef_node, lef, mid_lef);
    build(rig_node, mid_rig, rig);
    tree[index].sum = modp(tree[lef_node].sum + tree[rig_node].sum);
}

inline void updateSum(int index) {
    tree[index].sum = modp(modp(modp(tree[lef_node].sum * tree[lef_node].fact)
    + modp(tree[lef_node].lazy * (tree[lef_node].rig - tree[lef_node].lef + 1)))
    + modp(modp(tree[rig_node].sum * tree[rig_node].fact)
    + modp(tree[rig_node].lazy * (tree[rig_node].rig - tree[rig_node].lef + 1))));
}

void spread(int index) {
    if (!tree[index].lazy && tree[index].fact == 1) return;
    tree[lef_node].fact = modp(tree[lef_node].fact * tree[index].fact);
    tree[lef_node].lazy = modp(tree[lef_node].lazy * tree[index].fact + tree[index].lazy);
    tree[rig_node].fact = modp(tree[rig_node].fact * tree[index].fact);
    tree[rig_node].lazy = modp(tree[rig_node].lazy * tree[index].fact + tree[index].lazy);
    tree[index].fact = 1;
    tree[index].lazy = 0;
    updateSum(index);
}

void updateFact(int index, int lef, int rig, long long mul) {
    if (lef_son == lef && rig_son == rig) {
        tree[index].fact = modp(tree[index].fact * mul);
        tree[index].lazy = modp(tree[index].lazy * mul);
        return;
    }
    spread(index);
    if (lef <= mid_lef) updateFact(lef_node, lef, min(mid_lef, rig), mul);
    if (rig > mid_lef) updateFact(rig_node, max(lef, mid_rig), rig, mul);
    updateSum(index);
}

void updateLazy(int index, int lef, int rig, long long val) {
    if (lef_son == lef && rig_son == rig) {
        tree[index].lazy = modp(tree[index].lazy + val);
        return;
    }
    spread(index);
    if (lef <= mid_lef) updateLazy(lef_node, lef, min(mid_lef, rig), val);
    if (rig > mid_lef) updateLazy(rig_node, max(lef, mid_rig), rig, val);
    updateSum(index);
}

long long query(int index, int lef, int rig) {
    if (lef_son == lef && rig_son == rig) {
        return modp(modp(tree[index].sum * tree[index].fact)
        + modp(tree[index].lazy * (rig - lef + 1)));
    }
    spread(index);
    long long ans = 0;
    if (lef <= mid_lef) ans = query(lef_node, lef, min(mid_lef, rig));
    if (rig > mid_lef) ans = modp(ans + query(rig_node, max(lef, mid_rig), rig));
    return modp(modp(ans * tree[index].fact) + modp(tree[index].lazy * (rig - lef + 1)));
}

int main() {
    int n, m, q, x, y;
    long long w;
    scanf("%d %d %lld", &n, &m, &p);
    build(1, 1, n);
    while (m--) {
        scanf("%d %d %d", &q, &x, &y);
        if (q == 3) printf("%lld\n", query(1, x, y));
        else {
            scanf("%lld", &w);
            if (q == 1) updateFact(1, x, y, w);
            else updateLazy(1, x, y, w);
        }
    }
    return 0;
}