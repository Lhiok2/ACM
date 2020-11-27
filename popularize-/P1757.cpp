/*
P1757: 通天之分组背包(分组背包)
https://www.luogu.com.cn/problem/P1757
*/
#include <vector>
#include <iostream>
#include <algorithm>
#define _N 1005
using namespace std;

struct PAIR {
	int x, y;
	
	PAIR() {}
	PAIR(int x, int y) : x(x), y(y) {}
};

int _dp[_N][_N];
vector<PAIR> _group[_N];

inline void up(int& x, int y) {
	if (x < y) x = y;
}

inline void solve() {
	int i, j, n, m, a, b, c;
	cin >> m >> n;
	while (n--) {
		cin >> a >> b >> c;
		_group[c].push_back(PAIR(a, b));
	}
	for (i = 1; i < _N; ++i) {
		for (j = 1; j <= m; ++j) _dp[i][j] = _dp[i-1][j];
		for (PAIR p : _group[i])
			for (j = m; j >= p.x; --j)
				up(_dp[i][j], _dp[i-1][j-p.x] + p.y);
	}
	cout << _dp[_N-1][m] << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}