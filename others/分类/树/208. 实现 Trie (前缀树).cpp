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

using namespace std;

class Trie {
public:
    struct Node { // 改名为 Node
        // int val; // val 在 Trie 节点中不常用，除非有特殊含义
        std::map<char, std::shared_ptr<Node>> children;
        bool isEndOfWord = false;
        // ...
    };
    std::shared_ptr<Node> root; // 指向根节点

    Trie() : root(std::make_shared<Node>()) {}

    void insert(string word) {
        int n = word.size();
        // Start traversal from the root node.
        // Do NOT create a new node here like your initial attempt.
        std::shared_ptr<Node> curr = root;

        for (int i = 0; i < n; i++) {
            char c = word[i];

            // Check if a child node corresponding to character 'c' exists.
            // map::find returns an iterator to the element, or map::end() if not found.
            auto it = curr->children.find(c);

            if (it == curr->children.end()) {
                // If the path for 'c' does not exist, create a new node
                // and add it to the children map of the current node.
                curr->children[c] = std::make_shared<Node>();
            }

            // Move to the appropriate child node (either existing or newly created).
            // Using operator[] is convenient here: it finds the element or inserts
            // a default-constructed one if not found (though we handled insertion above).
            // Accessing via the key 'c' is safe now.
            curr = curr->children[c];
        }

        // After processing all characters of the word, mark the final node
        // as the end of a complete word.
        curr->isEndOfWord = true;
    }

    bool search(string word) {
        int n = word.size();
        std::shared_ptr<Node> curr = root;

        for (int i = 0; i < n; i++) {
            char c = word[i];
            auto it = curr->children.find(c); 
            if (it == curr->children.end()) {
                return false;
            }
            curr = it->second; 
        }

        return curr->isEndOfWord;
    }

    bool startsWith(string prefix) {
        int n = prefix.size();
        shared_ptr<Node> curr = root;

        for (int i = 0; i < n; i++) {
            char c = prefix[i];
            auto it = curr->children.find(c);
            if (it == curr->children.end()) {
                // 如果前缀路径不存在，直接返回 false
                return false;
            }
            curr = it->second;
        }

        // 如果循环成功完成，说明前缀路径存在，直接返回 true
        return true;

        
        // int n = prefix.size();
        // shared_ptr<Node> curr = root;

        // for (int i = 0; i < n; i++) {
        //     char c = prefix[i];
        //     auto it = curr->children.find(c);
        //     if (it == curr->children.end()) return false;

        //     curr = it->second;
        // }

        // auto dfs = [&](this auto &&dfs, shared_ptr<Node> node) -> bool {
        //     if (!node) return false;

        //     if (node->isEndOfWord) return true;

        //     for (auto &n : node->children) {
        //         if (dfs(n.second)) return true;
        //     }
        //     return false;
        //     };

        // return dfs(curr);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */


