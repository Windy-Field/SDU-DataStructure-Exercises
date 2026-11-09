#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        int p = 0;
        int q = 0;
        vector<int> result;
        while (p < m && q < n) {
            if (nums1[p] > nums2[q]) {
                result.push_back(nums2[q++]);
            } else {
                result.push_back(nums1[p++]);
            }
        }
        while (p < m) {
            result.push_back(nums1[p++]);
        }
        while (q < n) {
            result.push_back(nums2[q++]);
        }
        nums1.resize(m + n);
        for (int i = 0; i < m + n; i++) {
            nums1[i] = result[i];
        }
        return;
    }
};
int main() {
    vector<int> test0 = {1, 2, 2, 5};
    vector<int> test1 = {2, 4, 4, 8};
    Solution solve;
    solve.merge(test0, test0.size(), test1, test1.size());
    for (int i = 0; i < test0.size() + test1.size(); i++) {
        printf("%d ", test0[i]);
    }
    return 0;
}