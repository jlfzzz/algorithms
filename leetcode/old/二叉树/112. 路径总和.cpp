#include <algorithm>
#include <queue>

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
    bool hasPathSum(TreeNode *root, int targetSum) {
        if (root == nullptr) {
            return false;
        }

        targetSum -= root->val;
        if (isLeaf(root) && targetSum == 0) {
            return true;
        }

        return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
    }

    bool isLeaf(TreeNode *node) {
        return !node->left && !node->right;
    }
};