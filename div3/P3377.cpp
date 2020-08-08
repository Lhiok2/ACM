/*
P3377: 左偏树(可并堆)
https://www.luogu.com.cn/problem/P3377
*/
#include <queue>
#include <cstdio>
using namespace std;

struct cmp {
    bool operator () (pair<int, int> x, pair<int, int> y) {
        return x.first == y.first? x.second > y.second: x.first > y.first;
    }
};

const int max_n = 1e5 + 5;
int link_heap[max_n];
priority_queue< pair<int, int>, vector< pair<int, int> >, cmp> heap[max_n];

inline void init(int n) {
    for (register int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        link_heap[i] = i;
        heap[i].push({ x, i });
    }
}

inline void merge(int x, int y) {
    register pair<int, int> tmp;
    while (!heap[x].empty()) {
        tmp = heap[x].top();
        heap[x].pop();
        link_heap[tmp.second] = y;
        heap[y].push(tmp);
    }
}

inline void merge() {
    int x, y;
    scanf("%d %d", &x, &y);
    int heap_x = link_heap[x];
    int heap_y = link_heap[y];
    if (!heap_x || !heap_y || heap_x == heap_y) return;
    heap[heap_x].size() < heap[heap_y].size()? merge(heap_x, heap_y): merge(heap_y, heap_x);
}

inline void remove() {
    int x;
    scanf("%d", &x);
    if (!link_heap[x]) {
        printf("-1\n");
        return;
    }
    pair<int, int> tmp = heap[link_heap[x]].top();
    heap[link_heap[x]].pop();
    link_heap[tmp.second] = 0;
    printf("%d\n", tmp.first);
}

int main() {
    register int n, m, q;
    scanf("%d %d", &n, &m);
    init(n);
    while (m--) {
        scanf("%d", &q);
        if (q == 1) merge();
        else remove();
    }
    return 0;
}