/*
P3387: [模板]缩点
https://www.luogu.com.cn/problem/P3387
*/
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int max_n = 1e4 + 5;
const int max_m = 1e5 + 5;
queue<int> _que;
bool _exists[max_n];
vector<int> _vec, _color[max_n];
int _cnt, _cnt_2, _w[max_n], _w_2[max_n], _dfn[max_n], _low[max_n], _c[max_n];
int _dis[max_n], _vis_2[max_n], _fir[max_n], _nex[max_m], _road[max_m];

void tarjan(int u) {
    int i, v;
    _dfn[u] = ++_cnt;
    _low[u] = _cnt;
    _vec.push_back(u);
    for (i = _fir[u]; i; i = _nex[i]) {
        v = _road[i];
        if (_c[v]) continue;
        if (!_dfn[v]) tarjan(v);
        if (_low[v] < _low[u]) _low[u] = _low[v];
    }
    if (_dfn[u] == _low[u]) {
        ++_cnt_2;
        do {
            _c[_vec.back()] = _cnt_2;
            _color[_cnt_2].push_back(_vec.back());
            _vec.pop_back();
        } while (_color[_cnt_2].back() != u);
    }
}

inline void spfa() {
    register int i, u, u2, v, v2;
    for (i = 1; i <= _cnt_2; ++i) {
        for (int u : _color[i]) _w_2[i] += _w[u];
        _dis[i] = _w_2[i];
        _que.push(i);
        _exists[i] = true;
    }
    while(!_que.empty()) {
        u = _que.front();
        _que.pop();
        if (++_vis_2[u] > _cnt_2) return;
        _exists[u] = false;
        for (int u2 : _color[u]) {
            for (i = _fir[u2]; i; i = _nex[i]) {
                v2 = _road[i];
                v = _c[v2];
                if (u == v) continue;
                if (_dis[u] + _w_2[v] > _dis[v]) {
                    _dis[v] = _dis[u] + _w_2[v];
                    if (!_exists[v]) {
                        _exists[v] = true;
                        _que.push(v);
                    }
                }
            }
        }
    }
}

inline void solve() {
    register int n, m, i, u, v, cnt = 0, ans = 0;
    cin >> n >> m;
    for (i = 1; i <= n; ++i) cin >> _w[i];
    while (m--) {
        cin >> u >> v;
        _nex[++cnt] = _fir[u];
        _fir[u] = cnt;
        _road[cnt] = v;
    }
    for (i = 1; i <= n; ++i) if (!_dfn[i]) tarjan(i);
    spfa();
    for (i = 1; i <= _cnt_2; ++i) if (_dis[i] > ans) ans = _dis[i];
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}