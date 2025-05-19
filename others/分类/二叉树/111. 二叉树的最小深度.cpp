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
    int minDepthVal = INT_MAX;

    int minDepth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        dfs(root, 1);
        return minDepthVal;
    }

    int bfs(TreeNode *root) {
        queue<TreeNode *> q;
        q.emplace(root);
        int depth = 0;

        while (!q.empty()) {
            depth++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode *node = q.front();
                q.pop();
                if (node->left == nullptr && node->right == nullptr) return depth;
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
        }
    }




    void dfs(TreeNode *root, int currDepth) {
        if (root == nullptr) {
            return;
        }

        if (isLeaf(root)) {
            minDepthVal = min(minDepthVal, currDepth);
        }


        currDepth++;
        dfs(root->left, currDepth);
        dfs(root->right, currDepth);
    }

    bool isLeaf(TreeNode *node) {
        return !node->left && !node->right;
    }
};