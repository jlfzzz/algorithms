#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> path;
        int n = s.size();

        auto check = [&](int start, int end) -> bool {
            for (int i = 0; i < (end - start) / 2; i++) {
                if (s[i + start] != s[end - i - 1])
                    return false;
            }
            return true;
            };



        auto dfs = [&](this auto &&dfs, int index, int start) -> void {
            if (index == n) {
                ans.emplace_back(path);
                return;
            }

            
            };
        dfs(0, 0);
        return ans;
    }
};










class Solution2 {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<int> partition;
        partition.emplace_back(0);
        //int start = 0;
        int n = s.size();

        auto check = [&](int start, int end) -> bool {
            for (int i = 0; i < (end - start) / 2; i++) {
                if (s[i + start] != s[end - i - 1])
                    return false;
            }
            return true;
            };



        auto dfs = [&](this auto &&dfs, int index) -> void {
            if (index == n) {
                int size = partition.size();
                bool flag = true;
                vector<string> temp;
                for (int i = 0; i < size; i++) {
                    if (i == size - 1) {
                        flag = check(partition[i], n);
                        temp.push_back(s.substr(partition[i], n - partition[i]));
                    } else {
                        flag = check(partition[i], partition[i + 1]);
                        temp.push_back(s.substr(partition[i], partition[i + 1] - partition[i]));
                    }
                    if (flag == false) break;
                }
                if (flag) {
                    ans.push_back(temp);
                }
                return;
            }

            dfs(index + 1);
            partition.emplace_back(index);
            dfs(index + 1);
            partition.pop_back();
            };
        dfs(1);
        return ans;
    }
};