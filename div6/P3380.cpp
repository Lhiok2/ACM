/*
P3370: 字符串哈希
https://www.luogu.com.cn/problem/P3370
*/
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int str_size = 1505;
const long long base = 233;
const long long modulo = 1e9 + 7;
int n, si, num_count;
string s;
long long has[str_size];
unordered_map<long long, bool> vis;

inline void pre() {
    has[0] = 1LL;
    for (int i = 1; i < str_size; ++i) has[i] = (has[i-1] * base) % modulo;
}

inline void add() {
    si = s.size();
    long long sum = 0;
    for (int i = 0; i < si; ++i) sum = (sum + s[i] * has[i]) % modulo;
    if (!vis.count(sum)) {
        vis[sum] = true;
        ++num_count;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    pre();
    cin >> n;
    while (n--) {
        cin >> s;
        add();
    }
    cout << num_count << "\n";
    return 0;
}