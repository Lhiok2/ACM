/*
P5788: [模板]单调栈
https://www.luogu.com.cn/problem/P5788
*/
#include <iostream>
#include <algorithm>
#define que_si que[0].first
#define que_back que[que[0].first]
using namespace std;

const int max_n = 3e6 + 5;
int f[max_n];
pair<int, int> que[max_n];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, x;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        while (que_si && que_back.second < x) {
            f[que_back.first] = i;
            --que_si;
        }
        que[++que_si] = { i, x };
    }
    for (int i = 1; i <= n; ++i) cout << f[i] << " ";
    cout << endl;
    return 0;
}