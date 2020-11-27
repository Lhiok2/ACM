/*
P5656: [模板]二元一次不定方程
https://www.luogu.com.cn/problem/P5656
*/
#include <iostream>
#include <algorithm>
using namespace std;

long long exgcd(long long a, long long b, long long& x, long long& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    long long ans = exgcd(b, a % b, x, y);
    long long t = x;
    x = y;
    y = t - a / b * y;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    long long a, b, c, n, x, y, min_x, min_y, max_x, max_y, gcd_a_b;
    cin >> t;
    while (t--) {
        cin >> a >> b >> c;
        gcd_a_b = exgcd(a, b, x, y);
        if (c % gcd_a_b) cout << -1 << "\n";
        else {
            a /= gcd_a_b;
            b /= gcd_a_b;
            x *= c / gcd_a_b;
            y *= c / gcd_a_b;
            if (x <= 0) n = x / b - 1;
            else n = (x - 1) / b;
            min_x = x - b * n;
            max_y = y + a * n;
            if (max_y <= 0) {
                n = max_y / a - 1;
                min_y = max_y - a * n;
                cout << min_x << " " << min_y << "\n";
            } else {
                n = (max_y - 1) / a;
                max_x = min_x + b * n;
                min_y = max_y - a * n;
                cout << n + 1 << " " << min_x << " " << min_y << " " << max_x << " " << max_y << "\n";
            }
        }
    }
    return 0;
}