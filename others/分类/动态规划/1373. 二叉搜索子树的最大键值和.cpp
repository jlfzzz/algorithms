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
    typedef struct info {
        bool isBST;
        int sum;
        int left;
        int right;
    } info;

    int ans = 0;

    int maxSumBST(TreeNode *root) {
        dfs(root);
        return ans;
    }

    info dfs(TreeNode *root) {
        if (!root) {
            info i;
            i.isBST = true;
            i.left = INT_MAX;
            i.right = INT_MIN;
            i.sum = 0;
            return i;
        }

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        info currInfo;
        currInfo.isBST = true;
        int val = root->val;
        if (!left.isBST || !right.isBST || val <= left.right || val >= right.left) {
            currInfo.isBST = false;
            currInfo.left = INT_MIN;
            currInfo.right = INT_MAX;
            currInfo.sum = -1;
            return currInfo;
        }

        currInfo.sum = val + left.sum + right.sum;
        ans = max(ans, currInfo.sum);
        currInfo.left = min(left.left, val);
        currInfo.right = max(val, right.right);
        return currInfo;
    }
};