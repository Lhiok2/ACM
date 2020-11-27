/*
P5091: [模板]扩展欧拉定理
https://www.luogu.com.cn/problem/P5091
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int max_n = 1e8 + 5;
bool _notPri[max_n];
int _pri[max_n];

inline int read_p(int p) {
    register int x = 0, w = 1, ch = getchar();
    while (ch < 48 || ch > 57) {
        if (ch == 45) w = -1;
        ch = getchar();
    }
    while (ch > 47 && ch < 58) {
        x = ((x << 3) + (x << 1) + ch - 48) % p;
        ch = getchar();
    }
    return x * w;
}

inline int fastPow(long long x, int k, long long p) {
    if (!k) return (int) (x % p);
    long long ans = 1ll;
    while (k) {
        if (k & 1) ans = ans * x % p;
        x = x * x % p;
        k >>= 1;
    }
    return (int) ans;
}

inline int gcd(int x, int y) {
    return y? gcd(y, x % y): x;
}

inline int euler(int m) {
    register int i, j, ans = m;
    for (i = 2; i <= m; ++i) {
        if (!_notPri[i]) {
            _pri[++_pri[0]] = i;
            if (!(m % i)) ans = ans / i * (i - 1);
        }
        for (j = 1; j <= _pri[0]; ++j) {
            if (1ll * i * _pri[j] > m) break;
            _notPri[i * _pri[j]] = true;
            if (!(i % _pri[j])) break;
        }
    }
    return ans;
}

int main() {
    int a, b, p, p2;
    scanf("%d %d", &a, &p);
    p2 = euler(p);
    if (gcd(a, p) != 1) p2 <<= 1;
    b = read_p(p2);
    printf("%d\n", fastPow(a, b, p));
    return 0;
}