/*
P2613: 有理数取余
https://www.luogu.com.cn/problem/P2613
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const long long modulo = 19260817;

inline long long read() {
    long long x = 0LL, w = 1LL;
    long long ch = getchar();
    while (ch < 48LL || ch > 57LL) {
        if (ch == 45LL) ch = -1LL;
        ch = getchar();
    }
    while (ch > 47LL && ch < 58LL) {
        x = (x * 10LL + ch - 48LL) % modulo;
        ch = getchar();
    }
    return x * w;
}

inline long long fastPower(long long x, long long k) {
    long long ans = 1;
    while (k) {
        if (k & 1) ans = ans * x % modulo;
        x = x * x % modulo;
        k >>= 1;
    }
    return ans;
}

inline long long inv(long long x) {
    return fastPower(x, modulo - 2);
}

int main() {
    long long a = read();
    long long b = read();
    if (b) cout << (a * inv(b)) % modulo << endl;
    else cout << "Angry!" << endl;
    return 0;
}