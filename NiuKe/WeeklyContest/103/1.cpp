#include <bits/stdc++.h>
#include <vector>
using namespace std;
using i64 = long long;

const int MAXN = 1e5 + 10;
const int ALPHABET_SIZE = 26;
const int P = 13331;
const i64 MOD = 4611686018427387847;
using ll = long long;
#define i128 __int128_t

i64 powerP[MAXN]; // P 的幂

void init() {
    powerP[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        powerP[i] = powerP[i - 1] * P % MOD;
    }
}

class Trie {
public:
    int trie[MAXN][ALPHABET_SIZE]{};
    int freq[MAXN]{}; // 每个节点有多少字符串经过
    int next_pos;
    map<ll, ll> mp{}; // 哈希值 -> 累积贡献值

    Trie() : next_pos(1) {
        memset(trie, 0, sizeof(trie));
        memset(freq, 0, sizeof(freq));
    }

    void Insert(string &s) {
        int curr = 0;
        ll hash = 0;
        for (char c: s) {
            int i = c - 'a';
            hash = ((i128) hash * P + i) % MOD;
            if (!trie[curr][i]) {
                trie[curr][i] = next_pos++;
            }
            curr = trie[curr][i];
            freq[curr]++; // 增加经过这个节点的字符串数量
        }
    }

    void collectHashes() { dfs(0, 0, 0); }

private:
    void dfs(int node, ll hash, int sum) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            int next = trie[node][i];
            if (next) {
                ll newHash = ((i128) hash * P + i) % MOD;
                sum += freq[next]; // 累加贡献
                mp[newHash] = sum; // 存储这个前缀的总贡献
                dfs(next, newHash, sum);
                sum -= freq[next]; // 回溯
            }
        }
    }
};

void solve() {
    int n, m;
    string s;
    cin >> n >> m >> s;

    Trie trie;

    for (int i = 0; i < m; ++i) {
        string t;
        cin >> t;
        trie.Insert(t);
    }

    trie.collectHashes(); // 收集所有前缀哈希和对应的贡献值

    vector<ll> pre_hash(n + 1);
    pre_hash[0] = 0;
    for (int i = 1; i <= n; i++) {
        int j = s[i - 1] - 'a';
        pre_hash[i] = ((i128) pre_hash[i - 1] * P + j) % MOD;
    }

    ll ans = 0;

    // 枚举所有可能的起始位置（删除前缀后的剩余部分）
    for (int start = 0; start <= n; start++) {
        // 二分查找最长匹配前缀
        int lo = start;
        int hi = n;
        int best = 0;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            ll hash;
            if (start == 0) {
                hash = pre_hash[mid + 1];
            } else {
                hash = (pre_hash[mid + 1] - (i128) pre_hash[start] * powerP[mid - start + 1] % MOD + MOD) % MOD;
            }

            auto it = trie.mp.find(hash);
            if (it != trie.mp.end()) {
                best = it->second;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        ans = max(ans, (ll) best);
    }

    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
