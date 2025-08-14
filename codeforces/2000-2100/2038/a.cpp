#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>


using namespace std;

int main() {
    // 提高cin/cout效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;
    cin >> n >> k;

    vector<long long> a(n);
    vector<long long> b(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    // 1. 预计算每个工程师最多愿意做的工作
    vector<long long> max_work(n);
    long long total_max_work = 0;
    for (int i = 0; i < n; ++i) {
        max_work[i] = a[i] / b[i];
        total_max_work += max_work[i];
    }

    // 如果总潜力不足，项目不可能完成
    if (total_max_work < k) {
        for (int i = 0; i < n; ++i) {
            cout << 0 << (i == n - 1 ? "" : " ");
        }
        cout << endl;
        return 0;
    }

    // 2. 预计算后缀和，用于快速查找“后续潜力”
    vector<long long> suffix_sum(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        suffix_sum[i] = suffix_sum[i + 1] + max_work[i];
    }

    // 3. 模拟决策过程
    vector<long long> result(n);
    long long work_done_so_far = 0;

    for (int i = 0; i < n; ++i) {
        long long needed = k - work_done_so_far;

        // 后续工程师能提供的最大工作量
        long long future_potential = suffix_sum[i + 1];

        // 我为了让项目有成功的可能，至少要承担的工作量
        long long my_work = needed - future_potential;

        // 工作量不能为负，且不能超过我愿意做的最大值
        my_work = max(0LL, my_work);
        my_work = min(my_work, max_work[i]); // 这一步其实是多余的，因为初始的总量检查保证了不会超

        result[i] = my_work;
        work_done_so_far += my_work;
    }

    // 4. 输出结果
    for (int i = 0; i < n; ++i) {
        cout << result[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
