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
    int longestZigZag(TreeNode *root) {
        if (!root) return 0;
        int maxLength = 0;
        // 从根节点开始，分别尝试向左和向右的交错路径
        dfs(root->left, true, 1, maxLength);  // 第一步向左
        dfs(root->right, false, 1, maxLength); // 第一步向右
        return maxLength;
    }

private:
    // dir: true表示上一步是向左，下一步应该向右
    //      false表示上一步是向右，下一步应该向左
    void dfs(TreeNode *node, bool dir, int length, int &maxLength) {
        if (!node) {
            maxLength = max(maxLength, length - 1);
            return;
        }

        // 更新最大长度
        maxLength = max(maxLength, length);

        if (dir) {
            // 上一步向左，这一步应该向右继续交错路径
            dfs(node->right, !dir, length + 1, maxLength);
            // 从当前节点开始新的交错路径
            dfs(node->left, true, 1, maxLength);
        } else {
            // 上一步向右，这一步应该向左继续交错路径
            dfs(node->left, !dir, length + 1, maxLength);
            // 从当前节点开始新的交错路径
            dfs(node->right, false, 1, maxLength);
        }
    }
};

class Solution2 {
public:
    int longestZigZag(TreeNode *root) {
        if (!root) return 0;
        int maxLength = 0;
        dfs(root, maxLength);
        return maxLength;
    }

private:
    // 返回一个pair: {从当前节点向左的最长交错路径, 从当前节点向右的最长交错路径}
    pair<int, int> dfs(TreeNode *node, int &maxLength) {
        if (!node) return { 0, 0 };

        // 递归获取左右子树的结果
        auto [leftLeft, leftRight] = dfs(node->left, maxLength);
        auto [rightLeft, rightRight] = dfs(node->right, maxLength);

        // 计算从当前节点出发的最长交错路径
        int left = node->left ? (1 + leftRight) : 0;  // 向左走一步，然后从左子节点向右
        int right = node->right ? (1 + rightLeft) : 0; // 向右走一步，然后从右子节点向左

        // 更新全局最大长度
        maxLength = max(maxLength, max(left, right));

        return { left, right };
    }
};
