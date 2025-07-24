#include <algorithm>
#include <ranges>
#include<vector>

using namespace std;

class Solution {
public:
    long long minimumTime(vector<int> &time, int totalTrips) {
        long long low = 1;
        long long high = 0;
        for (long long t : time) {
            high = max(high, t);
        }
        long long totalTime = high * totalTrips;
        long long result = totalTime;
        while (low < totalTime) {
            long long t = (totalTime - low) / 2 + low;
            long long count = getTime(time, t);
            if (count >= totalTrips) {
                result = t;
                totalTime = t;
            } else {
                low = t + 1;
            }
        }
        return result;
    }

    long long getTime(const vector<int> &times, int totalTime) {
        long time = 0;
        for (int t : times) {
            time += totalTime / t;
        }
        return time;
    }
};