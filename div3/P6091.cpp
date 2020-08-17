/*
P6091: 原根
https://www.luogu.com.cn/problem/P6091
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int max_n = 1e6 + 5;
bool _valid[max_n], _root[max_n];
int _prime[max_n];

inline void pre() {
    register int i, j;
    register long long k;
    bool notPrime[max_n] = { false };
    for (i = 2; i < max_n; ++i) {
        if (!notPrime[i]) _prime[++_prime[0]] = i;
        for (j = 1; j <= _prime[0]; ++j) {
            if (1ll * i * _prime[j] >= max_n) break;
            notPrime[i * _prime[j]] = true;
            if (!(i % _prime[j])) break;
        }
    }
    _valid[1] = _valid[2] = _valid[4] = true;
    for (i = 2; i <= _prime[0]; ++i) 
        for (k = _prime[i]; k < max_n; k *= _prime[i]) {
            _valid[k] = true;
            if (k << 1 < max_n) _valid[k << 1] = true;
        }
}

inline int euler(int n) {
    register int i, j, ans = n;
    for (i = 1; _prime[i] <= n; ++i) {
        if (n % _prime[i]) continue;
        ans = ans / _prime[i] * (_prime[i] - 1);
    }
    return ans;
}

int gcd(int x, int y) {
    return y? gcd(y, x % y): x;
}

inline int fastPow(long long x, int k, long long p) {
    long long ans = 1ll;
    while (k) {
        if (k & 1) ans = ans * x % p;
        x = x * x % p;
        k >>= 1;
    }
    return (int) ans;
}

inline int minRoot(int n, vector<int> fact) {
    if (n == 2) return 1;
    register int i, j;
    for (i = 2; ; ++i) {
        if (gcd(i, n) != 1) continue;
        j = 1;
        for (int _ : fact) if (fastPow(i, _, n) == 1) j = 0;
        if (j) return i;
    }
}

inline void allRoot(int n) {
    vector<int> fact;
    register int i, j, g, m = euler(n);
    bool illegal[max_n] = { false };
    cout << euler(m) << '\n';
    for (i = 0; i < n; ++i) _root[i] = false;
    for (i = 1; _prime[i] < m; ++i) {
        if (m % _prime[i]) continue;
        fact.push_back(m / _prime[i]);
        for (j = 1; 1ll * j * _prime[i] < max_n; ++j) illegal[j * _prime[i]] = true;
    }
    g = minRoot(n, fact);
    _root[g] = true;
    for (i = 2; i < m; ++i) {
        if (illegal[i]) continue;
        int tmp = fastPow(g, i, n);
        _root[fastPow(g, i, n)] = true;
    }
}

inline void solve() {
    register int i, j, n, d;
    cin >> n >> d;
    if (!_valid[n]) {
        cout << 0 << "\n\n";
        return;
    }
    allRoot(n);
    for (i = 1, j = 0; i < n; ++i) {
        if (!_root[i] || (++j) % d) continue;
        cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    pre();
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}