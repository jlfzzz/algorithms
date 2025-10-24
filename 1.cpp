// Killing Monsters (SP Regionals 2023 Problem K)
// 计数在长度区间 [L, U] 的所有序列，使所选怪物赏金之和能被 K 整除。
// 令 A[r] = 赏金对 K 取模为 r 的怪物数量。长度为 t 的序列的模 K 计数分布为 A 的循环卷积 t 次幂：A^{*t}。
// 目标为 sum_{t=L..U} (A^{*t}[0])。在环 R = (Z_mod 1e9+7)[x]/(x^K-1) 中，设 F(x)=sum_r A[r] x^r，则 A^{*t} 即 F^t，
// 利用几何级数按二进制拆分：预处理 P[i]=F^{2^i} 与 S[i]=sum_{j=1..2^i} F^j，按位累加得到 S_n，最终答案为 (S_U -
// S_{L-1}) 的 x^0 系数。

#include <bits/stdc++.h>
using namespace std;

static constexpr int MOD = 1000000007;

static inline int addmod(int a, int b) {
    int s = a + b;
    if (s >= MOD) {
        s -= MOD;
    }
    return s;
}

static inline int submod(int a, int b) {
    int s = a - b;
    if (s < 0) {
        s += MOD;
    }
    return s;
}

static vector<int> cyclicConvolution(const vector<int> &a, const vector<int> &b) {
    int K = (int) a.size();
    vector<int> c(K, 0);
    for (int j = 0; j < K; ++j) {
        int aj = a[j];
        if (aj == 0) {
            continue;
        }
        long long aVal = aj;
        for (int i = 0; i < K; ++i) {
            int idx = i + j;
            if (idx >= K) {
                idx -= K;
            }
            long long prod = (aVal * (long long) b[i]) % MOD;
            int nv = c[idx] + (int) prod;
            if (nv >= MOD) {
                nv -= MOD;
            }
            c[idx] = nv;
        }
    }
    return c;
}

static vector<int> addVec(const vector<int> &a, const vector<int> &b) {
    int K = (int) a.size();
    vector<int> c(K);
    for (int i = 0; i < K; ++i) {
        c[i] = addmod(a[i], b[i]);
    }
    return c;
}

static void buildPowersAndSums(const vector<int> &F, long long maxN, vector<vector<int>> &P, vector<vector<int>> &S) {
    P.clear();
    S.clear();
    P.push_back(F);
    S.push_back(F);
    long long len = 1;
    while ((len << 1) <= maxN) {
        vector<int> p2 = cyclicConvolution(P.back(), P.back());
        vector<int> ps = cyclicConvolution(P.back(), S.back());
        vector<int> s2 = addVec(S.back(), ps);
        P.push_back(std::move(p2));
        S.push_back(std::move(s2));
        len <<= 1;
    }
}

static vector<int> prefixSum(long long n, const vector<vector<int>> &P, const vector<vector<int>> &S) {
    int K = (int) P[0].size();
    vector<int> resS(K, 0);
    vector<int> resP(K, 0);
    resP[0] = 1; // 单位元 E(x)=1
    int bit = 0;
    long long x = n;
    while (x > 0) {
        if ((x & 1LL) != 0) {
            vector<int> t = cyclicConvolution(resP, S[bit]);
            resS = addVec(resS, t);
            resP = cyclicConvolution(resP, P[bit]);
        }
        x >>= 1LL;
        bit += 1;
    }
    return resS;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    long long L, U;
    if (!(cin >> N >> K >> L >> U)) {
        return 0;
    }
    vector<int> A(K, 0);
    for (int i = 0; i < N; ++i) {
        long long b;
        cin >> b;
        int r = (int) (b % K);
        A[r] = addmod(A[r], 1);
    }

    // F(x) = sum_r A[r] x^r
    vector<vector<int>> P, S;
    buildPowersAndSums(A, U, P, S);

    vector<int> SU = prefixSum(U, P, S);
    vector<int> SLm1;
    if (L > 1) {
        SLm1 = prefixSum(L - 1, P, S);
    } else {
        SLm1.assign(K, 0);
    }
    int ans = submod(SU[0], SLm1[0]);
    cout << ans << '\n';
    return 0;
}
