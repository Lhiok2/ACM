/*
P3807: 卢卡斯定理
https://www.luogu.com.cn/problem/P3807
*/
#include <iostream>
#include <algorithm>
#define modp(x) ((x) % p)
using namespace std;

const int max_n = 1e5 + 5;
long long p, fact[max_n];

inline long long inv(long long x) {
    long long k = p - 2ll, ans = 1ll;
    while (k) {
        if (k & 1ll) ans = modp(ans * x);
        x = modp(x * x);
        k >>= 1;
    }
    return ans;
}

inline long long C(long long n, long long m) {
    return m < n? 0ll: modp(fact[m] * modp(inv(fact[n]) * inv(fact[m - n])));
}

long long lucas(long long n, long long m) {
    return n == 0ll? 1ll: modp(lucas(n / p, m / p) * C(n % p, m % p));
}

inline void solve() {
    register long long i, n, m;
    cin >> n >> m >> p;
    fact[0] = 1ll;
    for (i = 1ll; i < p; ++i) fact[i] = modp(fact[i - 1] * i);
    cout << lucas(n, n + m) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}