/*
P3811: 乘法逆元-费马小定理
https://www.luogu.com.cn/problem/P3811
*/
#include <cstdio>
#define modp(x) ((x) % p)

const int max_n = 3e6 + 5;
long long ans[max_n];

inline void pre(int n, long long p) {
    ans[0] = ans[1] = 1ll;
    for (int i = 2; i <= n; ++i) ans[i] = modp((p - p / i) * ans[p % i]);
}

int main() {
    int n, p;
    scanf("%d %d", &n, &p);
    pre(n, p);
    for (int i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
    return 0;
}