/*
P3919: [模板]可持久化线段树 1（可持久化数组）
https://www.luogu.com.cn/problem/P3919
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int _N = 1e6 + 5;
int _cnt, _root[_N];
int _ls[_N*20], _rs[_N*20], _val[_N*20];

int build(int l, int r) {
	int x = ++_cnt;
	if (l == r) cin >> _val[x];
	else {
		int mid = l + r >> 1;
		_ls[x] = build(l, mid);
		_rs[x] = build(mid+1, r);
	}
	return x;
}

int update(int cur, int l, int r, int tar) {
	int x = ++_cnt;
	if (l == r) cin >> _val[x];
	else {
		int mid = l + r >> 1;
		if (tar <= mid) {
			_ls[x] = update(_ls[cur], l, mid, tar);
			_rs[x] = _rs[cur];
		} else {
			_ls[x] = _ls[cur];
			_rs[x] = update(_rs[cur], mid+1, r, tar);
		}
	}
	return x;
}

int query(int cur, int l, int r, int tar) {
	if (l == r) return _val[cur];
	int mid = l + r >> 1;
	if (tar <= mid) return query(_ls[cur], l, mid, tar);
	return query(_rs[cur], mid+1, r, tar);
}

inline void solve() {
	register int i, n, m, v, t, loc;
	cin >> n >> m;
	_root[0] = build(1, n);
	for (i = 1; i <= m; ++i) {
		cin >> v >> t >> loc;
		if (t == 1) _root[i] = update(_root[v], 1, n, loc);
		else cout << query(_root[i] = _root[v], 1, n, loc) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}