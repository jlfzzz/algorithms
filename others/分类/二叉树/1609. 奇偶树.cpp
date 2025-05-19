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
    bool isEvenOddTree(TreeNode *root) {
        queue<TreeNode *> q;
        q.push(root);
        int layer = 0;
        while (!q.empty()) {
            int n = q.size();
            int prev = layer % 2 == 0 ? -1 : INT_MAX;
            for (int i = 0; i < n; i++) {
                auto cur = q.front();
                q.pop();
                if (layer % 2 == 0) {
                    if (cur->val % 2 == 0) {
                        return false;
                    }
                    if (cur->val <= prev) {
                        return false;
                    }

                    prev = cur->val;
                    if (cur->left) q.push(cur->left);
                    if (cur->right) q.push(cur->right);
                } else {
                    if (cur->val % 2 == 1) {
                        return false;
                    }
                    if (cur->val >= prev) {
                        return false;
                    }

                    prev = cur->val;
                    if (cur->left) q.push(cur->left);
                    if (cur->right) q.push(cur->right);
                }
            }
            layer++;
        }
        return true;
    }
};