#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// 方法2比1快 50 倍


class Solution1 {
public:
    int punishmentNumber(int n) {
        int ans = 0;
        vector<int> partition;
        for (int i = 1; i <= n; ++i) {
            string s = to_string(i * i);
            partition.clear();
            partition.push_back(0);
            if (dfs(1, partition, s, i)) {
                ans += i * i;
            }
        }
        return ans;
    }

    bool dfs(int index, vector<int> &partition, const string &s, int target) {
        if (index == s.size()) {
            partition.push_back(index);
            int sum = 0;
            for (int i = 0; i + 1 < partition.size(); ++i) {
                sum += stoi(s.substr(partition[i], partition[i + 1] - partition[i]));
            }
            partition.pop_back();
            return sum == target;
        }

        if (dfs(index + 1, partition, s, target)) return true;

        partition.push_back(index);
        if (dfs(index + 1, partition, s, target)) {
            partition.pop_back();
            return true;
        }
        partition.pop_back();
        return false;
    }
};

class Solution2 {
public:
    int punishmentNumber(int n) {
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int square = i * i;
            if (canPartition(square, i)) {
                ans += square;
            }
        }
        return ans;
    }

    bool canPartition(int num, int target) {
        return dfs(num, target);
    }

    bool dfs(int num, int target) {
        if (num == 0)
            return target == 0;

        int base = 1;
        int part = 0;
        // 尝试从末尾截取 1 到所有位数的每一段
        while (num >= base) {
            part = (num % (base * 10));
            if (part <= target && dfs(num / (base * 10), target - part)) {
                return true;
            }
            base *= 10;
        }
        return false;
    }
};

