/*
P3380: 模板】二逼平衡树（树套树）
https://www.luogu.com.cn/problem/P3380
*/
#include <iostream>
#include <algorithm>
#define _N 50005
#define _N_4 200010
#define _N_1000 50000005
#define _SEED 11511111
#define _INF 2147483647
#define _INF_NEG -2147483647
using namespace std;

struct NODE {
	int si, ls, rs, key, val;
} _fhq[_N_1000];

int _x, _y, _z, _cnt, _bas, _seed = 1, _zkw[_N_4];

inline int newNode(int val) {
	_fhq[++_cnt].si = 1;
	_fhq[_cnt].val = val;
	_fhq[_cnt].key = _seed *= _SEED;
	return _cnt;
}

inline void update(int x) {
	_fhq[x].si = _fhq[_fhq[x].ls].si + _fhq[_fhq[x].rs].si + 1;
}

void split(int cur, int& l, int& r, int val) {
	if (!cur) l = r = 0;
	else {
		_fhq[++_cnt] = _fhq[cur];
		if (_fhq[_cnt].val <= val) {
			l = _cnt;
			split(_fhq[l].rs, _fhq[l].rs, r, val);
			update(l);
		} else {
			r = _cnt;
			split(_fhq[r].ls, l, _fhq[r].ls, val);
			update(r);
		}
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

inline void del(int& root, int val) {
	split(root, _x, _y, val);
	split(_x, _x, _z, val - 1);
	_z = merge(_fhq[_z].ls, _fhq[_z].rs);
	root = merge(merge(_x, _z), _y);
}

inline void insert(int& root, int val) {
	split(root, _x, _y, val);
	root = merge(merge(_x, newNode(val)), _y);
}

void dfs(int& root, int x) {
	if (!x) return;
	insert(root, _fhq[x].val);
	dfs(root, _fhq[x].ls);
	dfs(root, _fhq[x].rs);
}

inline void update(int p, int val) {
	int las = _fhq[_zkw[p]].val;
	for ( ; p; p >>= 1) {
		del(_zkw[p], las);
		insert(_zkw[p], val);
	}
}

inline void up(int& x, int y) {
	if (x < y) x = y;
}

inline void down(int& x, int y) {
	if (x > y) x = y;
}

inline int ranks(int root, int val) {
	split(root, _x, _y, val - 1);
	return _fhq[_x].si;
}

inline int ranks(int l, int r, int val) {
	int rk = 0;
	for (--l, ++r; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if (~l & 1) rk += ranks(_zkw[l^1], val);
		if (r & 1) rk += ranks(_zkw[r^1], val);
	}
	return rk + 1;
}

inline int query(int l, int r, int rk) {
	int i = 0, j = 100000000, k;
	while (i <= j) {
		k = (i + j) >> 1;
		if (ranks(l, r, k) > rk) j = k - 1;
		else i = k + 1;
	}
	return j;
}

inline int pre(int root, int val) {
	split(root, _x, _y, val - 1);
	for ( ; _fhq[_x].rs; _x = _fhq[_x].rs);
	return _x? _fhq[_x].val: _INF_NEG;
}

inline int pre(int l, int r, int val) {
	int ans = _INF_NEG;
	for (--l, ++r; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if (~l & 1) up(ans, pre(_zkw[l^1], val));
		if (r & 1) up(ans, pre(_zkw[r^1], val));
	}
	return ans;
}

inline int suf(int root, int val) {
	split(root, _x, _y, val);
	for ( ; _fhq[_y].ls; _y = _fhq[_y].ls);
	return _y? _fhq[_y].val: _INF;
}

inline int suf(int l, int r, int val) {
	int ans = _INF;
	for (--l, ++r; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if (~l & 1) down(ans, suf(_zkw[l^1], val));
		if (r & 1) down(ans, suf(_zkw[r^1], val));
	}
	return ans;
}

inline void solve() {
	int i, n, m, x, l, r, p, opt;
	cin >> n >> m;
	for (_bas = 1; _bas <= n; _bas <<= 1);
	for (i = 1; i <= n; ++i) {
		cin >> x;
		_zkw[_bas + i] = newNode(x);
	}
	for (i = _bas - 1; i; --i) {
		_zkw[i] = ++_cnt;
		_fhq[_cnt] = _fhq[_zkw[i<<1]];
		dfs(_zkw[i], _zkw[i<<1|1]);
	}
	while (m--) {
		cin >> opt;
		if (opt == 3) {
			cin >> p >> x;
			update(_bas + p, x);
		} else {
			cin >> l >> r >> x;
			l += _bas;
			r += _bas;
			if (opt == 1) cout << ranks(l, r, x) << '\n';
			if (opt == 2) cout << query(l, r, x) << '\n';
			if (opt == 4) cout << pre(l, r, x) << '\n';
			if (opt == 5) cout << suf(l, r, x) << '\n';
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