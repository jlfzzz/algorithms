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
    void dfs(TreeNode *root, int &pre, int &ans) {
        if (root == nullptr) {
            return;
        }
        dfs(root->left, pre, ans);
        if (pre == -1) {
            pre = root->val;
        } else {
            ans = min(ans, root->val - pre);
            pre = root->val;
        }
        dfs(root->right, pre, ans);
    }
    int getMinimumDifference(TreeNode *root) {
        int ans = INT_MAX, pre = -1;
        dfs(root, pre, ans);
        return ans;
    }
};

class Solution2 {
public:
    vector<int> v;
    int getMinimumDifference(TreeNode *root) {
        helper(root);
        int ans = 10e6;
        int n = v.size();
        for (int i = 0; i < n - 1; i++) {
            ans = min(v[i + 1] - v[i], ans);
        }
        return ans;
    }

    void helper(TreeNode *node) {
        if (!node) {
            return;
        }

        helper(node->left);
        v.emplace_back(node->val);
        helper(node->right);
    }
};

class Solution3 {
public:
    int minDiffInBST(TreeNode *root) {
        int res = INT_MAX;
        dfs(root, res);
        return res;
    }

    pair<int, int> dfs(TreeNode *root, int &res) {
        if (!root) return { INT_MAX, INT_MIN };

        auto left = dfs(root->left, res);
        auto right = dfs(root->right, res);

        // 计算当前节点与左右子树最接近的值
        if (left.second != INT_MIN)
            res = min(res, root->val - left.second);
        if (right.first != INT_MAX)
            res = min(res, right.first - root->val);

        return {
            min(left.first, root->val),  // 当前子树的最小值
            max(right.second, root->val)  // 当前子树的最大值
        };
    }
};
