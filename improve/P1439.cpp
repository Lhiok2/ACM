/*
P1439: [模板]最长公共子序列
https://www.luogu.com.cn/problem/P1439
*/
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int max_n = 1e5 + 5;
const int inf = -0x3f3f3f3f;
int N, arr[max_n], tree[max_n << 2];
unordered_map<int, int> index (max_n << 1);

inline void build(int n) {
    register int i, i2;
    for (N = 1; N <= n + 1; N <<= 1);
}

inline void update(int x, int val) {
    register int i = N + x, max_v;
    tree[i] += val;
    while (i > 1) {
        max_v = max(tree[i], tree[i ^ 1]);
        tree[i] -= max_v;
        tree[i ^ 1] -= max_v;
        i >>= 1;
        tree[i] += max_v;
    }
}

inline int query(int lef, int rig) {
    register int i, j, max_l = inf, max_r = inf, ans;
    register bool vl = false, vr = false;
    for (i = lef + N - 1, j = rig + N + 1; i ^ j ^ 1; i >>= 1, j >>= 1) {
        max_l += tree[i];
        max_r += tree[j];
        if (~i & 1) {
            if (!vl) {
                vl = true;
                max_l = tree[i ^ 1];
            } else max_l = max(max_l, tree[i ^ 1]);
        }
        if (j & 1) {
            if (!vr) {
                vr = true;
                max_r = tree[j ^ 1];
            } else max_r = max(max_r, tree[j ^ 1]);
        }
    }
    ans = max(max_l + tree[i], max_r + tree[j]);
    for (i >>= 1; i; i >>= 1) ans += tree[i];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    register int n, x, i;
    cin >> n;
    build(n);
    for (i = 1; i <= n; ++i) cin >> arr[i];
    for (i = 1; i <= n; ++i) {
        cin >> x;
        index[x] = i;
    }
    for (i = 1; i <= n; ++i) {
        x = query(1, index[arr[i]]) + 1;
        update(index[arr[i]], x);
    }
    cout << query(1, n) << endl;
    return 0;
}