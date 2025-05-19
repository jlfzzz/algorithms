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
    bool isUnivalTree(TreeNode *root) {
        if (root == nullptr) {
            return true;
        }
        return helper(root, root->val);
    }

    bool helper(TreeNode *node, int val) {
        if (node == nullptr) {
            return true;
        }
        if (node->val != val) {
            return false;
        }
        return helper(node->left, val) && helper(node->right, val);
    }
};