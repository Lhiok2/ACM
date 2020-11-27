/*
P3811: [模板]乘法逆元-费马小定理
https://www.luogu.com.cn/problem/P3811
*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize(s)
#include <cstdio>
#define modp(x) ((x) % p)
#define pri_cnt pri[0]

const int max_n = 3e6 + 5;
const int pri_size = 1e6 + 5;
long long ans[max_n], pri[pri_size];
bool vis[max_n];

inline int fastPower(long long a, long long k, long long p) {
    long long ans = 1;
    while (k) {
        if (k & 1) ans = modp(ans * a);
        a = modp(a * a);
        k >>= 1;
    }
    return ans;
}

inline void pre(int n, long long p) {
    int i, j;
    ans[1] = 1;
    for (i = 2; i <= n; ++i) {
        if (!vis[i]) {
            pri[++pri_cnt] = i;
            ans[i] = fastPower(i, p-2, p);
        }
        for (j = 1; j <= pri_cnt; ++j) {
            if (i * pri[j] > n || i % pri[j] == 0) break;
            vis[i * pri[j]] = true;
            ans[i * pri[j]] = modp(ans[i] * ans[pri[j]]);
        }
    }
}

int main() {
    int n, p;
    scanf("%d %d", &n, &p);
    pre(n, p);
    for (int i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
    return 0;
}