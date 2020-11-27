/*
P3796: [模板]AC自动机（加强版）
https://www.luogu.com.cn/problem/P3796
*/
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int _N = 155;
const int _M = 11000;

string _str[_N];
bool _tmp[_M][26];
int _cnt, _nex[_M][26], _vis[_M], _num[_M], _ans[_N], _fail[_M];

inline void init(int p) {
	_vis[p] = _num[p] = _fail[p] = 0;
	for (int i = 0; i < 26; ++i) _tmp[p][i] = _nex[p][i] = 0;
}

inline void insert(int num) {
	register int x, p = 0;
	for (char ch : _str[num]) {
		x = ch - 'a';
		if (!_nex[p][x]) {
			init(++_cnt);
			_nex[p][x] = _cnt;
		}
		p = _nex[p][x];
	}
	_num[p] = num;
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
		if (_num[p]) _ans[_num[p]] = _vis[p];
	}
}

inline void query() {
	register int p = 0;
	vector<int> vec;
	for (char ch : _str[0]) {
		p = _nex[p][ch - 'a'];
		++_vis[p];
	}
	vec.push_back(0);
	dfs(vec);
}

inline bool solve() {
	register int i, n, maxi = 0;
	register vector<int> ans;
	cin >> n;
	if (!n) return false;
	_cnt = 0;
	init(_cnt);
	for (i = 1; i <= n; ++i) {
		cin >> _str[i];
		_ans[i] = 0;
		insert(i);
	}
	buildFail();
	cin >> _str[0];
	query();
	for (i = 1; i <= n; ++i) {
		if (_ans[i] > maxi) {
			maxi = _ans[i];
			ans.clear();
			ans.push_back(i);
		} else if (_ans[i] == maxi) ans.push_back(i);
	}
	cout << maxi << '\n';
	for (int p : ans) cout << _str[p] << '\n';
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while (solve());
	return 0;
}