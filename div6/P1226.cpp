/*
P1223: 快速幂-取余运算
https://www.luogu.com.cn/problem/P1226
*/
#include <iostream>
#include <algorithm>
using namespace std;

inline long long fastExponent(long long b, long long p, long long k) {
    long long ans = 1;
    while (p) {
        if (p & 1) ans = (ans * b) % k;
        b = (b * b) % k;
        p >>= 1;
    }
    // 当心模数为1指数为零的情况
    return ans % k;
}

int main() {
    long long b, p, k;
    cin >> b >> p >> k;
    cout << b << "^" << p << " mod " << k << "=" << fastExponent(b, p, k) << endl;
    return 0;
}