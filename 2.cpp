
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n = 0;
    vector<int> bit;
    explicit Fenwick(int n_) : n(n_), bit(n_ + 1, 0) {}
    void add(int idx, int delta) {
        for (int i = idx; i <= n; i += i & -i) {
            bit[i] += delta;
        }
    }
    int sumPrefix(int idx) const {
        int res = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            res += bit[i];
        }
        return res;
    }
    int sumRange(int l, int r) const {
        if (l > r) {
            return 0;
        }
        return sumPrefix(r) - sumPrefix(l - 1);
    }
};

struct FriendInterval {
    long long start;
    long long end;
};

struct Activity {
    long long start;
    long long end;
    long long fun;
    int attendees = 0;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numFriends;
    if (!(cin >> numFriends)) {
        return 0;
    }

    vector<FriendInterval> friendsList(numFriends);
    for (int i = 0; i < numFriends; ++i) {
        long long a, b;
        cin >> a >> b;
        friendsList[i] = {a, b};
    }

    int numActivities;
    cin >> numActivities;
    vector<Activity> activities(numActivities);
    for (int i = 0; i < numActivities; ++i) {
        long long s, e, f;
        cin >> s >> e >> f;
        activities[i] = {s, e, f, 0};
    }

    if (numActivities == 0) {
        cout << 0 << '\n';
        return 0;
    }

    // Discretize friend ends and activity ends for Fenwick over end times
    vector<long long> allEnds;
    allEnds.reserve(numFriends + numActivities);
    for (const auto &fr: friendsList) {
        allEnds.push_back(fr.end);
    }
    for (const auto &ac: activities) {
        allEnds.push_back(ac.end);
    }
    sort(allEnds.begin(), allEnds.end());
    allEnds.erase(unique(allEnds.begin(), allEnds.end()), allEnds.end());

    auto getEndIndex = [&](long long x) {
        int idx = int(lower_bound(allEnds.begin(), allEnds.end(), x) - allEnds.begin()) + 1; // 1-indexed
        return idx;
    };

    // Prepare friends sorted by start, and activities sorted by start
    vector<pair<long long, int>> friendsByStart; // (start, endIndex)
    friendsByStart.reserve(numFriends);
    for (const auto &fr: friendsList) {
        friendsByStart.emplace_back(fr.start, getEndIndex(fr.end));
    }
    sort(friendsByStart.begin(), friendsByStart.end());

    vector<int> activityEndIndex(numActivities, 0);
    vector<int> orderByStart(numActivities);
    iota(orderByStart.begin(), orderByStart.end(), 0);
    sort(orderByStart.begin(), orderByStart.end(), [&](int i, int j) {
        if (activities[i].start != activities[j].start) {
            return activities[i].start < activities[j].start;
        }
        return activities[i].end < activities[j].end;
    });
    for (int i = 0; i < numActivities; ++i) {
        activityEndIndex[i] = getEndIndex(activities[i].end);
    }

    // Sweep to compute attendees per activity: friends with start <= activity.start and end >= activity.end
    Fenwick fw((int) allEnds.size());
    int insertedFriends = 0;
    int friendPtr = 0;
    for (int idx: orderByStart) {
        long long actStart = activities[idx].start;
        while (friendPtr < (int) friendsByStart.size() && friendsByStart[friendPtr].first <= actStart) {
            fw.add(friendsByStart[friendPtr].second, 1);
            ++insertedFriends;
            ++friendPtr;
        }
        int eIdx = activityEndIndex[idx];
        int numWithEndGE = insertedFriends - fw.sumPrefix(eIdx - 1);
        if (numWithEndGE < 0) {
            numWithEndGE = 0;
        }
        activities[idx].attendees = numWithEndGE;
    }

    // Weighted interval scheduling on activities with weight = attendees * fun
    vector<int> orderByEnd(numActivities);
    iota(orderByEnd.begin(), orderByEnd.end(), 0);
    sort(orderByEnd.begin(), orderByEnd.end(), [&](int i, int j) {
        if (activities[i].end != activities[j].end) {
            return activities[i].end < activities[j].end;
        }
        return activities[i].start < activities[j].start;
    });

    vector<long long> endsSorted(numActivities);
    for (int i = 0; i < numActivities; ++i) {
        endsSorted[i] = activities[orderByEnd[i]].end;
    }

    vector<long long> dp(numActivities + 1, 0);
    for (int i = 0; i < numActivities; ++i) {
        const Activity &ac = activities[orderByEnd[i]];
        long long weight = ac.fun * 1LL * ac.attendees;
        // find last j < i with end <= ac.start
        int j = int(upper_bound(endsSorted.begin(), endsSorted.begin() + i, ac.start) - endsSorted.begin()) - 1;
        long long take = weight;
        if (j >= 0) {
            take += dp[j + 1];
        }
        dp[i + 1] = max(dp[i], take);
    }

    cout << dp[numActivities] << '\n';
    return 0;
}
