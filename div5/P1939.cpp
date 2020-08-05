/*
P1939: 矩阵加速
https://www.luogu.com.cn/problem/P1939
*/
#include <iostream>
#include <algorithm>
using namespace std;

const long long modulo = 1e9 + 7;

struct MATRIX {
    long long m[5][5];

    inline void fill(long long val) {
        int i, j;
        for (i = 1; i <= 3; ++i)
            for (j = 1; j <= 3; ++j) m[i][j] = val;
    }

    friend MATRIX operator * (const MATRIX& x, const MATRIX& y) {
        int i, j, k;
        MATRIX ans;
        for (i = 1; i <= 3; ++i) {
            for (j = 1; j <= 3; ++j) {
                ans.m[i][j] = 0ll;
                for (k  = 1; k <= 3; ++k) {
                    ans.m[i][j] = (ans.m[i][j] + x.m[i][k] * y.m[k][j] % modulo) % modulo;
                }
            }
        }
        return ans;
    }
};

MATRIX baseMatrix() {
    MATRIX base;
    base.fill(0ll);
    base.m[1][1] = base.m[1][2] = base.m[2][3] = base.m[3][1] = 1;
    return base;
}

MATRIX ansMatrix() {
    MATRIX ans;
    ans.fill(0ll);
    ans.m[1][1] = ans.m[2][2] = ans.m[3][3] = 1;
    return ans;
}

long long fastPower(int n) {
    MATRIX ans = ansMatrix();
    MATRIX base = baseMatrix();
    while (n) {
        if (n & 1) ans = ans * base;
        base = base * base;
        n >>= 1;
    }
    return ans.m[1][2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        cout << fastPower(n) << endl;
    }
    return 0;
}