#include <bits/stdc++.h>
using namespace std;

int a[200002];
int b[200002];
int c[200002];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            cin >> b[i];
        int suma = 0, sumb = 0, s = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] > b[i])
                suma += a[i];
            else if (a[i] < b[i])
                sumb += b[i];
            else if (a[i] != 0)
                c[++s] = a[i];
        }
        for (int i = 1; i <= s; i++) {
            if (suma >= sumb) {
                if (c[i] == 1)
                    sumb++;
                else
                    suma--;
            } else {
                if (c[i] == 1)
                    suma++;
                else
                    sumb--;
            }
        }
        cout << min(suma, sumb) << "\n";
    }
    return 0;
}
