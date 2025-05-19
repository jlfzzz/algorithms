#include <algorithm>
#include <queue>
#include <unordered_map>

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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        int n = preorder.size();
        unordered_map<int, int> index;
        for (int i = 0; i < n; i++) {
            index[inorder[i]] = i;
        }

        auto dfs = [&](this auto &&dfs, int pre_l, int pre_r, int in_l, int in_r) -> TreeNode * {
            if (pre_l == pre_r) { // 空节点
                return nullptr;
            }
            int left_size = index[preorder[pre_l]] - in_l; // 左子树的大小
            TreeNode *left = dfs(pre_l + 1, pre_l + 1 + left_size, in_l, in_l + left_size);
            TreeNode *right = dfs(pre_l + 1 + left_size, pre_r, in_l + 1 + left_size, in_r);
            return new TreeNode(preorder[pre_l], left, right);
            };
        return dfs(0, n, 0, n); // 左闭右开区间
    }
};