#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

constexpr int MOD = int(1e9 + 7);
constexpr int N = 1e6 + 5;

// 全局变量
int spf[N];
vector<int> primes;

// 初始化质数筛
void init() {
    for (int i = 2; i < N; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p: primes) {
            if (p > spf[i] || i * p >= N)
                break;
            spf[i * p] = p;
        }
    }
}

// 快速幂求逆元
ll power(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
ll modInverse(ll n) { return power(n, MOD - 2); }

void solve() {
    ll n;
    ll c;
    cin >> n >> c;
    string s;
    cin >> s;

    if (s[0] == '0' || s[n - 1] == '0') {
        cout << -1 << '\n';
        return;
    }

    // 1. 分解 c
    map<int, int> cntc;
    bool flag = false; // flag = true 表示 c 含有大于 n 的质因子
    ll temp = c;

    // 质因数分解 c
    for (int p: primes) {
        if (p > n)
            break;
        if (1ll * p * p > temp)
            break;
        if (temp % p == 0) {
            while (temp % p == 0) {
                cntc[p]++;
                temp /= p;
            }
        }
    }
    if (temp > 1) {
        if (temp > n)
            flag = true;
        else
            cntc[temp]++;
    }

    // 2. 统计需要的因子
    ll needed_2 = 0;
    if (cntc.count(2))
        needed_2 = cntc[2];

    // 需要的非2质因子
    vector<int> req_primes;
    for (auto const &[p, cnt]: cntc) {
        if (p != 2)
            req_primes.push_back(p);
    }

    // 3. 计算 Base 方案
    // 策略: i=1选0(mul=1), 其他?选1(mul=2)
    ll ans = 1;
    ll have_2 = 0;
    map<int, int> haves;

    // 收集可用的调整位置（下标 >=3 且为奇数的 ?）
    vector<int> odd_q_indices;

    F(i, 0, n - 2) {
        int mul = 0;
        bool is_question = false;

        if (s[i] == '1')
            mul = 2;
        else if (s[i] == '0')
            mul = i;
        else { // s[i] == '?'
            is_question = true;
            if (i == 1)
                mul = 1; // 贪心选最小
            else
                mul = 2;

            // 记录潜在修改点：只有 i >= 3 且 i 是奇数时，才能用来减少因子 2
            if (i >= 3 && (i % 2 != 0)) {
                odd_q_indices.push_back(i);
            }
        }

        ans = (ans * mul) % MOD;

        // 统计因子
        if (!flag && mul > 0) {
            int t = mul;
            while (t > 0 && t % 2 == 0) {
                have_2++;
                t /= 2;
            }
            for (int p: req_primes) {
                while (t > 0 && t % p == 0) {
                    haves[p]++;
                    t /= p;
                }
            }
        }
    }

    // 4. 判定与调整
    if (flag) {
        // c 有大质因子，Base 必不整除
        cout << ans << '\n';
        return;
    }

    bool missing_other = false;
    for (int p: req_primes) {
        if (haves[p] < cntc[p]) {
            missing_other = true;
            break;
        }
    }

    // 如果本身就不整除（缺奇数因子 或 缺2因子）
    if (missing_other || have_2 < needed_2) {
        cout << ans << '\n';
        return;
    }

    // --- Base 方案被整除，需要破坏整除性 ---

    // 如果 c 不需要 2 (c是奇数)，我们无法通过 "除以2" 来破坏整除性
    // 因为我们的操作只会增加奇数因子，不会减少奇数因子
    if (needed_2 == 0) {
        cout << -1 << '\n';
        return;
    }

    // 我们需要移除多少个 2 才能让 have_2 < needed_2 ?
    // 目前有 have_2, 需要变成 needed_2 - 1
    // 需要减少的数量 = have_2 - (needed_2 - 1) = have_2 - needed_2 + 1
    ll to_remove = have_2 - needed_2 + 1;

    // 检查是否有足够的奇数问号可供修改
    if (odd_q_indices.size() < to_remove) {
        cout << -1 << '\n';
    } else {
        // 取前 to_remove 个最小的奇数下标进行修改
        // 修改操作: mul 从 2 变为 k。
        // 数值变化: * k / 2
        // 模运算下: * k * inv(2)
        ll inv2 = modInverse(2);
        for (int k = 0; k < to_remove; k++) {
            int idx = odd_q_indices[k];
            ans = ans * inv2 % MOD;
            ans = ans * idx % MOD;
        }
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}