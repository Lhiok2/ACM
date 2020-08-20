/*
子序列自动机
https://www.luogu.com.cn/problem/P5826
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int _N = 1e5 + 5;
vector<int> num[_N];

inline void build(int n) {
	register int i, x;
	for (i = 1; i <= n; ++i) {
		cin >> x;
		num[x].push_back(i);
	}
}

inline void solve() {
	register bool t = true;
	register int i, x, n, pos = 0;
	cin >> n;
	for (i = 1; i <= n; ++i) {
		cin >> x;
		if (!t) continue;
		pos = upper_bound(num[x].begin(), num[x].end(), pos) - num[x].begin();
		if (num[x].size() == pos) t = false;
		else pos = num[x][pos];
	}
	if (t) cout << "Yes\n";
	else cout << "No\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int type, n, q, m;
	cin >> type >> n >> q >> m;
	build(n);
	while (q--) solve();
	return 0;
}