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

//回溯
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> ans;
        vector<string> path;
        auto dfs = [&](this auto &&dfs, TreeNode *node) -> void {
            if (node == nullptr) {
                return;
            }
            path.push_back(to_string(node->val));
            if (node->left == node->right) { // 叶子节点
                string joined_path;
                for (int i = 0; i < path.size(); i++) {
                    if (i > 0) {
                        joined_path += "->";
                    }
                    joined_path += path[i];
                }
                ans.push_back(joined_path);
            } else {
                dfs(node->left);
                dfs(node->right);
            }
            path.pop_back(); // 恢复现场
            };
        dfs(root);
        return ans;
    }
};

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> ans;
        auto dfs = [&](this auto &&dfs, TreeNode *node, string path) -> void {
            if (node == nullptr) {
                return;
            }
            path += to_string(node->val);
            if (node->left == node->right) { // 叶子节点
                ans.push_back(path);
                return;
            }
            path += "->";
            dfs(node->left, path);
            dfs(node->right, path);
            };
        dfs(root, "");
        return ans;
    }
};
