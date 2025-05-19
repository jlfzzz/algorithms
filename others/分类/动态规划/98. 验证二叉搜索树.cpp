// solution2 类似于dp

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
    bool isValidBST(TreeNode *root) {
        return helper(root, LONG_LONG_MIN, LONG_LONG_MAX);
    }

    bool helper(TreeNode *node, long long left, long long right) {
        if (!node) {
            return true;
        }
        int x = node->val;
        return (x > left && x < right) &&
            helper(node->left, left, x) &&
            helper(node->right, x, right);
    }
};

class Solution {
public:
    bool isValidBST(TreeNode *root) {
        return helper(root).second != LONG_LONG_MAX;
    }

    pair<long long, long long> helper(TreeNode *node) {
        if (!node) {
            return { LONG_LONG_MAX, LONG_LONG_MIN };
        }
        long long x = node->val;
        auto [leftleft, leftright] = helper(node->left);
        if (leftright >= x) {
            return { LONG_LONG_MIN,LONG_LONG_MAX };
        }
        auto [rightleft, rightright] = helper(node->right);
        if (rightleft <= x) {
            return { LONG_LONG_MIN,LONG_LONG_MAX };
        }
        return { min(x, leftleft), max(x, rightright) };
    }
};

