#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>


// 定义点结构，存储坐标和计算出的正确距离
struct Point {
    int x, y, dis;
};

// 自定义比较函数，用于构建最小堆
// 优先级: 1. 距离(dis) 2. x坐标 3. y坐标
auto cmp = [](const Point &a, const Point &b) {
    if (a.dis != b.dis)
        return a.dis > b.dis;
    if (a.x != b.x)
        return a.x > b.x;
    return a.y > b.y;
};

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> guests(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> guests[i];
    }

    // Type 1 客人的选择池：所有已知的可用座位
    std::priority_queue<Point, std::vector<Point>, decltype(cmp)> pq_any_seat(cmp);
    // Type 0 客人的选择池：所有已知的空桌子的最佳座位
    std::priority_queue<Point, std::vector<Point>, decltype(cmp)> pq_empty_table(cmp);

    // 状态记录
    std::map<std::pair<int, int>, int> table_occupancy; // 桌子(X,Y) -> 占用人数
    std::set<std::pair<int, int>> occupied_cells; // 已被占用的座位(x,y)
    std::set<std::pair<int, int>> discovered_tables; // 已被发现的桌子(X,Y)

    // 辅助函数：发现一张新桌子并将其座位加入两个队列
    auto discover_table = [&](int X, int Y) {
        if (discovered_tables.count({X, Y})) {
            return;
        }
        discovered_tables.insert({X, Y});

        // 1. 将这张空桌的最佳座位加入 Type 0 的队列
        pq_empty_table.push({3 * X + 1, 3 * Y + 1, 3 * (X + Y) + 2});

        // 2. 将这张桌子的全部4个座位加入 Type 1 的队列
        pq_any_seat.push({3 * X + 1, 3 * Y + 1, 3 * (X + Y) + 2});
        pq_any_seat.push({3 * X + 1, 3 * Y + 2, 3 * (X + Y) + 3});
        pq_any_seat.push({3 * X + 2, 3 * Y + 1, 3 * (X + Y) + 3});
        pq_any_seat.push({3 * X + 2, 3 * Y + 2, 3 * (X + Y) + 6});
    };

    // 初始状态：只发现 (0,0) 这一张桌子
    discover_table(0, 0);

    for (int guest_type: guests) {
        Point choice;

        if (guest_type == 1) { // Type 1: 任何空位都可以
            while (true) {
                Point p = pq_any_seat.top();
                pq_any_seat.pop();
                // 懒删除：如果这个座位已经被占用了，就跳过
                if (occupied_cells.count({p.x, p.y})) {
                    continue;
                }
                choice = p;
                break;
            }
        } else { // Type 0: 需要一张完全没被占用的桌子
            while (true) {
                Point p = pq_empty_table.top();
                pq_empty_table.pop();
                // 懒删除：如果这个座位已被占用，或其所在桌子已有别人，就跳过
                if (occupied_cells.count({p.x, p.y})) {
                    continue;
                }
                int table_X = (p.x - 1) / 3;
                int table_Y = (p.y - 1) / 3;
                if (table_occupancy.count({table_X, table_Y})) {
                    continue;
                }
                choice = p;
                break;
            }
        }

        std::cout << choice.x << " " << choice.y << "\n";

        // 更新所有状态
        occupied_cells.insert({choice.x, choice.y});
        int table_X = (choice.x - 1) / 3;
        int table_Y = (choice.y - 1) / 3;

        // 如果这是该桌子第一次被占用，就去发现它的邻居
        if (!table_occupancy.count({table_X, table_Y})) {
            discover_table(table_X + 1, table_Y);
            discover_table(table_X, table_Y + 1);
        }
        table_occupancy[{table_X, table_Y}]++;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T = 1;
    std::cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
