#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <queue>
#include <cstring>
#include <array> 
#include <bitset>
#include <stack>
#include <set>

using namespace std;

class AllOne {
public:
    struct list_node {
        int count;
        string s;
        list_node *next;
        list_node *prev;
        list_node(int x) : count(x), next(nullptr), prev(nullptr), s("") {}
    };

    int mn;
    int mx;
    unordered_map<string, list_node *> str_to_node;
    unordered_map<int, list_node *> cnt_to_list;

    AllOne() {
        mn = 0;
        mx = 0;
    }

    void remove(list_node *node) {
        bool erase = false;
        int cnt = node->count;

        // 检查是否是链表中唯一的实际节点（不包括哑节点）
        if (node->prev->count == 0 && node->next->count == 0) {
            erase = true;
        }

        node->next->prev = node->prev;
        node->prev->next = node->next;

        if (erase)
            cnt_to_list.erase(cnt);
    }

    void insert(list_node *node) {
        int curr_cnt = node->count;
        if (!cnt_to_list[curr_cnt]) {
            list_node *dummy = new list_node(0);
            dummy->next = dummy;
            dummy->prev = dummy;
            cnt_to_list[curr_cnt] = dummy;
        }

        list_node *dummy = cnt_to_list[curr_cnt];
        list_node *nxt = dummy->next;

        dummy->next = node;
        node->prev = dummy;
        node->next = nxt;
        nxt->prev = node;
    }

    void inc(string key) {
        if (str_to_node.find(key) != str_to_node.end()) {
            list_node *node = str_to_node[key];
            int old_count = node->count;
            remove(node);
            node->count++;
            insert(node);

            // 更新 mx
            if (node->count > mx) {
                mx = node->count;
            }

            // 如果移除了最小计数的最后一个节点，更新 mn
            if (old_count == mn && cnt_to_list.find(old_count) == cnt_to_list.end()) {
                mn = node->count;
                // 查找新的最小值
                for (auto &pair : cnt_to_list) {
                    if (pair.first > 0 && pair.first < mn) {
                        mn = pair.first;
                    }
                }
            }
        } else {
            list_node *new_node = new list_node(1);
            new_node->s = key;
            str_to_node[key] = new_node;
            insert(new_node);

            if (mn == 0 || mn > 1) {
                mn = 1;
            }
            if (mx < 1) {
                mx = 1;
            }
        }
    }

    void dec(string key) {
        if (str_to_node.find(key) == str_to_node.end()) {
            return;
        }

        auto node = str_to_node[key];
        int old_count = node->count;
        remove(node);
        node->count--;

        if (node->count == 0) {
            str_to_node.erase(key);
            delete node;

            // 如果移除了最后一个节点，重置 mn 和 mx
            if (str_to_node.empty()) {
                mn = 0;
                mx = 0;
            }
            // 如果移除了最小计数的最后一个节点，更新 mn
            else if (old_count == mn && cnt_to_list.find(old_count) == cnt_to_list.end()) {
                mn = INT_MAX;
                for (auto &pair : cnt_to_list) {
                    if (pair.first > 0 && pair.first < mn) {
                        mn = pair.first;
                    }
                }
            }

            // 如果移除了最大计数的最后一个节点，更新 mx
            if (old_count == mx && cnt_to_list.find(old_count) == cnt_to_list.end()) {
                mx = 0;
                for (auto &pair : cnt_to_list) {
                    if (pair.first > mx) {
                        mx = pair.first;
                    }
                }
            }
        } else {
            insert(node);

            // 更新 mn
            if (node->count < mn) {
                mn = node->count;
            }

            // 如果移除了最大计数的最后一个节点，更新 mx
            if (old_count == mx && cnt_to_list.find(old_count) == cnt_to_list.end()) {
                mx = 0;
                for (auto &pair : cnt_to_list) {
                    if (pair.first > mx) {
                        mx = pair.first;
                    }
                }
            }
        }
    }

    string getMaxKey() {
        if (mx == 0) {
            return "";
        }

        // 返回链表中第一个实际节点的字符串值，跳过哑节点
        list_node *dummy = cnt_to_list[mx];
        return dummy->next->s;
    }

    string getMinKey() {
        if (mn == 0) {
            return "";
        }

        // 返回链表中第一个实际节点的字符串值，跳过哑节点
        list_node *dummy = cnt_to_list[mn];
        return dummy->next->s;
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */