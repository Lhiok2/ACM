/*
P5357: AC自动机（二次加强版）
https://www.luogu.com.cn/problem/P5357
*/
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int _N = 2e5 + 5;
bool _tmp[_N][26];
vector<int> _num[_N];
int _cnt, _nex[_N][26], _vis[_N], _ans[_N], _fail[_N];

inline void insert(int num) {
	register int x, p = 0;
	register string str;
	cin >> str;
	for (char ch : str) {
		x = ch - 'a';
		if (!_nex[p][x]) _nex[p][x] = ++_cnt;
		p = _nex[p][x];
	}
	_num[p].push_back(num);
}

inline void buildFail() {
	register int i, p;
	register queue<int> que;
	for (i = 0; i < 26; ++i) if (_nex[0][i]) que.push(_nex[0][i]);
	while (!que.empty()) {
		p = que.front();
		que.pop();
		for (i = 0; i < 26; ++i) {
			if (!_nex[p][i]) {
				_tmp[p][i] = true;
				_nex[p][i] = _nex[_fail[p]][i];
			} else {
				_fail[_nex[p][i]] = _nex[_fail[p]][i];
				que.push(_nex[p][i]);
			}
		}
	}
}

void dfs(vector<int> vec) {
	vector<int> vec2;
	for (int p : vec) for (int i = 0; i < 26; ++i) if (_nex[p][i] && !_tmp[p][i]) vec2.push_back(_nex[p][i]);
	if (!vec2.empty()) dfs(vec2);
	for (int p : vec) {
		_vis[_fail[p]] += _vis[p];
		for (int x : _num[p]) _ans[x] = _vis[p];
	}
}

inline void query() {
	register int p = 0;
	register string str;
	register vector<int> vec;
	cin >> str;
	for (char ch : str) {
		p = _nex[p][ch - 'a'];
		++_vis[p];
	}
	vec.push_back(0);
	dfs(vec);
}

inline void solve() {
	register int i, n;
	cin >> n;
	for (i = 1; i <= n; ++i) insert(i);
	buildFail();
	query();
	for (i = 1; i <= n; ++i) cout << _ans[i] << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}