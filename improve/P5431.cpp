/*
P5431: [模板]乘法逆元2
https://www.luogu.com.cn/problem/P5431
*/
#pragma GCC optimize("Ofast")
#include <cstdio>
#define modp(x) ((x) % p)

inline int read() {
    register int x = 0, w = 1;
    register int ch = getchar();
    while (ch < 48 || ch > 57) {
        if (ch == 45) w = -1;
        ch = getchar();
    }
    while (ch > 47 && ch < 58) {
        x = (x << 1) + (x << 3) + ch - 48;
        ch = getchar();
    }
    return x;
}

const int max_n = 5e6 + 5;
long long p, deno[max_n], pre[max_n], suf[max_n];

inline long long fastPow(long long x, long long k) {
    register long long ans = 1ll;
    while (k) {
        if (k & 1ll) ans = modp(ans * x);
        x = modp(x * x);
        k >>= 1;
    }
    return ans;
}

int main() {
    register int i, n;
    register long long k, mole, ans = 0;
    n = read();
    p = read();
    k = read();
    for (i = 1, pre[1] = 1; i <= n; ++i) {
        deno[i] = read();
        pre[i+1] = modp(pre[i] * deno[i]);
    }
    for (i = n, suf[n] = 1; i > 1; --i) suf[i-1] = modp(suf[i] * deno[i]);
    for (i = 1, mole = k; i <= n; ++i, mole = modp(mole * k)) ans = modp(ans + modp(mole * modp(pre[i] * suf[i])));
    printf("%lld\n", modp(ans * fastPow(pre[n+1], p - 2)));
    return 0;
}