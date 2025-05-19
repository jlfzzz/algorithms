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

using namespace std;

// 1，2二分，3最小堆

typedef long long ll;
class Solution {
public:
    int calculate_height(ll time, int workerTime) {
        //二分工人的height
        int lhs = 0, rhs = 100000;
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs) / 2;
            ll consumption = (ll)workerTime * ((ll)mid * (mid + 1) / 2);
            //说明给的时间不足以完成这么高
            if (consumption > time)
                rhs = mid - 1;
            else
                lhs = mid + 1;
        }
        return rhs;
    }

    bool check(int mountainHeight, vector<int> &workerTimes, ll time) {
        int total_height = 0;
        for (int workerTime : workerTimes) {
            total_height += calculate_height(time, workerTime);
        }
        //说明给的秒数过多, 需要移动右指针
        if (total_height >= mountainHeight)
            return false;
        else
            return true;//给的秒数过少，需要移动左指针
    }

    long long minNumberOfSeconds(int mountainHeight, vector<int> &workerTimes) {
        //二分秒数
        //一个工人,极限秒数为5,000,050,000,000,000
        //求得的秒数刚好使得移除的height >= moutainheight
        ll lhs = 1, rhs = 5000050000000000;
        while (lhs <= rhs) {
            ll mid = lhs + (rhs - lhs) / 2;
            if (check(mountainHeight, workerTimes, mid))
                lhs = mid + 1;
            else
                rhs = mid - 1;
        }
        return lhs;
    }
};


class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int> &workerTimes) {
        auto check = [&](long long m) {
            int left_h = mountainHeight;
            for (int t : workerTimes) {
                left_h -= ((int)sqrt(m / t * 8 + 1) - 1) / 2;
                if (left_h <= 0) {
                    return true;
                }
            }
            return false;
            };

        int max_t = ranges::max(workerTimes);
        int h = (mountainHeight - 1) / workerTimes.size() + 1;
        long long left = 0, right = (long long)max_t * h * (h + 1) / 2;
        while (left + 1 < right) {
            long long mid = (left + right) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right;
    }
};

class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        priority_queue<tuple<long long, long long, int>, vector<tuple<long long, long long, int>>, greater<>> pq;
        for (int t : workerTimes) {
            pq.emplace(t, t, t);
        }
        long long ans = 0;
        while (mountainHeight--) {
            // 工作后总用时，当前工作（山高度降低 1）用时，workerTimes[i]
            auto [nxt, delta, base] = pq.top(); pq.pop();
            ans = nxt; // 最后一个出堆的 nxt 即为答案
            pq.emplace(nxt + delta + base, delta + base, base);
        }
        return ans;
    }
};