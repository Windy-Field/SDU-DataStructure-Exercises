#include <iostream>
#include <vector>
using namespace std;
// #define cout std::cout

void swap(vector<int> &numbers, int i, int j) {
    int tem = numbers[i];
    numbers[i] = numbers[j];
    numbers[j] = tem;
}

void print(vector<int> &numbers, int numCounts) {
    bool isFirst = true;
    for (int i = 0; i < numCounts; i++) {
        if (isFirst) {
            cout << numbers[i];
            isFirst = false;
            continue;
        }
        cout << "," << numbers[i];
    }
    cout << "\n";
}

int maxIndex(vector<int> &numbers, int numCounts) {
    int max_index = 0, curMax = numbers[max_index];
    for (int i = 0; i < numCounts; i++) {
        if (numbers[i] > curMax) {
            curMax = numbers[i];
            max_index = i;
        }
    }
    return max_index;
}

void radixSort(vector<int> &numbers, int numCounts) {
    cout << "radix sort\n";
    // 先计算最大位数
    int times = 0;
    int cpy = numbers[maxIndex(numbers, numCounts)];
    while (cpy > 0) {
        cpy /= 10;
        ++times;
    }

    long long exp = 1; // 对应当下排序的位
    for (int i = 0; i < times; i++) {
        vector<vector<int>> buckets(10, vector<int>(0));
        vector<int> bucketsLength(10, 0);
        for (int x : numbers) {
            buckets[(x / exp) % 10].push_back(x); // 入桶
            ++bucketsLength[(x / exp) % 10];
        }

        int index = 0;
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < bucketsLength[j]; k++) {
                numbers[index++] = buckets[j][k]; // 出桶
            }
        }

        exp *= 10; // 换下一位
    }

    print(numbers, numCounts);
}

int main() {
    cout << "input\n";
    int count = 0;
    vector<int> numbers(0);
    while (count < 18) {
        int number;
        cin >> number;

        // 以下是本题附加要求：当任意输入不小于 10 时直接输出 0，不进行基数排序
        if (number >= 10) {
            cout << "output\n";
            cout << "radix sort\n";
            cout << "0\n";
            cout << "end\n";
            return 0;
        }

        if (number == 0) {
            break;
        }
        numbers.push_back(number);
        ++count;
    }

    cout << "output\n";
    radixSort(numbers, count);
    cout << "end\n";

    return 0;
}