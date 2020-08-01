/*
P1776: 宝物筛选(单调队列优化做法)
https://www.luogu.com.cn/problem/P1776
*/
#include <iostream>
#include <algorithm>
#define que_st que[0].first
#define que_en que[0].second
using namespace std;

const int max_n = 105;
const int max_w = 4e4 + 5;
const int max_m = 1e5 + 5;
int v[max_n], w[max_n], m[max_n], dp[max_w];
pair<int, int> que[max_m];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int i, j, k, n, sv, sw, volume;
    cin >> n >> volume;
    for (i = 1; i <= n; ++i) cin >> v[i] >> w[i] >> m[i];
    for (i = 1; i <= n; ++i) {
        for (j = 0; j < w[i]; ++j) {
            que[0] = { 1, 0 };
            for (k = 0, sw = j; sw <= volume; ++k, sw += w[i]) {
                int sv = dp[sw] - k * v[i];
                while (que_st <= que_en && que[que_en].second <= sv) --que_en;
                que[++que_en] = { k, sv };
                while (que[que_st].first + m[i] < k) ++que_st;
                dp[sw] = que[que_st].second + k * v[i];
            }
        }
    }
    cout << dp[volume] << endl;
    return 0;
}