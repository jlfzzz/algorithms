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
    int count = 0;
    int goodNodes(TreeNode *root) {
        dfs(root, INT_MIN);
        return count;
    }

    void dfs(TreeNode *root, int maxSoFar) {
        if (root == nullptr) {
            return;
        }

        int curr = root->val;
        if (curr >= maxSoFar) {
            count++;
            maxSoFar = max(maxSoFar, curr);
        }
        dfs(root->left, maxSoFar);
        dfs(root->right, maxSoFar);
    }
};