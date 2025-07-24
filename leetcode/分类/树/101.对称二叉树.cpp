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

class Solution1 {
public:
    bool isSymmetric(TreeNode *root) {
        if (root == nullptr) {
            return true;
        }

        queue<TreeNode *> q;
        q.push(root->left);
        q.push(root->right);

        while (!q.empty()) {
            TreeNode *left = q.front();
            q.pop();
            TreeNode *right = q.front();
            q.pop();

            // 如果两个节点都为空，继续检查
            if (left == nullptr && right == nullptr) {
                continue;
            }

            // 如果一个为空另一个不为空，或者值不相等，返回false
            if (left == nullptr || right == nullptr || left->val != right->val) {
                return false;
            }

            // 将左子树的左子节点和右子树的右子节点入队
            q.push(left->left);
            q.push(right->right);

            // 将左子树的右子节点和右子树的左子节点入队
            q.push(left->right);
            q.push(right->left);
        }

        return true;
    }
};

class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (root == nullptr) return true;
        return isMirror(root->left, root->right);
    }

private:
    bool isMirror(TreeNode *left, TreeNode *right) {
        // 两个节点都为空
        if (left == nullptr && right == nullptr) return true;

        // 一个为空，一个不为空
        if (left == nullptr || right == nullptr) return false;

        // 值不相等
        if (left->val != right->val) return false;

        // 递归检查：左的左与右的右，左的右与右的左
        return isMirror(left->left, right->right) &&
            isMirror(left->right, right->left);
    }
};