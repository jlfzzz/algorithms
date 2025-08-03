#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>

using namespace std;

//正确答案是solution，但这题目是傻逼。 
// 应该return vector<string> 考察 超级大数还差不多

int main() {
    MySolution s;
    auto v = s.countNumbers(2);
    for (auto &s : v) {
        cout << s << endl;
    }

    return 0;
}

class MySolution {
public:
    vector<string> countNumbers(int cnt) {
        vector<string> ans;
        string path;
        auto dfs = [&](this auto &&dfs, int count, int limit) -> void {
            if (count == limit) {
                ans.emplace_back(path);
                return;
            }

            for (int i = 0; i <= 9; i++) {
                if (i == 0 && count == 0) continue;

                path += ('0' + i);
                dfs(count + 1, limit);
                path.pop_back();
            }
            };

        for (int i = 1; i < cnt; i++) {
            dfs(0, cnt);
        }
        return ans;
    }
};





class Solution {
public:
    vector<int> countNumbers(int cnt) {
        vector<int> ans;
        for (int i = 1; i < pow(10, cnt); i++) {
            ans.emplace_back(i);
        }
        return ans;
    }
};