#include <algorithm>
#include <queue>
#include <map>
#include <functional>
#include <string>

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
    TreeNode *subtreeWithAllDeepest(TreeNode *root) {
        return dfs(root).second;
    }

    pair<int, TreeNode *> dfs(TreeNode *root) {
        if (!root) {
            return { 0, nullptr };
        }

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        if (left.first > right.first)
            return { left.first + 1, left.second };

        if (left.first < right.first)
            return { right.first + 1, right.second };
        return { left.first + 1, root };

    }
};