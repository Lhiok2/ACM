/*
P3373: 线段树2-(zkw)
https://www.luogu.com.cn/problem/P3373
*/
#include <stack>
#include <cstdio>
#include <algorithm>
#define lef_p(x) ((x) << 1)
#define rig_p(x) ((x) << 1 | 1)
#define modp(x) ((x) % p)
using namespace std;

const int max_n = 4e5 + 5;
int N;
long long p;

struct NODE {
    int num;
    long long sum, fact, lazy;

    inline void clear() {
        this->fact = 1;
        this->lazy = 0;
    }
} tree[max_n];

inline void updateSum(int x) {
    tree[x].sum = modp(modp(tree[lef_p(x)].sum + tree[rig_p(x)].sum) * tree[x].fact 
    + modp(tree[x].lazy * tree[x].num));
}

inline void build(int n) {
    register int i, j;
    for (N = 1, i = n + 1; N <= i; N <<= 1);
    for (i = N + 1, j = N + n; i <= j; ++i) {
        tree[i].num = 1;
        scanf("%lld", &tree[i].sum);
    }
    for (i = N - 1; i; --i) {
        tree[i].clear();
        tree[i].num = tree[lef_p(i)].num + tree[rig_p(i)].num;
        updateSum(i);
    }
}

inline void spread(int x) {
    if (tree[x].num <= 1) return;
    if (tree[x].fact == 1 && !tree[x].lazy) return;
    tree[lef_p(x)].sum = modp(tree[lef_p(x)].sum * tree[x].fact + tree[lef_p(x)].num * tree[x].lazy);
    tree[lef_p(x)].fact = modp(tree[lef_p(x)].fact * tree[x].fact);
    tree[lef_p(x)].lazy = modp(tree[lef_p(x)].lazy * tree[x].fact + tree[x].lazy);
    tree[rig_p(x)].sum = modp(tree[rig_p(x)].sum * tree[x].fact + tree[rig_p(x)].num * tree[x].lazy);
    tree[rig_p(x)].fact = modp(tree[rig_p(x)].fact * tree[x].fact);
    tree[rig_p(x)].lazy = modp(tree[rig_p(x)].lazy * tree[x].fact + tree[x].lazy);
    tree[x].clear();
}

inline void applyTag(int x) {
    stack<int> s;
    while(x) {
        s.push(x);
        x >>= 1;
    }
    while(s.size()) {
        spread(s.top());
        s.pop();
    }
}

inline void updateFact(int lef, int rig, long long mul) {
    register int i, j, x;
    register bool vl = false, vr = false;
    for (i = lef + N - 1, j = rig + N + 1; i ^ j ^ 1; i >>= 1, j >>= 1) {
        if (~i & 1) {
            x = i ^ 1;
            if (!vl) {
                lef = x;
                vl = true;
                applyTag(x);
            }
            tree[x].sum = modp(tree[x].sum * mul);
            tree[x].fact = modp(tree[x].fact * mul);
            tree[x].lazy = modp(tree[x].lazy * mul);
        }
        if (j & 1) {
            x = j ^ 1;
            if (!vr) {
                rig = x;
                vr = true;
                applyTag(x);
            }
            tree[x].sum = modp(tree[x].sum * mul);
            tree[x].fact = modp(tree[x].fact * mul);
            tree[x].lazy = modp(tree[x].lazy * mul);
        }
    }
    for(lef >>= 1; lef; lef >>= 1) {
       updateSum(lef);
    }
    for(rig >>= 1; rig; rig >>= 1) {
       updateSum(rig);
    }
}

inline void updateLazy(int lef, int rig, long long val) {
    register int i, j, x;
    register bool vl = false, vr = false;
    for (i = lef + N - 1, j = rig + N + 1; i ^ j ^ 1; i >>= 1, j >>= 1) {
        if (~i & 1) {
            x = i ^ 1;
            if (!vl) {
                lef = x;
                vl = true;
                applyTag(x);
            }
            tree[x].sum = modp(tree[x].sum + val * tree[x].num);
            tree[x].lazy = modp(tree[x].lazy + val);
        }
        if (j & 1) {
            x = j ^ 1;
            if (!vr) {
                rig = x;
                vr = true;
                applyTag(x);
            }
            tree[x].sum = modp(tree[x].sum + val * tree[x].num);
            tree[x].lazy = modp(tree[x].lazy + val);
        }
    }
    for(lef >>= 1; lef; lef >>= 1) {
       updateSum(lef);
    }
    for(rig >>= 1; rig; rig >>= 1) {
       updateSum(rig);
    }
}

inline long long query(int lef, int rig) {
    register bool vl, vr;
    register long long ans = 0;
    for(lef = lef + N - 1, rig = rig + N + 1; lef ^ rig ^ 1; lef >>= 1, rig >>= 1) {
        if(~lef & 1) {
            if(!vl) {
                applyTag(lef ^ 1);
            }
            ans = modp(ans + tree[lef ^ 1].sum);
        }
        if(rig & 1) {
            if(!vr) {
                applyTag(rig ^ 1);
            }
            ans = modp(ans + tree[rig ^ 1].sum);
        }
    }
    return ans;
}

int main() {
    int n, m, q, x, y;
    long long w;
    scanf("%d %d %lld", &n, &m, &p);
    build(n);
    while (m--) {
        scanf("%d %d %d", &q, &x, &y);
        if (q == 3) printf("%lld\n", query(x, y));
        else {
            scanf("%lld", &w);
            if (q == 1) updateFact(x, y, w);
            else updateLazy(x, y, w);
        }
    }
    return 0;
}