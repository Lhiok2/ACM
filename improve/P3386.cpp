/*
P3386: [模板]二分图最大匹配
https://www.luogu.com.cn/problem/P3386
*/
#include <vector>
#include <iostream>
#include <algorithm>
#define _N 505
using namespace std;

int _vis[_N], _link[_N];
vector<int> _v[_N];

bool match(int x, int ti) {
	if (_vis[x] == ti) return false;
	_vis[x] = ti;
	for (int v : _v[x]) {
		if (_link[v] && !match(_link[v], ti)) continue;
		_link[v] = x;
		return true;
	}
	return false;
}

inline void solve() {
	int i, j, k, n, m, u, v, cnt = 0;
	cin >> n >> m >> k;
	while (k--) {
		cin >> u >> v;
		_v[u].push_back(v);
	}
	for (i = 1; i <= n; ++i) if (match(i, i)) ++cnt;
	cout << cnt << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}