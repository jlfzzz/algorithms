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

class TimeMap {
public:
    unordered_map<string, vector<pair<string, int>>> history;

    TimeMap() {

    }

    void set(string key, string value, int timestamp) {
        history[key].emplace_back(value, timestamp);
    }

    string get(string key, int timestamp) {
        if (history.find(key) == history.end()) {
            return ""; // Key not found
        }


        auto &v = history[key];
        if (v.empty()) {
            return "";
        }

        auto it = upper_bound(v.begin(), v.end(), timestamp,
            [](int ts_target, const pair<string, int> &element) {
                // Return true if ts_target < element's timestamp
                return ts_target < element.second;
            });

        // 4. Interpret the result of upper_bound:
        //    a) If `it` is the beginning of the vector (`v.begin()`):
        //       This means all timestamps in the vector are strictly greater than the target `timestamp`.
        //       Therefore, no value exists with timestamp <= target `timestamp`.
        if (it == v.begin()) {
            return "";
        }
        //    b) Otherwise (`it != v.begin()`):
        //       `it` points to the first element with timestamp > target `timestamp`.
        //       The element we are looking for (largest timestamp <= target `timestamp`)
        //       is the one *immediately before* `it`. We access it using `prev(it)`.
        else {
            // `prev(it)` gives an iterator to the previous element.
            // `->first` accesses the string value part of the pair.
            return prev(it)->first;
        }
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */