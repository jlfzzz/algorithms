#include <bits/stdc++.h>
using namespace std;

constexpr int N = int(1e5 + 5);

int INIT = [] { return 0; }();

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;

class Solution {
public:
    vector<long long> findXSum(vector<int> &nums, int k, int x) {
        multiset<pair<ll, ll>> st, others;
        unordered_map<ll, ll> freq;
        ll sum = 0;
        int n = nums.size();
        int limit = x;

        auto Check = [&]() {
            if (others.empty()) {
                return false;
            }

            if (st.size() < limit) {
                return true;
            }

            return (st.begin()->first < others.rbegin()->first) ||
                   (st.begin()->first == others.rbegin()->first && st.begin()->second < others.rbegin()->second);
        };

        auto Move = [&]() {
            auto [f2, x2] = *others.rbegin();

            if (st.size() < limit) {
                sum += f2 * x2;
                st.insert({f2, x2});
                others.erase(others.find({f2, x2}));
            } else {
                auto [f1, x1] = *st.begin();
                st.erase(st.begin());
                others.erase(others.find({f2, x2}));
                sum -= f1 * x1;
                sum += f2 * x2;
                st.insert({f2, x2});
                others.insert({f1, x1});
            }
        };

        auto Add = [&](ll x) {
            ll old_freq = freq[x];
            if (old_freq > 0) {
                auto it1 = st.find({old_freq, x});
                if (it1 != st.end()) {
                    st.erase(it1);
                    sum -= x * old_freq;
                } else {
                    auto it2 = others.find({old_freq, x});
                    if (it2 != others.end()) {
                        others.erase(it2);
                    }
                }
            }

            freq[x]++;
            others.insert({freq[x], x});

            while (Check()) {
                Move();
            }
        };

        auto Del = [&](ll x) {
            ll old_freq = freq[x];

            auto it1 = st.find({old_freq, x});
            if (it1 != st.end()) {
                st.erase(it1);
                sum -= x * old_freq;
            } else {
                auto it2 = others.find({old_freq, x});
                if (it2 != others.end()) {
                    others.erase(it2);
                }
            }

            freq[x]--;
            if (freq[x] > 0) {
                others.insert({freq[x], x});
            } else {
                freq.erase(x);
            }

            while (Check()) {
                Move();
            }
        };

        int r = 0;
        vector<ll> ans;
        for (int i = 0; i + k - 1 < n; i++) {
            while (i + k - 1 >= r && r < n) {
                int y = nums[r];
                Add(y);
                r++;
            }

            ans.push_back(sum);
            Del(nums[i]);
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Solution sol1;
    // ll n = 11;
    // vector<int> nums1{}, nums{};
}
