#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
static const int MOD = 1000000007;

int64 mod_pow(int64 a, int64 e){ int64 r=1%MOD; while(e){ if(e&1) r=r*a%MOD; a=a*a%MOD; e>>=1; } return r; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n; int k, b;
    cin >> n >> k >> b;
    vector<int> c(k);
    long long Cll = 0;
    for (int i = 0; i < k; ++i) { cin >> c[i]; Cll += c[i]; }
    int C = (int)Cll;

    // 预处理阶乘/逆阶乘到 C
    vector<int64> fact(C+1), invfact(C+1);
    fact[0]=1;
    for(int i=1;i<=C;++i) fact[i]=fact[i-1]*i%MOD;
    invfact[C]=mod_pow(fact[C], MOD-2);
    for(int i=C;i>=1;--i) invfact[i-1]=invfact[i]*i%MOD;

    auto nCr = [&](int N, int R)->int64{
        if(R<0 || R>N) return 0;
        return fact[N]*invfact[R]%MOD*invfact[N-R]%MOD;
    };

    int B = min(b, C);
    vector<int64> dp(B+1,0), ndp(B+1,0);
    dp[0] = 1;

    // 按颜色做卷积：系数必须是 C(c_i, t)
    for(int i=0;i<k;++i){
        fill(ndp.begin(), ndp.end(), 0);
        int ci = c[i];
        int lim = min(B, ci);
        for(int j=0;j<=B;++j) if(dp[j]){
            for(int t=0;t<=lim && j+t<=B;++t){
                ndp[j+t] = (ndp[j+t] + dp[j]*nCr(ci, t)) % MOD;
            }
        }
        dp.swap(ndp);
    }

    // 乘上 j!、(C-j)!，并整体乘 inv(∏ c_i!)
    int64 inv_prod_fact = 1;
    for(int x: c) inv_prod_fact = inv_prod_fact * invfact[x] % MOD;

    int64 ans = 0;
    for(int j=0;j<=B;++j){
        int64 term = dp[j];
        term = term * fact[j] % MOD;      // j!
        term = term * fact[C - j] % MOD;  // (C-j)!
        ans = (ans + term) % MOD;
    }
    ans = ans * inv_prod_fact % MOD;

    cout << ans << '\n';
    return 0;
}