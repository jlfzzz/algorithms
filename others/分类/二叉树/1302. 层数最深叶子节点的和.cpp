#include <algorithm>
#include <queue>
#include <map>
#include <functional>
#include <string>

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
    int deepestLeavesSum(TreeNode *root) {
        queue<TreeNode *> q;
        q.push(root);
        int sum = 0;
        while (!q.empty()) {
            sum = 0;
            int n = q.size();
            for (int i = 0; i < n; i++) {
                auto node = q.front();
                q.pop();
                sum += node->val;

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return sum;
    }
};