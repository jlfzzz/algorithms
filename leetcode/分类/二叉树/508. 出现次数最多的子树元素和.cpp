#include <algorithm>
#include <queue>
#include <map>
#include <functional>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

using namespace std;

class Solution {
public:
    unordered_map<int, int> map;
    vector<int> findFrequentTreeSum(TreeNode *root) {
        dfs(root);
        int maxCount = 0;
        for (auto &[sum, count] : map) {
            maxCount = max(count, maxCount);
        }
        vector<int> ans;
        for (auto &[sum, count] : map) {
            if (count == maxCount) {
                ans.push_back(sum);
            }
        }
        return ans;
    }

    int dfs(TreeNode *node) {
        if (node == nullptr) {
            return 0;
        }
        int sum = node->val;
        sum += dfs(node->left);
        sum += dfs(node->right);
        if (map.count(sum)) {
            map[sum]++;
        } else {
            map[sum] = 1;
        }

        return sum;
    }
};