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

using namespace std;

class SnapshotArray {
    unordered_map<int, vector<pair<int, int>>> history; // 每个 index 的历史修改记录
    int cur_snap_id = 0;

public:
    SnapshotArray(int) {}

    void set(int index, int val) {
        history[index].emplace_back(cur_snap_id, val);
    }

    int snap() {
        return cur_snap_id++;
    }

    int get(int index, int snap_id) {
        auto &h = history[index];
        // 找快照编号 <= snap_id 的最后一次修改记录
        // 等价于找快照编号 >= snap_id+1 的第一个修改记录，它的上一个就是答案
        int j = ranges::lower_bound(h, pair(snap_id + 1, 0)) - h.begin() - 1;
        return j >= 0 ? h[j].second : 0;
    }
};