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
    int findBottomLeftValue(TreeNode *root) {
        queue<TreeNode *> q;
        q.push(root);
        vector<int> v;
        while (!q.empty()) {
            v.clear();
            int n = q.size();
            for (int i = 0; i < n; i++) {
                auto t = q.front();
                q.pop();
                v.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return v[0];
    }
};

class Solution {
public:
    int findBottomLeftValue(TreeNode *root) {
        int maxDepth = 0;
        TreeNode *ans = root;

        auto dfs = [&](auto &&self, TreeNode *node, int depth) -> void {
            if (!node) {
                return;
            }

            if (depth > maxDepth) {
                maxDepth = depth;
                ans = node;
            }

            self(self, node->left, depth + 1);  // 传递self作为第一个参数
            self(self, node->right, depth + 1); // 传递self作为第一个参数
            };

        dfs(dfs, root, 0);

        return ans->val;
    }
};