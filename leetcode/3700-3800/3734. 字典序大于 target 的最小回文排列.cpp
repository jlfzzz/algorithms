class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        unordered_map<char, int> cnt;
        for (char c: s) {
            cnt[c]++;
        }
        {
            int c = 0;
            for (auto &[k, v]: cnt) {
                if (v & 1) {
                    c++;
                }
            }
            if (c > 1) {
                return "";
            }
        }

        char odd = '?';
        for (auto &[k, v]: cnt) {
            if (v & 1) {
                odd = k;
            }
        }
        if (odd != '?') {
            cnt[odd]--;
        }

        vector<int> oks;
        unordered_map<char, int> cnt2 = cnt;

        for (int i = 0; i < n / 2; i++) {
            char c2 = target[i];

            bool find = false;
            for (char c = c2 + 1; c <= 'z'; c++) {
                if (cnt2.contains(c) && cnt2[c] >= 2) {
                    find = true;
                    break;
                }
            }

            if (find) {
                oks.push_back(i);
            }

            if (cnt2.contains(c2) && cnt2[c2] >= 2) {
                cnt2[c2] -= 2;
                if (cnt2[c2] == 0) {
                    cnt2.erase(c2);
                }

                // cout << i << endl;
                if (i == n / 2 - 1) {
                    string half = target.substr(0, n / 2);
                    auto right = half;
                    if (odd != '?') {
                        half += odd;
                    }
                    reverse(right.begin(), right.end());
                    half += right;
                    if (half > target) {
                        return half;
                    }
                }
            } else {
                break;
            }
        }

        if (oks.empty()) {
            // cout << 1 << endl;
            unordered_map<char, int> cntt = cnt;
            string half = target.substr(0, n / 2);
            bool can = true;
            for (char c: half) {
                if (cntt.contains(c) && cntt[c] >= 2) {
                    cntt[c] -= 2;
                } else {
                    can = false;
                    break;
                }
            }

            if (can) {
                string left = half;
                string right = half;
                reverse(right.begin(), right.end());
                if (odd != '?') {
                    left += odd;
                }
                left += right;

                if (left > target) {
                    return left;
                }
            }

            return "";
        }

        int pos1 = oks.back();
        cout << pos1 << endl;
        string ans;
        for (int i = 0; i < pos1; i++) {
            ans += target[i];
            cnt[target[i]] -= 2;
        }

        char c2 = target[pos1];
        for (char c = c2 + 1; c <= 'z'; c++) {
            if (cnt.contains(c) && cnt[c] >= 2) {
                ans += c;
                cnt[c] -= 2;
                break;
            }
        }

        int half = n / 2;
        while (ans.size() < half) {
            for (char c = 'a'; c <= 'z'; c++) {
                if (cnt.contains(c) && cnt[c] >= 2) {
                    ans += c;
                    cnt[c] -= 2;
                    break;
                }
            }
        }

        string rev = ans;
        reverse(rev.begin(), rev.end());
        if (odd != '?') {
            ans += odd;
        }
        ans += rev;

        return ans;
    }
};
