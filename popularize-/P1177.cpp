/*
P1177: [模板]快速排序
https://www.luogu.com.cn/problem/P1177
*/
#include <iostream>
using namespace std;

const int arr_size = 1e5 + 5;
int a[arr_size];

inline void swap(int& x, int& y) {
    // 地址相同不能使用异或操作交换
    if (&x == &y) return;
    x ^= y;
    y ^= x;
    x ^= y;
}

inline pair<int, int> getIndex(int low, int hig) {
    int tmp = a[low+hig>>1];
    do {
        while (a[hig] > tmp) --hig;
        while (a[low] < tmp) ++low;
        if(low <= hig) swap(a[low++], a[hig--]);
    } while (low <= hig);
    return { hig, low };
}

void sort(int low, int hig) {
    if (low < hig) {
        pair<int, int> index = getIndex(low, hig);
        sort(low, index.first);
        sort(index.second, hig);
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(1, n);
    for (int i = 1; i < n; ++i) cout << a[i] << " ";
    cout << a[n] << endl;
    return 0;
}