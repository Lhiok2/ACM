/*
P5903: 树上k级祖先
https://www.luogu.com.cn/problem/P5903
*/
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#define ui unsigned int
#define pai(x, y) (x * base + y)
using namespace std;

inline void read(int& x) {
    x = 0;
    int w = 1, ch = getchar();
    while (ch < 48 || ch > 57) {
        if (ch == 45) w = -1;
        ch = getchar();
    }
    while (ch > 47 && ch < 58) {
        x = (x << 3) + (x << 1) + ch - 48;
        ch = getchar();
    }
    x *= w;
}

const int max_n = 5e5 + 5;
const long long base = 1e9;
int high[21], highbit[max_n], dep[max_n], len[max_n], top[max_n], son[max_n], fa[max_n][21], fir[max_n], nex[max_n];
unordered_map<long long, int> ind (max_n << 5);

void dfs1(int u) {
    len[u] = dep[u] = dep[fa[u][0]] + 1;
    for (int i = 0; i < 20 && fa[u][i]; ++i) fa[u][i+1] = fa[fa[u][i]][i];
    for (int i = fir[u]; i; i = nex[i]) {
        dfs1(i);
        if (len[i] > len[u]) {
            len[u] = len[i];
            son[u] = i;
        }
    }
}

void dfs2(int u, int p) {
    top[u] = p;
    if (u == p) {
        register int i, v, i2 = len[u] - dep[u];
        for (i = 0, v = u; i <= i2; ++i, v = fa[v][0]) ind[pai(u, i)] = v;
        for (i = -1, i2 *= -1, v = son[u]; i >= i2; --i, v = son[v]) ind[pai(u, i)] = v;
    }
    if (son[u]) dfs2(son[u], p);
    for (int i = fir[u]; i; i = nex[i]) {
        if (i == son[u]) continue;
        dfs2(i, i);
    }
}

inline void query(int x, int k, int& ans) {
    if (!k) ans = x;
    else {
        x = fa[x][highbit[k]];
        k -= high[highbit[k]];
        k -= dep[x] - dep[top[x]];
        x = top[x];
        ans = ind[pai(x, k)];
    }
}

inline void pre() {
    register int i, j;
    high[0] = 1;
    for (i = 1; i < 21; ++i) high[i] = high[i-1] << 1;
    for (i = 1, j = 1; i < max_n; ++i) {
        if (i >= high[j]) ++j;
        highbit[i] = j - 1;
    }
}

inline void get(ui& s) {
    s ^= s << 13;
    s ^= s >> 17;
    s ^= s << 5;
}

int main() {
    pre();
    register ui s;
    register int i, n, q, x, k, ans = 0;
    long long tot = 0;
    read(n);
    read(q);
    scanf("%ud", &s);
    for (i = 1; i <= n; ++i) {
        read(x);
        fa[i][0] = x;
        nex[i] = fir[x];
        fir[x] = i;
    }
    dfs1(fir[0]);
    dfs2(fir[0], fir[0]);
    for (i = 1; i <= q; ++i) {
        get(s);
        x = (s ^ ans) % n + 1;
        get(s);
        k = (s ^ ans) % dep[x];
        query(x, k, ans);
        tot ^= 1ll * i * ans;
    }
    printf("%lld\n", tot);
    return 0;
}