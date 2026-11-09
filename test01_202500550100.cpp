#include <algorithm>
#include <iostream>
using namespace std;

void solve(int numbers[], int firstIndex, int numberCount) {
    // 递归出口
    if (firstIndex == numberCount) {
        for (int index = 0; index < numberCount; index++) {
            if (index > 0) {
                cout << ",";
            }
            cout << numbers[index];
        }
        cout << endl;
        return;
    }

    for (int curIndex = firstIndex; curIndex < numberCount; curIndex++) {
        // swap(numbers[firstIndex], numbers[curIndex]); 第一次交换
        int tem = numbers[firstIndex];
        numbers[firstIndex] = numbers[curIndex];
        numbers[curIndex] = tem;

        solve(numbers, firstIndex + 1, numberCount);

        // swap(numbers[firstIndex], numbers[curIndex]); 第二次交换
        tem = numbers[firstIndex];
        numbers[firstIndex] = numbers[curIndex];
        numbers[curIndex] = tem;
    }
}

int main() {
    int numbers[20];
    int index = 0;
    int currentValue = 0;

    cout << "input" << endl;

    while (cin >> currentValue && currentValue != 0) {
        numbers[index++] = currentValue;
    }

    cout << "output" << endl;
    sort(numbers, numbers + index);
    solve(numbers, 0, index);
    cout << "end" << endl;

    return 0;
}
