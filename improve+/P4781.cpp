/*
P4781: [模板]拉格朗日插值
https://www.luogu.com.cn/problem/P4781
*/
#include <iostream>
#include <algorithm>
#define modp(x) ((x) % modulo)
using namespace std;

const int max_n = 2005;
const long long modulo = 998244353;
long long x[max_n], y[max_n], demo[max_n];

inline long long fastPow(long long a, long long k) {
    long long ans = 1;
    while (k) {
        if (k & 1) ans = modp(ans * a);
        a = modp(a * a);
        k >>= 1;
    }
    return ans;
}

inline long long inv(long long a) {
    return fastPow(modp(a + modulo), modulo - 2);
}

int main() {
    int n;
    long long k, ans = 0ll, mole = 1ll;
    cin >> n >> k;
    mole = 1ll;
    for (register int i = 1; i <= n; ++i) {
        cin >> x[i] >> y[i];
        demo[i] = modp(k - x[i] + modulo);
        mole = modp(mole * (k - x[i]));
    }
    for (register int i = 1; i <= n; ++i) {
        for (register int j = i + 1; j <= n; ++j) {
            demo[i] = modp(demo[i] * (x[i] - x[j]));
            demo[j] = modp(demo[j] * (x[j] - x[i]));
        }
        ans = modp(ans + modulo + modp(modp(mole * y[i]) * inv(demo[i])));
    }
    cout << ans << "\n";
    return 0;
}