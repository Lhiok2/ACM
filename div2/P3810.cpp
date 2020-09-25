/*
P3810: 三维偏序（陌上花开）
https://www.luogu.com.cn/problem/P3810
*/
#include <iostream>
#include <algorithm>
#define _N 100005
#define _M 800005
using namespace std;

struct COORD {
	int x, y, z;
	
	inline void read() {
		cin >> x >> y >> z;
	}
	
	bool operator < (const COORD& t) const {
	    return x != t.x? x < t.x:
			y != t.y? y < t.y:
				z < t.z;
	}
	
	bool operator == (const COORD& t) const {
		return x == t.x && y == t.y && z == t.z;
	}
} _point[_N], _tmp[_N];

int _cnt, _ti[_N], _ans[_M], _zkw[_M];

inline void update(int x) {
	for ( ; x; x >>= 1) ++_zkw[x];
}

inline void init(int x) {
	for ( ; x && _zkw[x]; x >>= 1) _zkw[x] = 0;
}

inline int query(int r) {
    if (r <= _cnt) return 0;
	int l = _cnt, ans = 0;
	for (++r; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if (~l & 1) ans += _zkw[l ^ 1];
		if (r & 1) ans += _zkw[r ^ 1];
	}
	return ans;
}

void CDQ(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	CDQ(l, mid);
	CDQ(mid+1, r);
	int i = l, j = mid + 1, k = 0, si = r - l;
	while (k <= si) {
		if (j > r || (i <= mid && _point[i].y <= _point[j].y)) {
			update(_point[i].z);
			_tmp[k++] = _point[i++];
		} else {
			_ti[_point[j].x] += query(_point[j].z);
			_tmp[k++] = _point[j++];
		}
	}
	// 初始化zkw-tree
	for (k = 0; k <= si; ) {
		init(_tmp[k].z);
		_point[l++] = _tmp[k++];
	}
}

inline void solve() {
	register int i, n, m;
	cin >> n >> m;
	for (_cnt = 1; _cnt <= m; _cnt <<= 1);
	for (i = 1; i <= n; ++i) _point[i].read();
	// 三维 x/y/z
	sort(_point + 1, _point + n + 1);
	// 相同坐标加贡献
	for (i = n - 1; i > 0; --i) if (_point[i] == _point[i+1]) _ti[i] = _ti[i+1] + 1;
	// 坐标处理
	for (i = 1; i <= n; ++i) {
		_point[i].x = i;
		_point[i].z += _cnt;
	}
	CDQ(1, n);
	for (i = 1; i <= n; ++i) ++_ans[_ti[i]];
	for (i = 0; i < n; ++i) cout << _ans[i] << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}