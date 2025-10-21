#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
    int cost;
};

struct MinCostMaxFlow {
    int n;
    vector<vector<Edge>> graph;
    MinCostMaxFlow(int n_) : n(n_), graph(n_) {}

    void addEdge(int u, int v, int cap, int cost) {
        Edge a{v, (int) graph[v].size(), cap, cost};
        Edge b{u, (int) graph[u].size(), 0, -cost};
        graph[u].push_back(a);
        graph[v].push_back(b);
    }

    pair<int, long long> minCostMaxFlow(int s, int t, int maxNeededFlow) {
        int flow = 0;
        long long cost = 0;
        const long long INFLL = (1LL << 60);
        vector<long long> dist(n);
        vector<int> inq(n);
        vector<int> pvNode(n);
        vector<int> pvEdge(n);
        while (flow < maxNeededFlow) {
            for (int i = 0; i < n; ++i) {
                dist[i] = INFLL;
                inq[i] = 0;
                pvNode[i] = -1;
                pvEdge[i] = -1;
            }
            deque<int> dq;
            dist[s] = 0;
            dq.push_back(s);
            inq[s] = 1;
            while (!dq.empty()) {
                int u = dq.front();
                dq.pop_front();
                inq[u] = 0;
                for (int ei = 0; ei < (int) graph[u].size(); ++ei) {
                    Edge const &e = graph[u][ei];
                    if (e.cap <= 0) {
                        continue;
                    }
                    int v = e.to;
                    long long nd = dist[u] + e.cost;
                    if (nd < dist[v]) {
                        dist[v] = nd;
                        pvNode[v] = u;
                        pvEdge[v] = ei;
                        if (!inq[v]) {
                            if (!dq.empty() && nd < dist[dq.front()]) {
                                dq.push_front(v);
                            } else {
                                dq.push_back(v);
                            }
                            inq[v] = 1;
                        }
                    }
                }
            }
            if (dist[t] == INFLL) {
                break;
            }
            int add = maxNeededFlow - flow;
            int v = t;
            while (v != s) {
                int u = pvNode[v];
                int ei = pvEdge[v];
                if (u == -1 || ei == -1) {
                    add = 0;
                    break;
                }
                add = min(add, graph[u][ei].cap);
                v = u;
            }
            if (add == 0) {
                break;
            }
            v = t;
            while (v != s) {
                int u = pvNode[v];
                int ei = pvEdge[v];
                Edge &e = graph[u][ei];
                Edge &re = graph[v][e.rev];
                e.cap -= add;
                re.cap += add;
                v = u;
            }
            flow += add;
            cost += (long long) add * dist[t];
        }
        return {flow, cost};
    }
};

static bool isAllowed(char ch, int pos, int n, int countH) {
    int oneBased = pos + 1;
    bool isTslot = (oneBased % 3 == 0);
    if (ch == 'T') {
        if (isTslot) {
            return true;
        } else {
            return false;
        }
    }
    if (isTslot) {
        return false;
    }
    if (ch == 'H') {
        if (countH == 1 && pos == 0) {
            return true;
        } else {
            return false;
        }
    }
    if (ch == 'b') {
        if (pos != 0 && pos != n - 1) {
            return true;
        } else {
            return false;
        }
    }
    if (ch == 'o') {
        if (countH == 1 && pos == 0) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }
    string s;
    cin >> s;
    if ((int) s.size() != n) {
        // If input length mismatches, consider impossible
        cout << -1 << '\n';
        return 0;
    }

    int cntT = 0, cntH = 0, cntB = 0, cntO = 0;
    for (char c: s) {
        if (c == 'T') {
            cntT += 1;
        } else if (c == 'H') {
            cntH += 1;
        } else if (c == 'b') {
            cntB += 1;
        } else if (c == 'o') {
            cntO += 1;
        } else {
            cout << -1 << '\n';
            return 0;
        }
    }

    int needT = n / 3; // positions 3,6,9,... (1-based)
    if (cntT != needT) {
        cout << -1 << '\n';
        return 0;
    }
    if (!(cntH == 0 || cntH == 1)) {
        cout << -1 << '\n';
        return 0;
    }
    if (cntB < 1 || cntO < 1) {
        cout << -1 << '\n';
        return 0;
    }

    int N = 2 * n + 2;
    int S = 0;
    int T = 2 * n + 1;
    MinCostMaxFlow mcmf(N);

    for (int i = 0; i < n; ++i) {
        mcmf.addEdge(S, 1 + i, 1, 0);
    }
    for (int i = 0; i < n; ++i) {
        char ch = s[i];
        for (int j = 0; j < n; ++j) {
            if (isAllowed(ch, j, n, cntH)) {
                int cost = abs(i - j);
                mcmf.addEdge(1 + i, 1 + n + j, 1, cost);
            } else {
                continue;
            }
        }
    }
    for (int j = 0; j < n; ++j) {
        mcmf.addEdge(1 + n + j, T, 1, 0);
    }

    auto res = mcmf.minCostMaxFlow(S, T, n);
    if (res.first != n) {
        cout << -1 << '\n';
    } else {
        cout << res.second << '\n';
    }
    return 0;
}
