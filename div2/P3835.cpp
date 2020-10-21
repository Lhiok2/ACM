/*
P3835: 可持久化平衡树
https://www.luogu.com.cn/problem/P3835
*/
#include <iostream>
#include <algorithm>
#define _N 500005
#define _M 25000010
#define _SEED 11511111
#define _INF 0x7FFF
#define _INF_NEG 0xFFFF
using namespace std;

struct NODE {
	int ls, rs, si, key, val;
} _fhq[_M];

int _x, _y, _z, _cnt, _seed = 1, _root[_N];

inline void update(int x) {
	_fhq[x].si = _fhq[_fhq[x].ls].si + _fhq[_fhq[x].rs].si + 1;
}

inline int newNode(int val) {
	_fhq[++_cnt].si = 1;
	_fhq[_cnt].val = val;
	_fhq[_cnt].key = _seed *= _SEED;
	return _cnt;
}

void split(int cur, int& l, int& r, int val) {
	if (!cur) {
		l = r = 0;
		return;
	}
	_fhq[++_cnt] = _fhq[cur];
	if (_fhq[cur].val <= val) {
		l = _cnt;
		split(_fhq[l].rs, _fhq[l].rs, r, val);
		update(l);
	} else {
		r = _cnt;
		split(_fhq[r].ls, l, _fhq[r].ls, val);
		update(r);
	}
}

int merge(int x, int y) {
	if (!x || !y) return x | y;
	if (_fhq[x].key > _fhq[y].key) {
		_fhq[++_cnt] = _fhq[x];
		x = _cnt;
		_fhq[x].rs = merge(_fhq[x].rs, y);
		update(x);
		return x;
	}
	_fhq[++_cnt] = _fhq[y];
	y = _cnt;
	_fhq[y].ls = merge(x, _fhq[y].ls);
	update(y);
	return y;
}

inline void insert(int& root, int val) {
	split(root, _x, _y, val);
	root = merge(merge(_x, newNode(val)), _y);
}

inline void del(int& root, int val) {
	split(root, _x, _y, val);
	split(_x, _x, _z, val - 1);
	_z = merge(_fhq[_z].ls, _fhq[_z].rs);
	root = merge(merge(_x, _z), _y);
}

inline int ranks(int root, int val) {
	split(root, _x, _y, val - 1);
	return _fhq[_x].si + 1;
}

inline int query(int root, int rk) {
	while (true) {
		_x = _fhq[root].ls;
		if (_fhq[_x].si >= rk) root = _x;
		else {
			rk -= _fhq[_x].si + 1;
			if (!rk) return _fhq[root].val;
			root = _fhq[root].rs;
		}
	}
}

inline int pre(int root, int val) {
	split(root, _x, _y, val - 1);
	for ( ; _fhq[_x].rs; _x = _fhq[_x].rs);
	return _x? _fhq[_x].val: _INF_NEG;
}

inline int suf(int root, int val) {
	split(root, _x, _y, val);
	for (; _fhq[_y].ls; _y = _fhq[_y].ls);
	return _y? _fhq[_y].val: _INF;
}

inline void solve() {
	int i, n, v, x, opt;
	cin >> n;
	for (i = 1; i <= n; ++i) {
		cin >> v >> opt >> x;
		_root[i] = _root[v];
		if (opt == 1) insert(_root[i], x);
		else if (opt == 2) del(_root[i], x);
		else if (opt == 3) cout << ranks(_root[i], x) << '\n';
		else if (opt == 4) cout << query(_root[i], x) << '\n';
		else if (opt == 5) cout << pre(_root[i], x) << '\n';
		else cout << suf(_root[i], x) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}