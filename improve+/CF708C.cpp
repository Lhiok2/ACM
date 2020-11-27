/*
CF708C: Centroids(换根DP)
https://www.luogu.com.cn/problem/CF708C
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int max_n = 4e5 + 5;
int _fir[max_n], _nex[max_n << 1], _v[max_n << 1];
int _n, _half, _si[max_n];
pair<int, int> _dp[max_n][2];
bool _bad[max_n];

inline void up(int x, pair<int, int> p) {
    if (p.second > _half) return;
    if (p.second > _dp[x][0].second) {
        if (_dp[x][0].first != p.first) _dp[x][1] = _dp[x][0];
        _dp[x][0] = p;
    } else if (_dp[x][0].first != p.first && p.second > _dp[x][1].second) _dp[x][1] = p;
}

void dfs1(int u, int fa) {
    _si[u] = 1;
    for (int i = _fir[u], v; i; i = _nex[i]) {
        v = _v[i];
        if (v == fa) continue;
        dfs1(v, u);
        _si[u] += _si[v];
        up(u, { v, _si[v] });
        up(u, { v, _dp[v][0].second });
    }
}

void dfs2(int u, int fa) {
    if (_dp[fa][0].first == u) up(u, _dp[fa][1]);
    else up(u, _dp[fa][0]);
    up(u, { fa, _si[fa] });
    for (int i = _fir[u], v, w; i; i = _nex[i]) {
        v = _v[i];
        w = _si[v] - (_dp[v][0].first == u? _dp[v][1].second: _dp[v][0].second);
        if (w > _half) _bad[u] = true;
        if (v == fa) continue;
        _si[u] = _n - _si[v];
        dfs2(v, u);
    }
}

inline void build() {
    register int i, j, u, v;
    cin >> _n;
    _half = _n >> 1;
    for (i = 1, j = max_n; i < _n; ++i, ++j) {
        cin >> u >> v;
        _nex[i] = _fir[u];
        _fir[u] = i;
        _v[i] = v;
        _nex[j] = _fir[v];
        _fir[v] = j;
        _v[j] = u;
    }
    dfs1(1, 0);
    dfs2(1, 0);
}

inline void solve() {
    for (register int i = 1; i <= _n; ++i) cout << (_bad[i]? 0: 1) << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    build();
    solve();
    return 0;
}