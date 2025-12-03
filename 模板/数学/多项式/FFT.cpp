#include <bits/stdc++.h>
using namespace std;


struct FFT {
    using cd = complex<double>;
    const double PI = acos(-1);

    vector<int> rev;
    void init_rev(int limit) {
        int bit = 0;
        while ((1 << bit) < limit)
            bit++;

        rev.resize(limit);
        rev[0] = 0;
        for (int i = 1; i < limit; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        }
    }

    void fft(vector<cd> &a, bool invert) {
        int n = a.size();

        if (rev.size() != n) {
            init_rev(n);
        }

        for (int i = 0; i < n; i++) {
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);
            }
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; j++) {
                    cd u = a[i + j];
                    cd v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (cd &x: a)
                x /= n;
        }
    }

    vector<long long> multiply(const vector<int> &const_a, const vector<int> &const_b) {
        vector<cd> fa(const_a.begin(), const_a.end());
        vector<cd> fb(const_b.begin(), const_b.end());
        int n = 1;
        while (n < const_a.size() + const_b.size())
            n <<= 1;
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++)
            fa[i] *= fb[i];
        fft(fa, true);

        vector<long long> result(n);
        for (int i = 0; i < n; i++)
            result[i] = round(fa[i].real());
        return result;
    }
};
