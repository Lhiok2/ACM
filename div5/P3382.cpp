/*
P3382: 三分法
https://www.luogu.com.cn/problem/P3382
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int n;
double factor[20];

inline bool dEqual(double x, double y) {
    return abs(x - y) < 0.00000001;
}

double tripartition(double lef, double rig) {
    if (dEqual(lef, rig)) return lef;
    double mid_1 = lef + rig / 3.0 - lef / 3.0;
    double mid_2 = rig - rig / 3.0 + lef / 3.0;
    double bas_1 = 1, bas_2 = 1;
    double ans_1 = 0, ans_2 = 0;
    for (int i = 0; i <= n; ++i) {
        ans_1 += bas_1 * factor[i];
        ans_2 += bas_2 * factor[i];
        bas_1 *= mid_1;
        bas_2 *= mid_2;
    }
    if (dEqual(ans_1, ans_2)) return tripartition(mid_1, mid_2);
    if (ans_1 < ans_2) return tripartition(mid_1, rig);
    return tripartition(lef, mid_2);
}

int main() {
    double lef, rig;
    scanf("%d %lf %lf", &n, &lef, &rig);
    for (int i = n; i >= 0; --i) scanf("%lf", &factor[i]);
    printf("%.5f\n", tripartition(lef, rig));
    return 0;
}