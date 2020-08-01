/*
P1776: 宝物筛选(二进制拆分做法)
https://www.luogu.com.cn/problem/P1776
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int max_n = 105;
const int max_w = 4e4 + 5;
const int max_m = 1e5 + 5;
int v[max_n], w[max_n], m[max_n], dp[max_w];

inline void up(int& x, int y) {
    if (y > x) x = y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int i, j, k, n, sv, sw, volume;
    cin >> n >> volume;
    for (i = 1; i <= n; ++i) cin >> v[i] >> w[i] >> m[i];
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m[i]; j <<= 1) {
            m[i] -= j;
            sw = w[i] * j;
            sv = v[i] * j;
            for (k = volume; k >= sw; --k) up(dp[k], dp[k-sw] + sv);
        }
        if (m[i]) {
            sw = w[i] * m[i];
            sv = v[i] * m[i];
            for (k = volume; k >= sw; --k) up(dp[k], dp[k-sw] + sv);
        }
    }
    cout << dp[volume] << endl;
    return 0;
}