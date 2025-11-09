#include <bits/stdc++.h>
int T, K;
long long N;
signed main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %lld", &K, &N);
        for (int i = 100000; i >= 1; i--) {
            int xx = N / i;
            if (xx == 0)
                continue;
            printf("(");
            for (int j = 1; j < i; j++)
                printf("()");
            for (int j = 1; j <= K; j++)
                printf("(");
            for (int j = 1; j <= K; j++)
                printf(")");
            for (int j = 1; j < xx; j++)
                printf("()");
            printf(")");
            N %= i;
        }
        printf("\n");
    }
}
