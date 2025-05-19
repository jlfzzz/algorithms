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
#include <cstring>

using namespace std;

class Solution {
public:
    int bestTeamScore(vector<int> &scores, vector<int> &ages) {
        int n = scores.size();
        pair<int, int> a[n];
        for (int i = 0; i < n; ++i)
            a[i] = { scores[i], ages[i] };
        sort(a, a + n);

        int f[n]; memset(f, 0, sizeof(f));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j)
                if (a[j].second <= a[i].second)
                    f[i] = max(f[i], f[j]);
            f[i] += a[i].first;
        }
        return *max_element(f, f + n);
    }
};
