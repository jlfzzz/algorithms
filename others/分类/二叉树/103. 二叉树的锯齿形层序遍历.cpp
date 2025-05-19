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
    vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
        queue<TreeNode *> q;
        vector<vector<int>> ans;
        if (root)
            q.push(root);
        int depth = 0;
        while (!q.empty()) {
            int n = q.size();
            vector<int> v;

            for (int i = 0; i < n; i++) {
                auto curr = q.front();
                q.pop();

                if (depth % 2 == 0) {
                    v.push_back(curr->val);
                } else {
                    v.insert(v.begin(), curr->val);
                }

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            ans.push_back(v);
            depth++;
        }
        return ans;
    }
};