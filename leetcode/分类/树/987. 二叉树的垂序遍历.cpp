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
    vector<vector<int>> verticalTraversal(TreeNode *root) {
        map<int, map<int, vector<int>>> columnMap;

        function<void(TreeNode *, int, int)> dfs = [&](TreeNode *node, int row, int col) {
            if (!node) return;
            columnMap[col][row].push_back(node->val);
            dfs(node->left, row + 1, col - 1);
            dfs(node->right, row + 1, col + 1);
            };

        dfs(root, 0, 0);

        vector<vector<int>> result;
        for (auto &[col, rowMap] : columnMap) {
            vector<int> colNodes;
            for (auto &[row, values] : rowMap) {
                sort(values.begin(), values.end());
                colNodes.insert(colNodes.end(), values.begin(), values.end());
            }
            result.push_back(colNodes);
        }

        return result;
    }
};