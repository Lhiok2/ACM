/*
P5854: [模板]笛卡尔树
https://www.luogu.com.cn/problem/P5854
*/
#include <stack>
#include <cstdio>
#include <algorithm>
using namespace std;

inline void read(int& x) {
    x = 0;
    int w = 1, ch = getchar();
    while (ch < 48 || ch > 57) {
        if (ch == 45) w = -1;
        ch = getchar();
    }
    while (ch > 47 && ch < 58) {
        x = (x << 3) + (x << 1) + ch - 48;
        ch = getchar();
    }
    x = x * w;
}

const int max_n = 1e7 + 5;
int n, a[max_n], ls[max_n], rs[max_n];

inline void build() {
    register int i, j;
    stack<int> _stack;
    read(n);
    for (i = 1; i <= n; ++i) {
        read(a[i]);
        while (!_stack.empty()) {
            j = _stack.top();
            if (a[j] < a[i]) break;
            _stack.pop();
            rs[j] = ls[i];
            ls[i] = j;
        }
        _stack.push(i);
    }
    i = _stack.top();
    _stack.pop();
    while (!_stack.empty()) {
        j = _stack.top();
        _stack.pop();
        rs[j] = i;
        i = j;
    }
}

int main() {
    long long ans_1 = 0, ans_2 = 0;
    build();
    for (register int i = 1; i <= n; ++i) {
        ans_1 ^= i * (ls[i] + 1ll);
        ans_2 ^= i * (rs[i] + 1ll);
    }
    printf("%lld %lld\n", ans_1, ans_2);
    return 0;
}