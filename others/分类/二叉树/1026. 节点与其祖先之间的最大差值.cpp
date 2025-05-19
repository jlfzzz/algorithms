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
    int mx = 0, mn = 0;
    int maxAncestorDiff(TreeNode *root) {
        if (!root) {
            return 0;
        }



        return helper(root, root->val, root->val);
    }

    int helper(TreeNode *node, int mx, int mn) {
        if (!node) {
            return mx - mn;
        }

        mx = max(mx, node->val);
        mn = min(mn, node->val);

        return max(helper(node->left, mx, mn), helper(node->right, mx, mn));
    }
};