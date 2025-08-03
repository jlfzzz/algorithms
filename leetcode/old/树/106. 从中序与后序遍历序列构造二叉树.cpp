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

// 后序遍历数组最后一个是真正的 root 
class Solution {
public:
    unordered_map<int, int> inMap;
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        int n = inorder.size();
        for (int i = 0; i < n; i++) {
            inMap[inorder[i]] = i;
        }
        return dfs(inorder, postorder, 0, n, 0, n);
    }

    TreeNode *dfs(vector<int> &inorder, vector<int> &postorder, int in_l, int in_r, int pos_l, int pos_r) {
        if (pos_l == pos_r) {
            return nullptr;
        }

        int leftSize = inMap[postorder[pos_r - 1]] - in_l;
        auto left = dfs(inorder, postorder, in_l, in_l + leftSize, pos_l, pos_l + leftSize);
        auto right = dfs(inorder, postorder, in_l + 1 + leftSize, in_r, pos_l + leftSize, pos_r - 1);
        return new TreeNode(postorder[pos_r - 1], left, right);
        
    }
};