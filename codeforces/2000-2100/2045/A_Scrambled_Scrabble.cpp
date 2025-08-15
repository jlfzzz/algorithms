#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    string s;
    cin >> s;

    int vowels = 0; // A,E,I,O,U 的数量
    int y = 0; // Y 的数量
    int n = 0, g = 0; // N 和 G 的数量
    int other_consonants = 0; // 其他辅音数量

    // 统计各类字符
    for (char c: s) {
        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            vowels++;
        } else if (c == 'Y') {
            y++;
        } else if (c == 'N') {
            n++;
        } else if (c == 'G') {
            g++;
        } else {
            other_consonants++;
        }
    }

    int max_length = 0;

    // 尝试不同的Y分配和NG使用策略
    for (int y_vowel = 0; y_vowel <= y; y_vowel++) {
        int y_consonant = y - y_vowel;
        int total_vowels = vowels + y_vowel;

        if (total_vowels == 0)
            continue;

        // 尝试不同的NG配对数量
        int max_ng_pairs = min(n, g);
        for (int ng_pairs = 0; ng_pairs <= max_ng_pairs; ng_pairs++) {
            // 计算剩余的辅音
            int remaining_n = n - ng_pairs;
            int remaining_g = g - ng_pairs;
            int single_consonants = other_consonants + remaining_n + remaining_g + y_consonant;

            // 每个音节需要2个辅音单位和1个元音
            // NG算作1个辅音单位，但占2个字符
            int total_consonant_units = single_consonants + ng_pairs;
            int possible_syllables = min(total_vowels, total_consonant_units / 2);

            // 计算实际使用的字符数
            int used_vowels = possible_syllables;
            int used_consonant_units = possible_syllables * 2;

            // 贪心：优先使用NG（因为它贡献更多长度）
            int used_ng = min(ng_pairs, used_consonant_units);
            int used_single = used_consonant_units - used_ng;

            int total_length = used_vowels + used_ng * 2 + used_single;
            max_length = max(max_length, total_length);
        }
    }

    cout << max_length << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
