// 注意：本题与力扣 865 重复：https://leetcode-cn.com/problems/smallest-subtree-with-all-the-deepest-nodes/
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
    unordered_map<TreeNode *, int> map;
    TreeNode *lcaDeepestLeaves(TreeNode *root) {
        return dfs(root, 0);
    }

    TreeNode *dfs(TreeNode *root, int depth) {
        if (!root) {
            return nullptr;
        }

        if (!root->right && !root->left) {
            map[root] = depth;
            return root;
        }

        auto left = dfs(root->left, depth + 1);
        auto right = dfs(root->right, depth + 1);
        if (left && right) {
            if (map[left] == map[right]) {
                map[root] = map[left];
                return root;
            } else if (map[left] > map[right]) {
                return left;
            } else {
                return right;
            }
        }

        if (left) {
            return left;
        }

        if (right) {
            return right;
        }
        return nullptr;
    }
};

class Solution2 {
    pair<int, TreeNode *> dfs(TreeNode *node) {
        if (node == nullptr)
            return { 0, nullptr };
        auto [left_height, left_lca] = dfs(node->left);
        auto [right_height, right_lca] = dfs(node->right);
        if (left_height > right_height) // 左子树更高
            return { left_height + 1, left_lca };
        if (left_height < right_height) // 右子树更高
            return { right_height + 1, right_lca };
        return { left_height + 1, node }; // 一样高
    }

public:
    TreeNode *lcaDeepestLeaves(TreeNode *root) {
        return dfs(root).second;
    }
};

