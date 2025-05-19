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
    unordered_map<int, int> map;
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        for (int i = 0; i < inorder.size(); i++) {
            map[inorder[i]] = i;
        }
        int n = preorder.size();
        return dfs(preorder, inorder, 0, n, 0);
    }

    TreeNode *dfs(vector<int> &preorder, vector<int> &inorder, int prev_l, int prev_r, int inorder_l) {
        if (prev_l == prev_r) {
            return nullptr;
        }

        TreeNode *curr = new TreeNode(preorder[prev_l]);
        int leftChildren = map[preorder[prev_l]] - inorder_l;
        curr->left = dfs(preorder, inorder, prev_l + 1, prev_l + 1 + leftChildren, inorder_l);
        curr->right = dfs(preorder, inorder, prev_l + 1 + leftChildren, prev_r, inorder_l + leftChildren + 1);
        return curr;
    }
};