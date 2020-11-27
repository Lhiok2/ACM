/*
P3368: [模板]树状树组2
https://www.luogu.com.cn/problem/P3368
*/
#include <iostream>
#include <algorithm>
#define now_p (i & 1)
#define las_p ((i & 1) ^ 1)
#define lowbit(x) (x & -x)
using namespace std;

const int max_n = 5e5 + 5;
long long arr[max_n];

inline void update(int index, long long val) {
    for ( ; index < max_n; index += lowbit(index)) arr[index] += val;
}

inline void build(int n) {
    long long tmp[2] = { 0, 0 };
    for (int i = 1; i <= n; ++i) {
        cin >> tmp[now_p];
        update(i, tmp[now_p] - tmp[las_p]);
    }
}

inline long long get(int index) {
    long long ans = 0;
    for ( ; index; index ^= lowbit(index)) ans += arr[index];
    return ans;
}

inline void update() {
    int lef, rig, val;
    cin >> lef >> rig >> val;
    update(lef, val);
    update(rig + 1, -val);
}

inline void query() {
    int index;
    cin >> index;
    cout << get(index) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, q, lef, rig;
    long long val;
    cin >> n >> m;
    build(n);
    while (m--) {
        cin >> q;
        if (q == 1) update();
        else query();
    }
    return 0;
}