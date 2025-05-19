#include <algorithm>
#include <queue>
#include <unordered_map>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

using namespace std;

//可以再把 to_delete放到一个map，这样快一点
class Solution {
public:
    vector<TreeNode *> ans;
    vector<TreeNode *> delNodes(TreeNode *root, vector<int> &to_delete) {
        auto ret = dfs(root, to_delete);
        if (ret)
            ans.emplace_back(ret);
        return ans;
    }

    TreeNode *dfs(TreeNode *root, vector<int> &to_delete) {
        if (!root) {
            return nullptr;
        }

        auto left = dfs(root->left, to_delete);
        auto right = dfs(root->right, to_delete);
        root->left = left;
        root->right = right;
        if (ranges::find(to_delete.begin(), to_delete.end(), root->val) != to_delete.end()) {
            if (left)
                ans.emplace_back(left);
            if (right)
                ans.emplace_back(right);
            return nullptr;
        }
        return root;
    }
};