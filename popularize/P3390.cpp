/*
P3390: [模板]矩阵快速幂
https://www.luogu.com.cn/problem/P3390
*/
#include <iostream>
#include <algorithm>
#define modu(x) ((x) % modulo)
using namespace std;

const long long modulo = 1e9 + 7;
int n;

struct MATRIX {
    long long a[105][105];

    friend MATRIX operator * (const MATRIX& x, const MATRIX& y) {
        int i, j, k;
        MATRIX ans;
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                ans.a[i][j] = 0ll;
                for (k = 1; k <= n; ++k) ans.a[i][j] = modu(ans.a[i][j] + modu(x.a[i][k] * y.a[k][j]));
            }
        }
        return ans;
    }

    friend ostream& operator << (ostream &out ,const MATRIX &p) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) out << p.a[i][j] << " ";
            out << "\n";
        }
        return out;
    }

    friend istream& operator >>(istream &in, MATRIX &p) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) in >> p.a[i][j];
        return in;
    }
};

inline MATRIX fastPower(MATRIX matrix, long long k) {
    MATRIX ans;
    for (int i = 1; i <= n; ++i) ans.a[i][i] = 1ll;
    while (k) {
        if (k & 1) ans = ans * matrix;
        matrix = matrix * matrix;
        k >>= 1;
    }
    return ans;
}

int main() {
    long long k;
    MATRIX matrix;
    cin >> n >> k >> matrix;
    matrix = fastPower(matrix, k);
    cout << matrix;
    return 0;
}