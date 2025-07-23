#include <bits/stdc++.h>
using namespace std;

long long T, n;
long long nums[200005];
long long prefixPrimeCount[200005];    // sum[]
long long primeFreq[200005];           // ji[]
long long semiprimeFreq[200005];       // jib[]
bool isPrime[200005];                  // ck[]
long long isSemiprime[200005];         // ck2[]
long long semiprimeFactor[200005];     // ck3[]

inline bool checkPrime(long long x) {
    for (long long i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

inline long long checkSemiprime(long long x) {
    for (long long i = 2; i * i <= x; i++) {
        if (x % i == 0 && (!isPrime[i] || !isPrime[x / i])) return -1;
    }
    return 1;
}

inline long long getSmallestPrimeFactor(long long x) {
    for (long long i = 2; i * i <= x; i++) {
        if (x % i == 0) return i;
    }
    return 0;
}

int main() {
    // 初始化质数与半质数信息
    for (long long i = 1; i <= 200000; i++) {
        isPrime[i] = checkPrime(i);
    }
    for (long long i = 1; i <= 200000; i++) {
        if (!isPrime[i]) {
            isSemiprime[i] = checkSemiprime(i);
            semiprimeFactor[i] = getSmallestPrimeFactor(i);
        }
    }

    scanf("%lld", &T);
    while (T--) {
        long long answer = 0;
        scanf("%lld", &n);

        for (long long i = 1; i <= n; i++) {
            prefixPrimeCount[i] = 0;
            primeFreq[i] = 0;
            semiprimeFreq[i] = 0;
            scanf("%lld", &nums[i]);
        }

        for (long long i = 1; i <= n; i++) {
            // 当前是prime。加前面[i-1]里面的prime数量减去当前的出现次数
            if (isPrime[nums[i]]) {
                answer += (prefixPrimeCount[i - 1] - primeFreq[nums[i]]);
                primeFreq[nums[i]]++;
            }
            prefixPrimeCount[i] = prefixPrimeCount[i - 1] + isPrime[nums[i]];

            // 当前是半质数，两个半质数相组合
            // 半质数与自身组合
            if (isSemiprime[nums[i]] == 1) {
                semiprimeFreq[nums[i]]++;
                answer += semiprimeFreq[nums[i]];
            }
        }

        for (long long i = 1; i <= n; i++) {
            if (isSemiprime[nums[i]] == 1) {
                long long p = semiprimeFactor[nums[i]];
                answer += primeFreq[p] + primeFreq[nums[i] / p];
                if (p * p == nums[i]) answer -= primeFreq[p];
            }
        }

        printf("%lld\n", answer);
    }
}
