/*
P3804 【模板】后缀自动机 (SAM)
https://www.luogu.com.cn/problem/P3804
*/
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#define _N 1000005
using namespace std;

struct STATE {
	int ti, len, link;
	map<int, int> next;
};

struct SAM {
	int cnt, last;
	STATE st[_N<<1];
	
	inline void init() {
		st[0].link = -1;
		st[0].len = cnt = last = 0;
	}
	
	inline void extend(const char& ch) {
		int p = last, cur = ++cnt;
		st[cur].ti = 1;
		st[cur].len = st[p].len + 1;
		for ( ; ~p && !st[p].next.count(ch); p = st[p].link) st[p].next[ch] = cur;
		if (~p) {
			int q = st[p].next[ch];
			if (st[q].len == st[p].len + 1) st[cur].link = q;
			else {
				int clone = ++cnt;
				st[clone].ti = 0;
				st[clone].link = st[q].link;
				st[clone].next = st[q].next;
				st[clone].len = st[p].len + 1;
				st[cur].link = st[q].link = clone;
				for ( ; ~p && st[p].next[ch] == q; p = st[p].link) st[p].next[ch] = clone;
			}
		} else st[cur].link = 0;
		last = cur;
	}
	
	inline void build(const string& str) {
		init();
		for (const char& ch : str) extend(ch);
		int i, rk[cnt+1];
		for (i = 1; i <= cnt; ++i) rk[i] = i;
		sort(rk + 1, rk + cnt + 1, [&](const int& x, const int& y) {
			return st[x].len > st[y].len;
		});
		for (i = 1; i <= cnt; ++i) st[st[rk[i]].link].ti += st[rk[i]].ti;
	}
} _sam;

inline void up(long long& x, const long long& y) {
	if (x < y) x = y;
}

inline void solve() {
	int i;
	long long ans = 0;
	string str;
	cin >> str;
	_sam.build(str);
	for (i = _sam.cnt; i; --i) if (_sam.st[i].ti > 1) up(ans, 1ll * _sam.st[i].ti * _sam.st[i].len);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}