/*
P3834: [模板]可持久化线段树 2（主席树）
https://www.luogu.com.cn/problem/P3834
*/
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int _N = 2e5 + 5;
const int _M = 4e6 + 5;
int _cnt, _ls[_M], _rs[_M], _si[_M], _root[_N];
unordered_map<int, int> _key, _val;

struct ARR {
	int p, val;
} _arr[_N];

int update(int cur, int l, int r, int tar) {
	int x = ++_cnt;
	_si[x] = _si[cur] + 1;
	if (l != r) {
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

int query(int lef, int rig, int l, int r, int k) {
	if (l == r) return _val[l];
	int si = _si[_ls[rig]] - _si[_ls[lef]];
	if (k <= si) return query(_ls[lef], _ls[rig], l, l + r >> 1, k);
	return query(_rs[lef], _rs[rig], (l + r >> 1) + 1, r, k - si);
}

inline void solve() {
	register int i, n, m, l, r, k, cnt = 0;
	cin >> n >> m;
	for (i = 1; i <= n; ++i) {
		_arr[i].p = i;
		cin >> _arr[i].val;
	}
	sort(_arr + 1, _arr + n + 1, [](ARR x, ARR y) {
		return x.val < y.val;
	});
	_val[++cnt] = _arr[1].val;
	_key[_arr[1].val] = cnt;
	for (i = 2; i <= n; ++i) {
		if (_arr[i].val == _arr[i-1].val) continue;
		_val[++cnt] = _arr[i].val;
		_key[_arr[i].val] = cnt;
	}
	sort(_arr + 1, _arr + n + 1, [](ARR x, ARR y) {
		return x.p < y.p;
	});
	for (i = 1; i <= n; ++i) _root[i] = update(_root[i-1], 1, cnt, _key[_arr[i].val]);
	while (m--) {
		cin >> l >> r >> k;
		cout << query(_root[l-1], _root[r], 1, cnt, k) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}