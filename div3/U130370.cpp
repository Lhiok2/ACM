/*
U130370: 二维凸包（加强版）
https://www.luogu.com.cn/problem/U130370
*/
#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

const int _N = 1e6 + 5;
bool _used[_N];
int _stk[_N];

struct COORD {
	long long x, y;
	
	COORD() {}
	COORD(long long x, long long y) {
		this->x = x;
		this->y = y;
	}
	
	inline void read() {
		cin >> x >> y;
	}
	
	inline double distance() {
		return sqrt(x * x + y * y);
	}
	
	bool operator < (const COORD& t) const {
		return x == t.x? y < t.y: x < t.x;
	}
	
	bool operator == (const COORD& t) const {
		return x == t.x && y == t.y;
	}
	
	COORD operator - (const COORD& t) const {
		return COORD(x - t.x, y - t.y);
	}
	
	long long operator * (const COORD& t) const {
		return x * t.y - t.x * y;
	}
} _point[_N];

vector<COORD> _down, _up;

inline long long getArea(COORD a, COORD b, COORD c) {
	return abs((b - a) * (c - a));
}

inline int judge(COORD a, COORD b, COORD c, COORD d) {
	if (a * b == 0 || c * d == 0) return 0;
	return a * b < 0 && c * d < 0? 1: -1;
}

inline void solve() {
	register double c = 0;
	register int i, j, n, m, cnt = 0;
	register long long area = 0ll;
	cin >> n >> m;
	for (i = 1; i <= n; ++i) _point[i].read();
	sort(_point + 1, _point + n + 1);
	_stk[++cnt] = 1;
	for (i = 2; i <= n; ++i) {
		while (cnt >= 2 &&
			(_point[_stk[cnt-1]] - _point[_stk[cnt]]) * (_point[_stk[cnt]] - _point[i]) <= 0ll) 
				_used[_stk[cnt--]] = false;
		_used[i] = true;
		_stk[++cnt] = i;
	}
	for (i = n-1; i; --i) {
		if (_used[i]) continue;
		while (_stk[cnt] != n &&
			(_point[_stk[cnt-1]] - _point[_stk[cnt]]) * (_point[_stk[cnt]] - _point[i]) <= 0ll) --cnt;
		_stk[++cnt] = i;
	}
	_down.push_back(_point[1]);
	for (i = 2; ; ++i) {
		_down.push_back(_point[_stk[i]]);
		c += (_point[_stk[i]] - _point[_stk[i-1]]).distance();
		area += getArea(_point[1], _point[_stk[i-1]], _point[_stk[i]]);
		if (_stk[i] == n) break;
	}
	for (j = cnt; j > i; --j) {
		_up.push_back(_point[_stk[j]]);
		c += (_point[_stk[j]] - _point[_stk[j-1]]).distance();
		area += getArea(_point[1], _point[_stk[j-1]], _point[_stk[j]]);
	}
	_up.push_back(_point[n]);
	cout << fixed << setprecision(0) << c << '\n' << area << '\n';
	while (m--) {
		_point[0].read();
		if (_point[0] == _point[1]) {
			cout << 0 << '\n';
			continue;
		} else if (_point[0] < _point[1] || _point[n] < _point[0]) {
			cout << -1 << '\n';
			continue;
		}
		i = lower_bound(_down.begin(), _down.end(), _point[0]) - _down.begin();
		j = lower_bound(_up.begin(), _up.end(), _point[0]) - _up.begin();
		cout << judge(_down[i-1] - _point[0], _point[0] - _down[i], _up[j] - _point[0], _point[0] - _up[j-1]) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}