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
    int ans;
    int kthSmallest(TreeNode *root, int k) {
        dfs(root, k);
        return ans;
    }

    void dfs(TreeNode *node, int &k) {
        if (!node) {
            return;
        }

        dfs(node->left, k);
        if (--k == 0) {
            ans = node->val;
        }
        dfs(node->right, k);
    }
};