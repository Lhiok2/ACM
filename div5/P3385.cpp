/*
P3385: 负环
https://www.luogu.com.cn/problem/P3385
*/
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

const int max_n = 2005;
const int max_m = 3005;
bool _exists[max_n];
int _vis[max_n], _fir[max_n], _nex[max_m << 1], _road[max_m << 1];
long long _dis[max_n], _w[max_m << 1];
queue<int> _que;

inline void init(int n) {
    for (register int i = 1; i <= n; ++i) {
        _exists[i] = false;
        _vis[i] = _fir[i] = 0;
        _dis[i] = __LONG_LONG_MAX__;
    }
    while (!_que.empty()) _que.pop();
}

inline int spfa(int n) {
    register int i, u, v;
    _dis[1] = 0;
    _que.push(1);
    _exists[1] = true;
    while (!_que.empty()) {
        u = _que.front();
        _que.pop();
        if (++_vis[u] > n) return -1;
        _exists[u] = false;
        for (i = _fir[u]; i; i = _nex[i]) {
            v = _road[i];
            if (_w[i] + _dis[u] < _dis[v]) {
                _dis[v] = _dis[u] + _w[i];
                if (!_exists[v]) {
                    _exists[v] = true;
                    _que.push(v);
                }
            }
        }
    }
    return 0;
}

inline void solve() {
    register int n, m, u, v, cnt = 0;
    register long long w;
    cin >> n >> m;
    init(n);
    while (m--) {
        cin >> u >> v >> w;
        _nex[++cnt] = _fir[u];
        _fir[u] = cnt;
        _road[cnt] = v;
        _w[cnt] = w;
        if (w >= 0) {
            _nex[++cnt] = _fir[v];
            _fir[v] = cnt;
            _road[cnt] = u;
            _w[cnt] = w;
        }
    }
    cout << (~spfa(n)? "NO": "YES") << '\n';
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