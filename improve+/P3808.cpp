/*
P3808: [模板]AC自动机（简单版）
https://www.luogu.com.cn/problem/P3808
*/
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int _N = 1e6;
int _cnt, _nex[_N][26], _fail[_N], _exist[_N];

inline void insert(string str) {
	register int p = 0, x;
	for (char ch : str) {
		x = ch - 'a';
		if (!_nex[p][x]) _nex[p][x] = ++_cnt;
		p = _nex[p][x];
	}
	++_exist[p];
}

inline void buildFail() {
	register int i, x;
	queue<int> que;
	for (i = 0; i < 26; ++i) if (_nex[0][i]) que.push(_nex[0][i]);
	while (!que.empty()) {
		x = que.front();
		que.pop();
		for (i = 0; i < 26; ++i) {
			if (!_nex[x][i]) _nex[x][i] = _nex[_fail[x]][i];
			else {
				que.push(_nex[x][i]);
				_fail[_nex[x][i]] = _nex[_fail[x]][i];
			}
		}
	}
}

inline int query(string str) {
	register int x, p = 0, ans = 0;
	for (char ch : str) {
		p = _nex[p][ch-'a'];
		for (x = p; x && ~_exist[x]; x = _fail[x]) {
			ans += _exist[x];
			// 剪枝
			_exist[x] = -1;
		}
	}
	return ans;
}

inline void solve() {
	register int i, n;
	register string str;
	cin >> n;
	for (i = 0; i < n; ++i) {
		cin >> str;
		insert(str);
	}
	buildFail();
	cin >> str;
	cout << query(str) << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}