/*
P4182: [USACO18JAN]Lifeguards P (单调队列优化dp)
https://www.luogu.com.cn/problem/P4182
*/
#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;

struct PAIR {
	int first, second;
	
	PAIR() {}
	PAIR(int first, int second) {
		this->first = first;
		this->second = second;
	}
	
	bool operator < (const PAIR& t) const {
		return first == t.first? second > t.second: first < t.first;
	}
};

const int _N = 1e5 + 5;
const int _M = 105;
int _dp[_N][_M], _non_over[_N];
PAIR _cows[_N];
deque<PAIR> _over[_N];

inline void up(int& x, int y) {
	if (x < y) x = y;
}

inline void solve() {
	register PAIR tmp;
	register int n, m, i, j, j2, k, ans = 0;
	cin >> n >> m;
	for (i = 1; i <= n; ++i) cin >> _cows[i].first >> _cows[i].second;
	sort(_cows + 1, _cows + n + 1);
	for (i = 1, j = 2; j <= n; ++j) {
		if (_cows[j].second <= _cows[i].second) --m;
		else _cows[++i] = _cows[j];
	}
	n = i;
	m = max(0, m);
	for (i = 1; i <= n; ++i) {
		for (j = 0, j2 = min(i, m + 1); j < j2; ++j) {
			k = i - j - 1;
			while (!_over[k].empty() && _over[k].front().second <= _cows[i].first) {
				tmp = _over[k].front();
				_over[k].pop_front();
				up(_non_over[k], tmp.first + tmp.second);
			}
			up(_dp[i][j], _non_over[k] + _cows[i].second - _cows[i].first);
			if (!_over[k].empty()) up(_dp[i][j], _over[k].front().first + _cows[i].second);
			++k;
			tmp = PAIR(_dp[i][j] - _cows[i].second, _cows[i].second);
			while (!_over[k].empty() && _over[k].back().first <= tmp.first) _over[k].pop_back();
			_over[k].push_back(tmp);
		}
		k = m - n + i;
		if (k >= 0) up(ans, _dp[i][k]);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}