#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Solution {
public:
    long long minimumFuelCost(vector<vector<int>> &roads, int seats) {
        int n = roads.size() + 1;
        long long ans = 0;
        vector<vector<int>> map(n);

        for (auto &v : roads) {
            map[v[0]].emplace_back(v[1]);
            map[v[1]].emplace_back(v[0]);
        }

        auto dfs = [&](this auto &&dfs, int idx, int father) -> int {
            int peopleSum = 1;
            for (auto meet : map[idx]) {
                if (meet != father) {
                    int peopleCnt = dfs(meet, idx);
                    peopleSum += peopleCnt;
                    ans += (peopleCnt + seats - 1) / seats;
                }
            }
            return peopleSum;
            };
        dfs(0, -1);
        return ans;
    }
};