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
    TreeNode *sufficientSubset(TreeNode *root, int limit) {
        int i = dfs(root, 0, limit);
        if (i < limit) {
            return nullptr;
        } else {
            return root;
        }
    }

    int dfs(TreeNode *node, int depth, int limit) {
        if (!node->left && !node->right) {
            return depth + node->val;
        }
        int left = INT_MIN;
        int right = INT_MIN;
        if (node->left) {
            left = dfs(node->left, depth + node->val, limit);
            if (left < limit) {
                node->left = nullptr;
            }
        }

        if (node->right) {
            right = dfs(node->right, depth + node->val, limit);
            if (right < limit) {
                node->right = nullptr;
            }
        }
        return max(left, right);
    }
};

// 方法二，省去了值传递，直接判断是不是nullptr
class Solution2 {
public:
    TreeNode *sufficientSubset(TreeNode *root, int limit) {
        limit -= root->val;
        if (root->left == root->right) // root 是叶子
            // 如果 limit > 0 说明从根到叶子的路径和小于 limit，删除叶子，否则不删除
            return limit > 0 ? nullptr : root;
        if (root->left) root->left = sufficientSubset(root->left, limit);
        if (root->right) root->right = sufficientSubset(root->right, limit);
        // 如果有儿子没被删除，就不删 root，否则删 root
        return root->left || root->right ? root : nullptr;
    }
};

