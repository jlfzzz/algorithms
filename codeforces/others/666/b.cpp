//
// Created by 123 on 25-7-19.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

/*
 *B. World Tour
time limit per test5 seconds
memory limit per test512 megabytes
A famous sculptor Cicasso goes to a world tour!

Well, it is not actually a world-wide. But not everyone should have the opportunity to see works of sculptor, shouldn't he? Otherwise there will be no any exclusivity. So Cicasso will entirely hold the world tour in his native country — Berland.

Cicasso is very devoted to his work and he wants to be distracted as little as possible. Therefore he will visit only four cities. These cities will be different, so no one could think that he has "favourites". Of course, to save money, he will chose the shortest paths between these cities. But as you have probably guessed, Cicasso is a weird person. Although he doesn't like to organize exhibitions, he likes to travel around the country and enjoy its scenery. So he wants the total distance which he will travel to be as large as possible. However, the sculptor is bad in planning, so he asks you for help.

There are n cities and m one-way roads in Berland. You have to choose four different cities, which Cicasso will visit and also determine the order in which he will visit them. So that the total distance he will travel, if he visits cities in your order, starting from the first city in your list, and ending in the last, choosing each time the shortest route between a pair of cities — will be the largest.

Note that intermediate routes may pass through the cities, which are assigned to the tour, as well as pass twice through the same city. For example, the tour can look like that: . Four cities in the order of visiting marked as overlines: [1, 5, 2, 4].

Note that Berland is a high-tech country. So using nanotechnologies all roads were altered so that they have the same length. For the same reason moving using regular cars is not very popular in the country, and it can happen that there are such pairs of cities, one of which generally can not be reached by car from the other one. However, Cicasso is very conservative and cannot travel without the car. Choose cities so that the sculptor can make the tour using only the automobile. It is guaranteed that it is always possible to do.

Input
In the first line there is a pair of integers n and m (4 ≤ n ≤ 3000, 3 ≤ m ≤ 5000) — a number of cities and one-way roads in Berland.

Each of the next m lines contains a pair of integers ui, vi (1 ≤ ui, vi ≤ n) — a one-way road from the city ui to the city vi. Note that ui and vi are not required to be distinct. Moreover, it can be several one-way roads between the same pair of cities.

Output
Print four integers — numbers of cities which Cicasso will visit according to optimal choice of the route. Numbers of cities should be printed in the order that Cicasso will visit them. If there are multiple solutions, print any of them.

Example
InputCopy
8 9
1 2
2 3
3 4
4 1
4 5
5 6
6 7
7 8
8 5
OutputCopy
2 1 8 7
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    // 计算所有点对之间的最短距离
    vector<vector<int>> dis(n + 1, vector<int>(n + 1, -1));

    // 对每个起点进行BFS
    for (int start = 1; start <= n; start++) {
        queue<int> q;
        vector<bool> visited(n + 1, false);

        q.push(start);
        visited[start] = true;
        dis[start][start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : graph[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    dis[start][v] = dis[start][u] + 1;
                    q.push(v);
                }
            }
        }
    }

    // to[i]: 能到达点i的前3个最远点
    // fr[i]: 从点i能到达的前3个最远点
    vector<vector<int>> to(n + 1, vector<int>(3, 0));
    vector<vector<int>> fr(n + 1, vector<int>(3, 0));

    for (int i = 1; i <= n; i++) {
        // 找到能到达点i的前3个最远点
        vector<int> candidates_to;
        for (int j = 1; j <= n; j++) {
            if (j != i && dis[j][i] != -1) {
                candidates_to.push_back(j);
            }
        }
        sort(candidates_to.begin(), candidates_to.end(), [&](int x, int y) {
            return dis[x][i] > dis[y][i];
        });
        for (int j = 0; j < min(3, static_cast<int>(candidates_to.size())); j++) {
            to[i][j] = candidates_to[j];
        }

        // 找到从点i能到达的前3个最远点
        vector<int> candidates_fr;
        for (int j = 1; j <= n; j++) {
            if (j != i && dis[i][j] != -1) {
                candidates_fr.push_back(j);
            }
        }
        sort(candidates_fr.begin(), candidates_fr.end(), [&](int x, int y) {
            return dis[i][x] > dis[i][y];
        });
        for (int j = 0; j < min(3, static_cast<int>(candidates_fr.size())); j++) {
            fr[i][j] = candidates_fr[j];
        }
    }

    vector<int> ans(4, -1);
    int max_len = -1;

    // 枚举中间两个点 b, c
    for (int b = 1; b <= n; b++) {
        for (int c = 1; c <= n; c++) {
            if (b == c || dis[b][c] == -1) continue;

            int a = 0, d = 0;

            // 策略1: 先选择到达b的最远点a，再选择从c出发的最远点d（避免冲突）
            for (int i = 0; i < 3; i++) {
                if (to[b][i] != 0 && to[b][i] != c && dis[to[b][i]][b] != -1) {
                    a = to[b][i];
                    break;
                }
            }
            for (int i = 0; i < 3; i++) {
                if (fr[c][i] != 0 && fr[c][i] != a && fr[c][i] != b && dis[c][fr[c][i]] != -1) {
                    d = fr[c][i];
                    break;
                }
            }

            if (a != 0 && d != 0) {
                int total_dist = dis[a][b] + dis[b][c] + dis[c][d];
                if (total_dist > max_len) {
                    max_len = total_dist;
                    ans[0] = a;
                    ans[1] = b;
                    ans[2] = c;
                    ans[3] = d;
                }
            }

            // 策略2: 先选择从c出发的最远点d，再选择到达b的最远点a（避免冲突）
            a = 0, d = 0;
            for (int i = 0; i < 3; i++) {
                if (fr[c][i] != 0 && fr[c][i] != b && dis[c][fr[c][i]] != -1) {
                    d = fr[c][i];
                    break;
                }
            }
            for (int i = 0; i < 3; i++) {
                if (to[b][i] != 0 && to[b][i] != c && to[b][i] != d && dis[to[b][i]][b] != -1) {
                    a = to[b][i];
                    break;
                }
            }

            if (a != 0 && d != 0) {
                int total_dist = dis[a][b] + dis[b][c] + dis[c][d];
                if (total_dist > max_len) {
                    max_len = total_dist;
                    ans[0] = a;
                    ans[1] = b;
                    ans[2] = c;
                    ans[3] = d;
                }
            }
        }
    }

    for (int x : ans) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
