#include <iostream>
#include <vector>
using namespace std;

int findRoot(int *parent, int number) {
    while (number != parent[number]) {
        number = parent[number];
    }
    return number;
}

void printBucket(vector<vector<int>> bucket, vector<int> length, int maxNumber) {
    for (int i = 1; i <= maxNumber; i++) {
        if (length[i] == 0) {
            continue;
        }
        bool isFirst = true;
        cout << "(";
        for (int j = 0; j < length[i]; j++) {
            if (bucket[i][j] == 0) {
                break;
            }
            if (isFirst) {
                cout << bucket[i][j];
                isFirst = false;
            } else {
                cout << "," << bucket[i][j];
            }
        }
        cout << ")" << endl;
    }
}

int main() {
    int maxNumber;
    int times;
    cout << "input" << endl;
    cin >> maxNumber >> times;

    int parent[maxNumber + 1];
    for (int i = 1; i <= maxNumber; i++) {
        parent[i] = i;
    }

    while (times--) {
        int a, b;
        char rubbish;
        cin >> rubbish >> a >> rubbish >> b >> rubbish; // (a,b)
        int rootA = findRoot(parent, a), rootB = findRoot(parent, b);
        rootA > rootB ? parent[rootA] = rootB : parent[rootB] = rootA; // 注意：这里要改的是 parent[root]
    }

    vector<vector<int>> bucket(maxNumber + 1, vector<int>(maxNumber + 1, 0));
    vector<int> length(maxNumber + 1, 0); // 每个桶的长度
    for (int i = 1; i <= maxNumber; i++) {
        bucket[findRoot(parent, i)][length[findRoot(parent, i)]++] = i;
    }
    cout << "output" << endl;
    printBucket(bucket, length, maxNumber);
    cout << "end" << endl;

    return 0;
}