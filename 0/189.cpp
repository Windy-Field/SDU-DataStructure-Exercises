// 轮转数组
// 三次反转
#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    void rotate(vector<int> &num, int k) {
        int len = num.size();
        k %= len;
        reverse(num.begin(), num.end());
        reverse(num.begin(), num.begin() + k);
        reverse(num.begin() + k, num.end());
        return;
    }
};

int main() {
    int a;
    cin >> a;
    Solution solve;
    vector<int> array = {1, 2, 3, 4, 5, 6, 7};
    solve.rotate(array, a);
    for (int i = 0; i < array.size(); i++) {
        printf("%d ", array[i]);
    }
}
