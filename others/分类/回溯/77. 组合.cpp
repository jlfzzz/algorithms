#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;

        auto dfs = [&](this auto &&dfs, int index,
            vector<int> &choose) -> void {
                if (index > n) {
                    if (choose.size() == k) {
                        ans.emplace_back(choose);
                        return;
                    }
                }

                if (choose.size() == k) {
                    ans.emplace_back(choose);
                    return;
                }

                int size = choose.size();
                if (size + n - index + 1 < k || size > k)
                    return;
                dfs(index + 1, choose);
                choose.push_back(index);
                dfs(index + 1, choose);
                choose.pop_back();
            };
        vector<int> choose;
        dfs(1, choose);
        return ans;
    }
};