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

void bubbleSort(vector<int> &numbers, int numCounts) {
    cout << "bubble sort\n";
    for (int i = 0; i < numCounts; i++) {
        for (int j = 0; j < numCounts - 1 - i; j++) {
            if (numbers[j] > numbers[j + 1]) {
                swap(numbers, j, j + 1);
            }
        }
    }
    print(numbers, numCounts);
}

void insertSort(vector<int> &numbers, int numCounts) {
    cout << "insert sort\n";
    for (int i = 1; i < numCounts; i++) {
        for (int j = i; j > 0; j--) {
            if (numbers[j - 1] > numbers[j]) {
                swap(numbers, j, j - 1);
            }
        }
    }
    print(numbers, numCounts);
}

void selectSort(vector<int> &numbers, int numCounts) {
    cout << "select sort\n";
    for (int i = numCounts - 1; i >= 0; i--) {
        swap(numbers, maxIndex(numbers, i + 1), i); // 注意：这里 maxIndex 调用的是 (i+1) 而非 i
    }
    print(numbers, numCounts);
}

int main() {
    cout << "input\n";
    cout << "1-bubble sort,2-insert sort,3-select sort\n";
    int count = 0;
    vector<int> numbers(0);
    while (count < 18) {
        int number;
        cin >> number;
        if (number == 0) {
            break;
        }
        numbers.push_back(number);
        ++count;
    }
    int mode;
    cin >> mode;

    cout << "output\n";
    switch (mode) {
    case 1:
        bubbleSort(numbers, count);
        break;
    case 2:
        insertSort(numbers, count);
        break;
    case 3:
        selectSort(numbers, count);
        break;
    }
    cout << "end\n";

    return 0;
}