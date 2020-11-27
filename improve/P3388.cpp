/*
P3388: [模板]割点(割顶)
https://www.luogu.com.cn/problem/P3388
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int max_n = 2e4 + 5;
vector<int> _road[max_n], _ans;
bool _taken[max_n];
int _cnt, _dfn[max_n], _low[max_n];

inline void down(int& x, int y) {
    if (y < x) x = y;
}

void tarjan(int u, int fa) {
    _dfn[u] = _low[u] = ++_cnt;
    for (int v : _road[u]) {
        if (v == fa) continue;
        if (!_dfn[v]) {
            tarjan(v, u);
            down(_low[u], _low[v]);
            if (_low[v] >= _dfn[u] && !_taken[u]) {
                _taken[u] = true;
                _ans.push_back(u);
            }
        } else down(_low[u], _dfn[v]);
    }
}

inline void solve() {
    register int i, n, m, u, v, son_num;
    cin >> n >> m;
    while (m--) {
        cin >> u >> v;
        _road[u].push_back(v);
        _road[v].push_back(u);
    }
    for (i = 1; i <= n; ++i) {
        if (_dfn[i]) continue;
        son_num = 0;
        _dfn[i] = _low[i] = ++_cnt;
        for (int j : _road[i]) {
            if (_dfn[j]) continue;
            ++son_num;
            tarjan(j, i);
        }
        if (son_num > 1 && !_taken[i]) {
            _taken[i] = true;
            _ans.push_back(i);
        }
    }
    sort(_ans.begin(), _ans.end());
    cout << _ans.size() << '\n';
    for (int j : _ans) cout << j << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}