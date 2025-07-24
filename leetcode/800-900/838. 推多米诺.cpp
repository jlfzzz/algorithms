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
#include <queue>
#include <cstring>
#include <array> 
#include <bitset>

using namespace std;

class Solution {
public:
    string pushDominoes(string dominoes) {
        string s = "L" + dominoes + "R"; // 前后各加一个哨兵（不加哨兵的写法见另一份代码）
        int n = s.size();
        int pre = 0; // 上一个 L 或 R 的位置
        for (int i = 1; i < n; i++) {
            if (s[i] == '.') {
                continue;
            }
            if (s[i] == s[pre]) { // L...L 或 R...R
                fill(s.begin() + pre + 1, s.begin() + i, s[i]); // 全变成 s[i]
            } else if (s[i] == 'L') { // R...L
                fill(s.begin() + pre + 1, s.begin() + (pre + i + 1) / 2, 'R'); // 前一半变 R
                fill(s.begin() + (pre + i) / 2 + 1, s.begin() + i, 'L'); // 后一半变 L
            }
            pre = i;
        }
        return s.substr(1, n - 2); // 去掉前后哨兵
    }
};

class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size();

        vector<int> left_record(n, 0);
        vector<int> right_record(n, 0);

        for (int i = 1; i < n; i++) {
            if (dominoes[i] == '.') {
                if (dominoes[i - 1] == 'R') {
                    left_record[i] = 1;
                } else if (left_record[i - 1]) {
                    left_record[i] = left_record[i - 1] + 1;
                }
            }
        }

        for (int i = n - 2; i >= 0; i--) {
            if (dominoes[i] == '.') {
                if (dominoes[i + 1] == 'L') {
                    right_record[i] = 1;
                } else if (right_record[i + 1]) {
                    right_record[i] = right_record[i + 1] + 1;
                }
            }
        }

        string ans;
        for (int i = 0; i < n; i++) {
            if (left_record[i] == right_record[i]) {
                ans += dominoes.substr(i, 1);
            } else {
                if (left_record[i] && right_record[i]) {
                    if (left_record[i] < right_record[i]) {
                        ans += "R";
                    } else {
                        ans += "L";
                    }
                } else {
                    if (left_record[i]) {
                        ans += "R";
                    } else {
                        ans += "L";
                    }
                }
            }
        }

        return ans;
    }
};