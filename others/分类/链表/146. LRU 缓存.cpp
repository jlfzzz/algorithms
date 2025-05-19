#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

struct DLinkedNode {
    int key, value;
    DLinkedNode *prev;
    DLinkedNode *next;
    DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkedNode *> cache;
    DLinkedNode *head;
    DLinkedNode *tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity) : capacity(_capacity), size(0) {
        // 使用伪头部和伪尾部节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode *node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode *node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode *removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        } else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode *node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode *node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(DLinkedNode *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode *node) {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode *removeTail() {
        DLinkedNode *node = tail->prev;
        removeNode(node);
        return node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

 /*
 int capacity;
    unordered_map<int, int> map;
    vector <int> list;
    int count;

    LRUCache(int capacity) {
        this->capacity = capacity;
        count = 0;
    }

    int get(int key) {
        if (!map.count(key)) {
            return -1;
        }

        auto it = find(list.begin(), list.end(), key);
        list.erase(it);
        list.push_back(key);
        return map[key];
    }

    void put(int key, int value) {
        if (map.count(key)) {
            // 键已存在，更新值并更新使用顺序
            map[key] = value;
            auto it = find(list.begin(), list.end(), key);
            list.erase(it);
            list.push_back(key);
        } else {
            // 键不存在，需要添加新元素
            if (count == capacity) {
                // 缓存已满，移除最久未使用的元素（列表头部）
                int lru_key = list.front();
                list.erase(list.begin());
                map.erase(lru_key);
                count--;
            }

            // 添加新元素
            map[key] = value;
            list.push_back(key);
            count++;
        }
    }
        */