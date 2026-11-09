#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    vector<int> print(vector<int> &nums, int target) {
        vector<int> numbers(10, 0);
        for (int i = 0; i < 10; i++) {
            printf("%d", numbers[i]);
        }
        return numbers;
    }
};

int main() {
    Solution solve;
    vector<int> numbers = {0, 0, 0};
    solve.print(numbers, 1);
    return 0;
}