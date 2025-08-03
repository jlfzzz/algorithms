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
    TreeNode *replaceValueInTree(TreeNode *root) {
        queue<TreeNode *> q;
        q.push(root);
        map<TreeNode *, TreeNode *> map;
        map[root] = new TreeNode(0, root, nullptr);

        while (!q.empty()) {
            int sum = 0;
            vector<TreeNode *> currLayer;
            int n = q.size();

            // 第一次遍历：收集当前层节点并计算总和
            for (int i = 0; i < n; i++) {
                auto node = q.front();
                q.pop();
                currLayer.push_back(node);
                sum += node->val;

                if (node->left) {
                    map[node->left] = node;
                    q.push(node->left);
                }

                if (node->right) {
                    map[node->right] = node;
                    q.push(node->right);
                }
            }

            // 创建节点到原始值的映射
            unordered_map<TreeNode *, int> original_values;
            for (auto &node : currLayer) {
                original_values[node] = node->val;
            }

            // 计算每个父节点的子节点原始值之和
            unordered_map<TreeNode *, int> family_sum;
            for (auto &node : currLayer) {
                TreeNode *parent = map[node];
                family_sum[parent] += original_values[node];
            }

            // 然后计算新值
            for (auto &node : currLayer) {
                auto parent = map[node];
                node->val = sum - family_sum[parent];
            }
        }

        return root;
    }
};