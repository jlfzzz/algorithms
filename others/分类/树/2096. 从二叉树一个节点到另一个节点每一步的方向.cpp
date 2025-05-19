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

class Solution1 {
public:
    string getDirections(TreeNode *root, int startValue, int destValue) {
        // 找到从根节点到起点和终点的路径
        string pathToStart = "", pathToDest = "";
        findPath(root, startValue, pathToStart);
        findPath(root, destValue, pathToDest);

        // 去掉公共前缀
        int i = 0;
        while (i < pathToStart.size() && i < pathToDest.size() && pathToStart[i] == pathToDest[i]) {
            i++;
        }

        // 从起点到LCA全是向上，从LCA到终点保持原方向
        return string(pathToStart.size() - i, 'U') + pathToDest.substr(i);
    }

    bool findPath(TreeNode *root, int target, string &path) {
        if (!root) return false;

        if (root->val == target) return true;

        // 尝试左子树
        path.push_back('L');
        if (findPath(root->left, target, path)) return true;
        path.pop_back();

        // 尝试右子树
        path.push_back('R');
        if (findPath(root->right, target, path)) return true;
        path.pop_back();

        return false;
    }
};