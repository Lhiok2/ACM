/*
P5367: [模板]康托展开
https://www.luogu.com.cn/problem/P5367
*/
#include <iostream>
#include <algorithm>
#define lowbit(x) (x & -x)
#define modp(x) ((x) % modulo)
using namespace std;

const int max_n = 1e6 + 5;
const long long modulo = 998244353;
int a[max_n], t_arr[max_n];
long long fact[max_n];

inline void update(int index) {
    for ( ; index < max_n; index += lowbit(index)) ++t_arr[index];
}

inline int query(int index) {
    int ans = 0;
    for ( ; index; index ^= lowbit(index)) ans += t_arr[index];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    long long ans = 1ll;
    cin >> n;
    fact[0] = 1;
    for (register int i = 1; i <= n; ++i) {
        cin >> a[i];
        fact[i] = modp(fact[i-1] * i);
    }
    for (register int i = 1; i <= n; ++i) {
        ans = modp(ans + modp((a[i] - 1 - query(a[i])) * fact[n-i]));
        update(a[i]);
    }
    cout << ans << endl;
    return 0;
}