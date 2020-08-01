/*
P1886: 单调队列
https://www.luogu.com.cn/problem/P1886
*/
#include <iostream>
#include <algorithm>
#define min_st min_que[0]
#define min_en min_que[1] 
#define max_st max_que[0]
#define max_en max_que[1]
using namespace std;

const int arr_size = 1e6 + 5;
int arr[arr_size];
int min_que[arr_size], max_que[arr_size];

int main() {
    int n, k;
    min_st = max_st = 2;
    min_en = max_en = 1;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i < k; ++i) {
        while (min_en >= min_st && arr[min_que[min_en]] >= arr[i] && i - min_que[min_en] < k) --min_en;
        while (max_en >= max_st && arr[max_que[max_en]] <= arr[i] && i - max_que[max_en] < k) --max_en;
        min_que[++min_en] = max_que[++max_en] = i;
    }
    for (int i = k; i <= n; ++i) {
        while (min_en >= min_st && arr[min_que[min_en]] >= arr[i] && i - min_que[min_en] < k) --min_en;
        min_que[++min_en] = i;
        while (min_que[min_st] + k <= i) ++min_st;
        cout << arr[min_que[min_st]] << " ";
    }
    cout << endl;
    for (int i = k; i <= n; ++i) {
        while (max_en >= max_st && arr[max_que[max_en]] <= arr[i] && i - max_que[max_en] < k) --max_en;
        max_que[++max_en] = i;
        while (max_que[max_st] + k <= i) ++max_st;
        cout << arr[max_que[max_st]] << " ";
    }
    cout << endl;
    return 0;
}