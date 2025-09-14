#include <cstring>
#include <iostream>

using namespace std;

const int N = 100000;
long long dp[N + 10];
int c[5], d[5];

int main() {
    for (int i = 1; i <= 4; i++) {
        cin >> c[i];
    }

    dp[0] = 1;
    for (int i = 1; i <= 4; i++) {
        for (int j = c[i]; j <= N; j++) {
            dp[j] += dp[j - c[i]];
        }
    }

    int T;
    cin >> T;

    while (T--) {
        for (int i = 1; i <= 4; i++) {
            cin >> d[i];
        }
        int sum;
        cin >> sum;

        long long result = 0;
        for (int mask = 0; mask < 16; mask++) {
            long long temp_sum = sum;
            int sign = 1;

            for (int i = 0; i < 4; i++) {
                if (mask & (1 << i)) {
                    temp_sum -= c[i + 1] * (d[i + 1] + 1);
                    sign = -sign;
                }
            }

            if (temp_sum >= 0) {
                if (sign == 1) {
                    result += dp[temp_sum];
                } else {
                    result -= dp[temp_sum];
                }
            }
        }

        cout << result << endl;
    }

    return 0;
}
