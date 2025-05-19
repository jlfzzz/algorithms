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
    unordered_map<int, int> map;
    vector<int> rightSideView(TreeNode *root) {
        vector<int> ans;
        if (root == nullptr) {
            return ans;
        }

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();

            // 遍历当前层的所有节点
            for (int i = 0; i < size; i++) {
                TreeNode *node = q.front();
                q.pop();

                // 如果是当前层的最后一个节点，将其值添加到结果中
                if (i == size - 1) {
                    ans.push_back(node->val);
                }

                // 添加子节点到队列
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
        }

        return ans;
    }



    vector<int> rightSideViewDfs(TreeNode *root) {
        dfs(root, 0);
        vector<int> temp;
        for (auto &[row, val] : map) {
            temp.push_back(row);
        }
        ranges::sort(temp);
        vector<int> ans;
        for (auto row : temp) {
            ans.emplace_back(map[row]);
        }
        return ans;
    }

    

    void dfs(TreeNode *node, int row) {
        if (node == nullptr) {
            return;
        }

        int val = node->val;
        map[row] = val;
        dfs(node->left, row + 1);
        dfs(node->right, row + 1);
    }
};