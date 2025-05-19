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
    bool find = false;
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (!root) {
            return nullptr;
        }

        if (root == q || root == p)
            return root;

        auto left = lowestCommonAncestor(root->left, p, q);
        auto right = lowestCommonAncestor(root->right, p, q);

        if (left && right)
            return root;

        if (left)
            return left;

        if (right)
            return right;

        return nullptr;
    }


};