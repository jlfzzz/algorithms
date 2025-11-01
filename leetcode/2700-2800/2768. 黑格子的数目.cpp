using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;


class Solution {
public:
    vector<long long> countBlackBlocks(int m, int n, vector<vector<int>> &coordinates) {
        auto getMask = [&](int x, int y) -> ll { return (ll) x << 30 | y; };
        unordered_set<ll> st;
        for (auto &v: coordinates) {
            st.insert(getMask(v[0], v[1]));
        }

        unordered_set<ll> blks;

        for (auto &v: coordinates) {
            int x = v[0];
            int y = v[1];
            for (int r = x - 1; r <= x; ++r) {
                for (int c = y - 1; c <= y; ++c) {
                    if (r >= 0 && r < m - 1 && c >= 0 && c < n - 1) {
                        blks.insert(getMask(r, c));
                    }
                }
            }
        }

        vector<ll> other(5, 0);

        for (ll block_key: blks) {
            int r = (int) (block_key >> 30);
            int c = (int) (block_key & 0x3FFFFFFF);

            int cnt = 0;
            if (st.contains(getMask(r, c)))
                cnt++;
            if (st.contains(getMask(r, c + 1)))
                cnt++;
            if (st.contains(getMask(r + 1, c)))
                cnt++;
            if (st.contains(getMask(r + 1, c + 1)))
                cnt++;

            other[cnt]++;
        }

        ll total = (ll) (m - 1) * (n - 1);
        other[0] = total - blks.size();

        return other;
    }
};
