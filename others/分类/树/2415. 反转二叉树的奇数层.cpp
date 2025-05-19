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
    TreeNode *reverseOddLevels(TreeNode *root) {
        dfs(root->left, root->right, true);
        return root;
    }

    void dfs(TreeNode *root1, TreeNode *root2, bool flag) {
        if (!root1) return;

        if (flag) swap(root1->val, root2->val);

        dfs(root1->left, root2->right, !flag);
        dfs(root1->right, root2->right, !flag);
    }
};

class Solution {
public:
    TreeNode *reverseOddLevels(TreeNode *root) {
        queue<TreeNode *> qu;
        qu.emplace(root);
        bool isOdd = false;
        while (!qu.empty()) {
            int sz = qu.size();
            vector<TreeNode *> arr;
            for (int i = 0; i < sz; i++) {
                TreeNode *node = qu.front();
                qu.pop();
                if (isOdd) {
                    arr.emplace_back(node);
                }
                if (node->left) {
                    qu.emplace(node->left);
                    qu.emplace(node->right);
                }
            }
            if (isOdd) {
                for (int l = 0, r = sz - 1; l < r; l++, r--) {
                    swap(arr[l]->val, arr[r]->val);
                }
            }
            isOdd ^= true;
        }
        return root;
    }
};