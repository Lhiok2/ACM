/*
P3375: [模板]KMP字符串匹配
https://www.luogu.com.cn/problem/P3375
*/
#include <cstdio>
#include <cstring>

const int max_n = 1e6 + 5;
int kmp[max_n];
char s1[max_n], s2[max_n];

int main() {
    int i, j, si_1, si_2;
    scanf("%s %s", s1, s2);
    si_1 = strlen(s1);
    si_2 = strlen(s2);
    kmp[0] = 0;
    for (i = 1, j = 0; i < si_2; ++i) {
        while (j && s2[i] != s2[j]) j = kmp[j-1];
        kmp[i] = s2[i] == s2[j]? ++j: 0;
    }
    for (i = 0, j = 0; i < si_1; ++i) {
        while (j && s1[i] != s2[j]) j = kmp[j-1];
        if (s1[i] == s2[j]) {
            if (++j == si_2) {
                printf("%d\n", i - si_2 + 2);
                j = kmp[j-1];
            }
        }
    }
    for (i = 0; i < si_2; ++i) printf("%d ", kmp[i]);
    return 0;
}