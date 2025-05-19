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
    int sum = 0;
    int sumNumbers(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        dfs(root, 0);
        return sum;
    }

    void dfs(TreeNode *root, long long currSum) {
        if (root == nullptr) {
            return;
        }
        currSum += root->val;

        if (isLeaf(root)) {
            sum += currSum;
        }

        dfs(root->left, currSum * 10);
        dfs(root->right, currSum * 10);
    }

    bool isLeaf(TreeNode *node) {
        return !node->left && !node->right;
    }
};