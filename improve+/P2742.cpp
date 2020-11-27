/*
P2742: [模板]二维凸包
https://www.luogu.com.cn/problem/P2742
*/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

const int _N = 1e5 + 5;
int _stk[_N];
bool _used[_N];

struct COORD {
	double x, y;
	
	COORD() {}
	COORD(double x, double y) {
		this->x = x;
		this->y = y;
	}
	
	inline void read() {
		cin >> x >> y;
	}
	
	inline double distance() {
		return sqrt(x * x + y * y);
	}
	
	COORD operator - (const COORD& t) const {
		return COORD(x - t.x, y - t.y);
	}
	
	double operator * (const COORD& t) const {
		return x * t.y - y * t.x;
	}
	
	bool operator < (const COORD& t) const {
		return x == t.x? y < t.y: x < t.x;
	}
} _point[_N];

inline void solve() {
	register int i, n, cnt = 0;
	register double ans = 0;
	cin >> n;
	for (i = 1; i <= n; ++i) _point[i].read();
	sort(_point + 1, _point + n + 1);
	_stk[++cnt] = 1;
	for (i = 2; i <= n; ++i) {
		while (cnt >= 2 &&
			(_point[_stk[cnt-1]] - _point[_stk[cnt]]) * (_point[_stk[cnt]] - _point[i]) <= 0)
				_used[_stk[cnt--]] = false;
		_stk[++cnt] = i;
		_used[i] = true;
	}
	for (i = n-1; i; --i) {
		if (_used[i]) continue;
		while (_stk[cnt] != n && 
			(_point[_stk[cnt-1]] - _point[_stk[cnt]]) * (_point[_stk[cnt]] - _point[i]) <= 0) --cnt;
		_stk[++cnt] = i;
	}
	for (i = 2; i <= cnt; ++i) ans += (_point[_stk[i]] - _point[_stk[i-1]]).distance();
	cout << fixed << setprecision(2) << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}