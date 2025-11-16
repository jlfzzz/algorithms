#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

struct Point {
    ll x, y;
};

ll distSq(Point p1, Point p2) { return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y); }

double getDist(Point p1, Point p2) { return sqrt(distSq(p1, p2)); }

ll cross_product(Point a, Point b) { return a.x * b.y - a.y * b.x; }

ll cross_product(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }

vector<Point> buildConvexHull(vector<Point> &pts) {
    int n = pts.size();
    if (n <= 2)
        return pts;

    sort(pts.begin(), pts.end(), [](const Point &a, const Point &b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });

    vector<Point> hull;
    for (int i = 0; i < n; ++i) {
        while (hull.size() >= 2 && cross_product(hull[hull.size() - 2], hull.back(), pts[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() > lower_size && cross_product(hull[hull.size() - 2], hull.back(), pts[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }

    if (hull.size() > 1)
        hull.pop_back();
    return hull;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    double r;
    cin >> n >> r;

    vector<Point> pts(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }

    vector<Point> hull = buildConvexHull(pts);

    double min_dist = 1e18;
    bool f = true;

    if (hull.size() < 3) {
        f = false;
    } else {
        for (int i = 0; i < hull.size(); ++i) {
            Point p1 = hull[i];
            Point p2 = hull[(i + 1) % hull.size()];

            ll cp = cross_product(p1, p2);

            if (cp < 0) {
                f = false;
                break;
            }
        }
    }

    if (!f) {
        min_dist = 0.0;
    } else {
        for (int i = 0; i < hull.size(); ++i) {
            Point p1 = hull[i];
            Point p2 = hull[(i + 1) % hull.size()];

            double cp = abs((double) cross_product(p1, p2));
            double len = getDist(p1, p2);

            double d = cp / len;
            if (d < min_dist) {
                min_dist = d;
            }
        }
    }

    double ans = r * r * acos(min_dist / r) - min_dist * sqrt(r * r - min_dist * min_dist);
    cout << fixed << setprecision(20) << ans << '\n';

    return 0;
}
