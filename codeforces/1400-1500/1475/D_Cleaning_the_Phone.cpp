#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iterator>

using namespace std;

const int N = 2e5 + 5;

int arr[N];
int que1[N], tot1;
int que2[N], tot2;

void run() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        if (x == 1) {
            que1[tot1] = arr[i];
            ++tot1;
        } else {
            que2[tot2] = arr[i];
            ++tot2;
        }
    }
    sort(que1, que1 + tot1, greater<int>());
    sort(que2, que2 + tot2, greater<int>());
    int cnt1 = 0, cnt2 = 0;
    int h1 = 0, h2 = 0;
    while (cnt1 < m) {
        if (que1[h1] == 0 && que2[h2] == 0) {
            cnt2 = -1;
            break;
        }
        if (cnt1 + que1[h1] >= m) {
            ++cnt2;
            break;
        }
        if (que2[h2] >= que1[h1] + que1[h1 + 1]) {
            cnt1 += que2[h2];
            cnt2 += 2;
            ++h2;
        } else {
            cnt1 += que1[h1];
            ++cnt2;
            ++h1;
        }
    }
    printf("%d\n", cnt2);
    tot1 = 0, tot2 = 0;
    memset(que1, 0, sizeof que1);
    memset(que2, 0, sizeof que2);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        run();
    }
}
