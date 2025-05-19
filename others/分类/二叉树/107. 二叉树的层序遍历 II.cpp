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
    vector<vector<int>> levelOrderBottom(TreeNode *root) {
        vector<vector<int>> ans;
        if (!root) return ans;  // 处理空树情况

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty()) {
            int n = q.size();
            vector<int> v;

            for (int i = 0; i < n; i++) {
                TreeNode *temp = q.front();
                q.pop();
                v.push_back(temp->val);

                // 将左右子节点加入队列
                if (temp->left) q.push(temp->left);
                if (temp->right) q.push(temp->right);
            }

            ans.insert(ans.begin(), v);  // 将当前层的节点值加入结果
        }

        return ans;  // 返回最终结果
    }
};