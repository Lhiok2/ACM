/*
P6136: 普通平衡树(数据加强版)
https://www.luogu.com.cn/problem/P6136
*/
#include <cstdio>
#include <random>
#include <algorithm>
std::mt19937 rnd(233);
using namespace std;

inline int read() {
    int x = 0, w = 1;
    int ch = getchar();
    while (ch < 48 || ch > 57) {
        if (ch == 45) w = -1;
        ch = getchar();
    }
    while (ch > 47 && ch < 58) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * w;
}

const int max_n = 1100005;
int cnt, root, x, y, z, last;

struct NODE {
    int l, r;
    int size;
    int val;
    int key;
} fhq[max_n];

inline int newNode(int val) {
    fhq[++cnt].val = val;
    fhq[cnt].size = 1;
    fhq[cnt].key = rnd();
    return cnt;
}

inline void update(int index) {
    fhq[index].size = fhq[fhq[index].l].size + fhq[fhq[index].r].size + 1;
}

void split(int now, int val, int& x, int& y) {
    if (!now) x = y = 0;
    else {
        if (fhq[now].val <= val) {
            x = now;
            split(fhq[now].r, val, fhq[now].r, y);
        } else {
            y = now;
            split(fhq[now].l, val, x, fhq[now].l);
        }
        update(now);
    }
}

int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (fhq[x].key > fhq[y].key ) {
        fhq[x].r = merge(fhq[x].r, y);
        update(x);
        return x;
    } else {
        fhq[y].l = merge(x, fhq[y].l);
        update(y);
        return y;
    }
}

inline void insert(int val) {
    split(root, val, x, y);
    root = merge(merge(x, newNode(val)), y);
}

inline void del(int val) {
    split(root, val, x, z);
    split(x, val-1, x, y);
    y = merge(fhq[y].l, fhq[y].r);
    root = merge(merge(x, y), z);
}

inline void ranking(int val) {
    split(root, val - 1, x, y);
    last = fhq[x].size + 1;
    root = merge(x, y);
}

inline void query(int rank) {
    x = root;
    while (true) {
        if (fhq[fhq[x].l].size + 1 == rank) break;
        if (fhq[fhq[x].l].size >= rank) x = fhq[x].l;
        else {
            rank -= fhq[x].l + 1;
            x = fhq[x].r;
        }
    }
    last = fhq[x].val;
}

inline void prev(int val) {
    split(root, val-1, x, y);
    z = x;
    while (fhq[z].r) z = fhq[z].r;
    last = fhq[z].val;
    root = merge(x, y);
}

inline void rear(int val) {
    split(root, val, x, y);
    z = y;
    while (fhq[z].l) z = fhq[z].l;
    last = fhq[z].val;
    root = merge(x, y);
}

int main() {
    int op, ans = 0;
    int n = read();
    int m = read();
    for (register int i = 0; i < n; ++i) insert(read());
    while (m--) {
        op = read();
        if (op == 1) insert(read() ^ last);
        else if (op == 2) del(read() ^ last);
        else {
            if (op == 3) ranking(read() ^ last);
            else if (op == 4) query(read() ^ last);
            else if (op == 5) prev(read() ^ last);
            else rear(read() ^ last);
            ans ^= last;
        }
    }
    printf("%d\n", ans);
    return 0;
}