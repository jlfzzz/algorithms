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
    bool flag = true;
    bool isBalanced(TreeNode *root) {

        dfs(root, 0);
        return flag;
    }

    int dfs2(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        int left = dfs2(root->left);
        int right = dfs2(root->right);
        if (left == -1 || right == -1 || abs(left - right) > 1) {
            return -1;
        }
        return max(left, right) + 1;

    }

    int dfs(TreeNode *root, int currDepth) {
        if (root == nullptr) {
            return currDepth;
        }
        currDepth++;
        int left = dfs(root->left, currDepth);
        int right = dfs(root->right, currDepth);

        if (abs(left - right) > 1) {
            flag = false;
        }
        return max(left, right);
    }
};