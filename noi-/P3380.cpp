/*
P3380: [模板]二逼平衡树（树套树）
https://www.luogu.com.cn/problem/P3380
*/
#include <iostream>
#include <algorithm>
#define _N 50005
#define _N_4 200010
#define _N_50 2500005
#define _SEED 11511111
#define _INF 2147483647
#define _INF_NEG -2147483647
using namespace std;

struct NODE {
	int si, ls, rs, key, val;
} _fhq[_N_50];

int _x, _y, _z, _n, _cnt, _seed = 1, _arr[_N], _seg[_N_4];

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
		if (_fhq[cur].val <= val) {
			l = cur;
			split(_fhq[l].rs, _fhq[l].rs, r, val);
			update(l);
		} else {
			r = cur;
			split(_fhq[r].ls, l, _fhq[r].ls, val);
			update(r);
		}
	}
}

int merge(int x, int y) {
	if (!x || !y) return x | y;
	if (_fhq[x].key > _fhq[y].key) {
		_fhq[x].rs = merge(_fhq[x].rs, y);
		update(x);
		return x;
	}
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

void build(int cur, int l, int r) {
	for (int i = l; i <= r; ++i) insert(_seg[cur], _arr[i]);
	if (l == r) return;
	build(cur << 1, l, l + r >> 1);
	build(cur << 1 | 1, (l + r >> 1) + 1, r);
}

inline void update(int p, int val) {
	for (int l = 1, r = _n, cur = 1, mid; ; ) {
		del(_seg[cur], _arr[p]);
		insert(_seg[cur], val);
		if (l == r) break;
		mid = l + r >> 1;
		if (p <= mid) {
			cur <<= 1;
			r = mid;
		} else {
			cur = cur << 1 | 1;
			l = mid + 1;
		}
	}
	_arr[p] = val;
}

inline void up(int& x, int y) {
	if (x < y) x = y;
}

inline void down(int& x, int y) {
	if (x > y) x = y;
}

inline int ranks(int& root, int val) {
	split(root, _x, _y, val - 1);
	_z = _fhq[_x].si;
	root = merge(_x, _y);
	return _z;
}

inline int ranks(int cur, int l, int r, int l_bound, int r_bound, int val) {
	if (l >= l_bound && r <= r_bound) return ranks(_seg[cur], val);
	int rk = 0, mid = l + r >> 1;
	if (mid >= l_bound) rk += ranks(cur << 1, l, mid, l_bound, r_bound, val);
	if (mid < r_bound) rk += ranks(cur << 1 | 1, mid + 1, r, l_bound, r_bound, val);
	return rk;
}

inline int query(int l, int r, int rk) {
	int i = 0, j = 100000000, k;
	while (i <= j) {
		k = (i + j) >> 1;
		if (ranks(1, 1, _n, l, r, k) >= rk) j = k - 1;
		else i = k + 1;
	}
	return j;
}

inline int pre(int& root, int val) {
	split(root, _x, _y, val - 1);
	for (_z = _x; _fhq[_z].rs; _z = _fhq[_z].rs);
	root = merge(_x, _y);
	return _z? _fhq[_z].val: _INF_NEG;
}

inline int pre(int cur, int l, int r, int l_bound, int r_bound, int val) {
	if (l >= l_bound && r <= r_bound) return pre(_seg[cur], val);
	int mid = l + r >> 1;
	if (mid >= l_bound && mid < r_bound) return max(pre(cur << 1, l, mid, l_bound, r_bound, val), pre(cur << 1 | 1, mid + 1, r, l_bound, r_bound, val));
	if (mid >= l_bound) return pre(cur << 1, l, mid, l_bound, r_bound, val);
	return pre(cur << 1 | 1, mid + 1, r, l_bound, r_bound, val);
}

inline int suf(int& root, int val) {
	split(root, _x, _y, val);
	for (_z = _y; _fhq[_z].ls; _z = _fhq[_z].ls);
	root = merge(_x, _y);
	return _z? _fhq[_z].val: _INF;
}

inline int suf(int cur, int l, int r, int l_bound, int r_bound, int val) {
	if (l >= l_bound && r <= r_bound) return suf(_seg[cur], val);
	int mid = l + r >> 1;
	if (mid >= l_bound && mid < r_bound) return min(suf(cur << 1, l, mid, l_bound, r_bound, val), suf(cur << 1 | 1, mid + 1, r, l_bound, r_bound, val));
	if (mid >= l_bound) return suf(cur << 1, l, mid, l_bound, r_bound, val);
	return suf(cur << 1 | 1, mid + 1, r, l_bound, r_bound, val);
}

inline void solve() {
	int i, m, x, l, r, p, opt;
	cin >> _n >> m;
	for (i = 1; i <= _n; ++i) cin >> _arr[i];
	build(1, 1, _n);
	while (m--) {
		cin >> opt;
		if (opt == 3) {
			cin >> p >> x;
			update(p, x);
		} else {
			cin >> l >> r >> x;
			if (opt == 1) cout << ranks(1, 1, _n, l, r, x) + 1 << '\n';
			if (opt == 2) cout << query(l, r, x) << '\n';
			if (opt == 4) cout << pre(1, 1, _n, l, r, x) << '\n';
			if (opt == 5) cout << suf(1, 1, _n, l, r, x) << '\n';
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