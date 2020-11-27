/*
P3372: [模板]线段树1
https://www.luogu.com.cn/problem/P3372
*/
#include <iostream>
#include <algorithm>
using namespace std;

inline void swapL(int& x, int& y) {
    x ^= y;
    y ^= x;
    x ^= y;
}

const int node_num = 4e5 + 5;

struct Node {
    int lef, rig, mid;
    long long sum, lazy;

    inline bool isLeaf() {
        return lef == rig;
    }

    inline bool correctArea(int lef, int rig) {
        return this->lef == lef && this->rig == rig;
    }
} tree[node_num];

long long build(int index, int lef, int rig) {
    tree[index].lef = lef;
    tree[index].rig = rig;
    tree[index].mid = tree[index].lef + tree[index].rig >> 1;
    tree[index].lazy = 0;
    if (tree[index].isLeaf()) cin >> tree[index].sum;
    else tree[index].sum = build(index << 1, lef, tree[index].mid) + build((index << 1) + 1, tree[index].mid + 1, rig);
    return tree[index].sum;
}

void update(int index, int lef, int rig, long long val) {
    if (tree[index].correctArea(lef, rig)) {
        tree[index].lazy += val;
        return;
    }
    tree[index].sum += (rig - lef + 1) * val;
    if (lef <= tree[index].mid) update(index << 1, lef, min(rig, tree[index].mid), val);
    if (rig > tree[index].mid) update((index << 1) + 1, max(lef, tree[index].mid + 1), rig, val);
}

long long query(int index, int lef, int rig) {
    long long ans = tree[index].lazy *(rig - lef + 1);
    if (tree[index].correctArea(lef, rig)) return ans + tree[index].sum;
    if (lef <= tree[index].mid) ans += query(index << 1, lef, min(rig, tree[index].mid));
    if (rig > tree[index].mid) ans += query((index << 1) + 1, max(lef, tree[index].mid + 1), rig);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, q, x, y;
    long long val;
    cin >> n >> m;
    build(1, 1, n);
    while (m--) {
        cin >> q >> x >> y;
        if (q == 1) {
            cin >> val;
            update(1, x, y, val);
        } else {
            val = query(1, x, y);
            if (y < x) swap(x, y);
            cout << val << "\n";
        }
    }
    return 0;
}