class Solution {
public:
    int numberOfChild(int n, int k) {
        int rounds = k / (n - 1);
        int left = k % (n - 1);
        return rounds % 2 ? n - left - 1 : left;
    }
};