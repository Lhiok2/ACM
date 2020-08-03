/*
P4549: 裴蜀定理
https://www.luogu.com.cn/problem/P4549
*/
#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int x, int y) {
    return x % y? gcd(y, x % y): y;
}

int main() {
    int i, n, x, y;
    cin >> n >> x;
    for (i = 1; i < n; ++i) {
        cin >> y;
        if (!x) x = y;
        else if (!y) continue;
        else x = abs(gcd(x, y));
    }
    cout << x << endl;
    return 0;
}