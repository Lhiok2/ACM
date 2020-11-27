/*
P3865: [模板]ST表
https://www.luogu.com.cn/problem/P3865
*/
#include <cmath>
#include <cctype>
#include <cstdio>

inline void read(int& x) {
    x = 0;
    int w = 1, ch = getchar();
    while (!isdigit(ch)) {
        if (ch == 45) w = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    x *= w;
}

const int max_n = 1e5 + 5;
int dp[max_n][18], log_2[max_n];

inline void update(int& x, int y) {
    if (y > x) x = y;
}

inline int max(int x, int y) {
    return x > y? x: y;
}

inline void build(int n) {
    int i, j, k;
    for (i = 1; i <= n; ++i) {
        read(dp[i][0]);
        log_2[i] = log2(i);
    }
    for (j = 1, k = 1; j < 18; ++j, k <<= 1) {
        for (i = 1; i <= n; ++i) {
            dp[i][j] = dp[i][j - 1];
            if (i + k <= n) update(dp[i][j], dp[i + k][j - 1]);
        }
    }
}

inline void rmq(int lef, int rig) {
    int _2 = log_2[rig - lef + 1];
    printf("%d\n", max(dp[lef][_2], dp[rig + 1 - (1 << _2)][_2]));
}

int main() {
    int n, m, lef, rig;
    read(n);
    read(m);
    build(n);
    while (m--) {
        read(lef);
        read(rig);
        rmq(lef, rig);
    }
    return 0;
}