/*
P1429: 平面最近点对（加强版）
https://www.luogu.com.cn/problem/P1429
*/
#include <set>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define _N 200005
using namespace std;

struct COORD {
	double x, y;
	
	inline void read() {
		cin >> x >> y;
	}
	
	inline double distance() {
		return sqrt(x * x + y * y);
	}
	
	COORD() {}
	COORD(double x, double y) {
		this->x = x;
		this->y = y;
	}
	
	COORD operator - (const COORD& t) const {
		return COORD(x - t.x, y - t.y);
	}
	
	bool operator < (const COORD& t) const {
		return y == t.y? x < t.x: y < t.y;
	}
} _point[_N];

inline void down(double& x, double y) {
	if (x > y) x = y;
}

multiset<COORD> _set;

inline void solve() {
	register double ans;
	register int i, j, n;
	register multiset<COORD>::iterator it;
	cin >> n;
	for (i = 1; i <= n; ++i) _point[i].read();
	sort(_point + 1, _point + n + 1, [](COORD a, COORD b) {
		return a.x == b.x? a.y < b.y: a.x < b.x;
	});
	ans = (_point[2] - _point[1]).distance();
	// ans > 0.00001 防止RE
	for (i = j = 1; ans > 0.00001 && i <= n; ++i) {
		while (_point[i].x - _point[j].x >= ans) _set.erase(_point[j++]);
		for (it = _set.upper_bound(_point[i] - COORD(ans, ans));
			it != _set.end() && (*it).y < _point[i].y + ans; ++it)
				down(ans, (_point[i] - *it).distance());
		_set.insert(_point[i]);
	}
	cout << fixed << setprecision(4) << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}