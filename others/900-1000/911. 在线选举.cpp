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

using namespace std;

class TopVotedCandidate {
public:
    vector<int> winners;
    vector<int> times;

    TopVotedCandidate(vector<int> &persons, vector<int> &times) {
        this->times = times;
        winners.resize(times.size());

        unordered_map<int, int> voteCount;
        int leadingPerson = -1;
        int maxVotes = 0;

        for (int i = 0; i < persons.size(); i++) {
            int person = persons[i];
            voteCount[person]++;

            if (voteCount[person] >= maxVotes) {
                maxVotes = voteCount[person];
                leadingPerson = person;
            }

            winners[i] = leadingPerson;
        }
    }

    int q(int t) {
        // 找到不大于t的最大时间点
        int idx = upper_bound(times.begin(), times.end(), t) - times.begin() - 1;
        return winners[idx];
    }
};