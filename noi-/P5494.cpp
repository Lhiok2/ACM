/*
P5494: [模板]线段树分裂
https://www.luogu.com.cn/problem/P5494
*/
#include <iostream>
#include <algorithm>
#define _N 200005
#define _M 4000010
using namespace std;

long long _si[_M];
int _cnt, _root[_N];
int _cnt_2, _ls[_M], _rs[_M];

inline void update(int x) {
	_si[x] = _si[_ls[x]] + _si[_rs[x]];
}

int build(int l, int r) {
	if (l == r) {
		int si;
		cin >> si;
		if (!si) return 0;
		_si[++_cnt_2] = si;
		return _cnt_2;
	}
	int mid = l + r >> 1;
	int ls = build(l, mid), rs = build(mid+1, r);
	if (!ls && !rs) return 0;
	_ls[++_cnt_2] = ls;
	_rs[_cnt_2] = rs;
	update(_cnt_2);
	return _cnt_2;
}

void split(int& x, int& y, int tl, int tr, int l, int r) {
	if (tl <= l && tr >= r) {
		y = x;
		x = 0;
		return;
	}
	y = ++_cnt_2;
	int mid = l + r >> 1;
	if (tl <= mid) split(_ls[x], _ls[y], tl, tr, l, mid);
	if (tr > mid) split(_rs[x], _rs[y], tl, tr, mid+1, r);
	update(x);
	update(y);
}

void merge(int& x, int y, int l, int r) {
	if (!y) return;
	if (!x) {
		x = y;
		return;
	}
	int mid = l + r >> 1;
	_si[x] += _si[y];
	merge(_ls[x], _ls[y], l, mid);
	merge(_rs[x], _rs[y], mid+1, r);
}

void update(int& x, int tar, long long val, int l, int r) {
	if (!x) x = ++_cnt_2;
	_si[x] += val;
	if (l == r) return;
	int mid = l + r >> 1;
	if (tar <= mid) update(_ls[x], tar, val, l, mid);
	else update(_rs[x], tar, val, mid+1, r);
}

long long query(int x, int tl, int tr, int l, int r) {
	if (!x) return 0ll;
	if (tl <= l && tr >= r) return _si[x];
	int mid = l + r >> 1;
	if (tr <= mid) return query(_ls[x], tl, tr, l, mid);
	if (tl > mid) return query(_rs[x], tl, tr, mid+1, r);
	return query(_ls[x], tl, tr, l, mid) + query(_rs[x], tl, tr, mid+1, r);
}

int query(int x, long long rk, int l, int r) {
	if (_si[x] < rk) return -1;
	if (l == r) return l;
	int mid = l + r >> 1;
	long long lsi = _si[_ls[x]];
	if (lsi >= rk) return query(_ls[x], rk, l, mid);
	return query(_rs[x], rk-lsi, mid+1, r);
}

inline void solve() {
	long long k;
	int n, m, x, y, p, q, t, op;
	cin >> n >> m;
	_root[++_cnt] = build(1, n);
	while (m--) {
		cin >> op;
		switch (op) {
			case 0:
				cin >> p >> x >> y;
				split(_root[p], _root[++_cnt], x, y, 1, n);
				break;
			case 1:
				cin >> p >> t;
				merge(_root[p], _root[t], 1, n);
				break;
			case 2:
				cin >> p >> x >> q;
				update(_root[p], q, x, 1, n);
				break;
			case 3:
				cin >> p >> x >> y;
				cout << query(_root[p], x, y, 1, n) << '\n';
				break;
			case 4:
				cin >> p >> k;
				cout << query(_root[p], k, 1, n) << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}