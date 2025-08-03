#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int MAXN = 1e5 + 10;
const int ALPHABET_SIZE = 26;
const int P = 13331;
const i64 MOD = 4611686018427387847;

i64 powerP[MAXN]; // P 的幂

class Trie {
private:
    int trie[MAXN * 5][ALPHABET_SIZE];
    int freq[MAXN * 5];
    int nodeCount;
    vector<pair<i64, int>> prefixHashes;

public:
    Trie() { reset(); }

    void reset() {
        for (int i = 0; i <= nodeCount; ++i) {
            freq[i] = 0;
            fill(trie[i], trie[i] + ALPHABET_SIZE, 0);
        }
        nodeCount = 0;
        prefixHashes.clear();
    }

    void insert(const string &s) {
        int node = 0;
        for (char c: s) {
            int ch = c - 'a';
            if (!trie[node][ch])
                trie[node][ch] = ++nodeCount;
            node = trie[node][ch];
            freq[node]++;
        }
    }

    void collectHashes() {
        dfs(0, 0, 0);
        sort(prefixHashes.begin(), prefixHashes.end());
    }

    int findContribution(i64 hash) const {
        int l = 0, r = prefixHashes.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (prefixHashes[mid].first == hash)
                return prefixHashes[mid].second;
            else if (prefixHashes[mid].first < hash)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return -1;
    }

private:
    void dfs(int node, i64 hash, int sum) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            int next = trie[node][i];
            if (next) {
                i64 newHash = ((__int128_t) hash * P + (i + 'a')) % MOD;
                sum += freq[next];
                prefixHashes.emplace_back(newHash, sum);
                dfs(next, newHash, sum);
                sum -= freq[next]; // 回溯
            }
        }
    }
};

void solveCase() {
    int n, m;
    string s;
    cin >> n >> m >> s;

    Trie trie;

    // 插入所有模式串
    for (int i = 0; i < m; ++i) {
        string t;
        cin >> t;
        trie.insert(t);
    }

    // 收集 Trie 的所有前缀哈希和贡献
    trie.collectHashes();

    // 构造前缀哈希
    s = " " + s; // 1-based indexing
    vector<i64> prefixHash(n + 1);
    for (int i = 1; i <= n; i++) {
        prefixHash[i] = ((__int128_t) prefixHash[i - 1] * P + s[i]) % MOD;
    }

    // 枚举所有后缀，二分最长匹配前缀
    int maxContribution = 0;
    for (int start = 1; start <= n; ++start) {
        int l = start, r = n, best = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            i64 hash = ((__int128_t) prefixHash[mid] -
                        (__int128_t) prefixHash[start - 1] * powerP[mid - start + 1] % MOD + MOD) %
                       MOD;
            int contrib = trie.findContribution(hash);
            if (contrib != -1) {
                best = contrib;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        maxContribution = max(maxContribution, best);
    }

    cout << maxContribution << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 预处理 P 的幂
    powerP[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        powerP[i] = (__int128_t) powerP[i - 1] * P % MOD;
    }

    int t;
    cin >> t;
    while (t--)
        solveCase();
    return 0;
}
