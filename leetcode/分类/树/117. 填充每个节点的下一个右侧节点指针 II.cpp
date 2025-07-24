// 空间 O(1)
#include <algorithm>
#include <queue>
#include <map>
#include <functional>
#include <string>

class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {
    }
};

using namespace std;

class Solution {
public:
    Node *connect(Node *root) {
        Node dummy;                // 创建一个哑节点作为下一层链表的头部前置节点
        Node *cur = root;          // cur指向当前正在处理的层的第一个节点

        while (cur) {              // 外层循环：处理每一层，直到没有更多的层
            dummy.next = nullptr;  // 初始化下一层的链表为空
            Node *nxt = &dummy;    // nxt是下一层链表的尾部，初始指向哑节点

            while (cur) {          // 内层循环：遍历当前层的所有节点
                if (cur->left) {           // 如果当前节点有左子节点
                    nxt->next = cur->left; // 将左子节点连接到下一层链表
                    nxt = cur->left;       // 更新下一层链表的尾部
                }

                if (cur->right) {           // 如果当前节点有右子节点
                    nxt->next = cur->right; // 将右子节点连接到下一层链表
                    nxt = cur->right;       // 更新下一层链表的尾部
                }

                cur = cur->next;   // 移动到当前层的下一个节点
            }

            cur = dummy.next;      // 当前层处理完毕，移动到下一层的第一个节点
        }

        return root;
    }
};