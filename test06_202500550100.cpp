#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct BiTreeNode {
  public:
    char value;
    BiTreeNode *left;
    BiTreeNode *right;
    BiTreeNode() = default;
    BiTreeNode(const char &ch) : value(ch), left(nullptr), right(nullptr) {};
};

typedef struct BiTreeNode BiTreeNode;

BiTreeNode *createBiTreeNode(const string &receive) {
    if (receive.size() == 0) {
        return nullptr;
    }

    queue<BiTreeNode *> nodes;
    int pos = 0;
    BiTreeNode *root;

    if (pos == 0) { // 首节点单独处理，先赋值并放到队列中
        BiTreeNode *newNode = new BiTreeNode(receive[pos] - 'A' + 'a');
        nodes.push(newNode);
        ++pos;
        root = newNode;
    }

    while (pos < receive.size()) {
        if (nodes.empty()) {
            break;
        }
        BiTreeNode *frontNode = nodes.front(); // 每次先取队首节点
        nodes.pop();

        BiTreeNode *newLeftNode = new BiTreeNode(receive[pos++] - 'A' + 'a'); // 每个队首元素必然左右节点都为空，先赋左节点
        frontNode->left = newLeftNode;
        nodes.push(newLeftNode);

        if (pos < receive.size()) { // 尝试赋右节点
            BiTreeNode *newRightNode = new BiTreeNode(receive[pos++] - 'A' + 'a');
            frontNode->right = newRightNode;
            nodes.push(newRightNode);
        }
    }
    return root;
}

int treeHeight(const BiTreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    if (leftHeight <= rightHeight) {
        return 1 + rightHeight;
    } else {
        return 1 + leftHeight;
    }
}

int nodeCounts(const BiTreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + nodeCounts(root->left) + nodeCounts(root->right);
}

int maxHeightDifference(const BiTreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int result = 0;
    if (result < treeHeight(root->left) - treeHeight(root->right)) {
        result = treeHeight(root->left) - treeHeight(root->right);
    }

    int leftResult = maxHeightDifference(root->left);
    int rightResult = maxHeightDifference(root->right);
    if (result < leftResult) {
        result = leftResult;
    }
    if (result < rightResult) {
        result = rightResult;
    }
    return result;
}

void printPreOrder(const BiTreeNode *root, bool &isFirst) {
    if (root == nullptr) {
        return;
    }

    if (isFirst) {
        cout << root->value;
        isFirst = false;
    } else {
        cout << "," << root->value;
    }
    printPreOrder(root->left, isFirst);
    printPreOrder(root->right, isFirst);
}

void printInOrder(const BiTreeNode *root, bool &isFirst) {
    if (root == nullptr) {
        return;
    }

    printInOrder(root->left, isFirst);
    if (isFirst) {
        cout << root->value;
        isFirst = false;
    } else {
        cout << "," << root->value;
    }
    printInOrder(root->right, isFirst);
}

void printPostOrder(const BiTreeNode *root, bool &isFirst) {
    if (root == nullptr) {
        return;
    }

    printPostOrder(root->left, isFirst);
    printPostOrder(root->right, isFirst);
    if (isFirst) {
        cout << root->value;
        isFirst = false;
    } else {
        cout << "," << root->value;
    }
}

void printLevelOrder(BiTreeNode *root) {
    queue<BiTreeNode *> queue;
    if (root == nullptr) {
        return;
    }
    queue.push(root);
    int pos = 1;
    while (!queue.empty()) {
        BiTreeNode *frontNode = queue.front();
        queue.pop();
        if (pos == 1) {
            cout << frontNode->value;
        } else {
            cout << "," << frontNode->value;
        }
        ++pos;
        if (frontNode->left != nullptr) {
            queue.push(frontNode->left);
        }
        if (frontNode->right != nullptr) {
            queue.push(frontNode->right);
        }
    }
}

BiTreeNode *getBiTreeFromPreAndIn(const string &preString, const string &inString) {
    if (preString.empty()) {
        return nullptr;
    }

    char rootValue = preString[0];
    BiTreeNode *root = new BiTreeNode(rootValue - 'A' + 'a');
    int leftCounts = inString.find(rootValue); // 以根元素位置作为左子树节点个数

    string preLeftString = preString.substr(1, leftCounts); // 注意：此处从第二个元素开始
    string inLeftString = inString.substr(0, leftCounts);
    string preRightString = preString.substr(leftCounts + 1);
    string inRightString = inString.substr(leftCounts + 1);

    root->left = getBiTreeFromPreAndIn(preLeftString, inLeftString);
    root->right = getBiTreeFromPreAndIn(preRightString, inRightString);

    return root;
}

int main() {
    cout << "input1" << endl;
    string receive;
    cin >> receive;

    cout << "output1" << endl;
    BiTreeNode *root = createBiTreeNode(receive);

    bool isPreFirst = true;
    printPreOrder(root, isPreFirst);
    cout << endl;
    bool isInFirst = true;
    printInOrder(root, isInFirst);
    cout << endl;
    bool isPostFirst = true;
    printPostOrder(root, isPostFirst);
    cout << endl;

    cout << nodeCounts(root) << endl;
    cout << treeHeight(root) << endl;

    delete root;

    cout << "input2" << endl;
    string receive1, receive2;
    cin >> receive1 >> receive2;

    cout << "output2" << endl;
    BiTreeNode *newRoot = getBiTreeFromPreAndIn(receive1, receive2);

    bool isPostFirst_ = true;
    printPostOrder(newRoot, isPostFirst_);
    cout << endl;
    printLevelOrder(newRoot);
    cout << endl;
    cout << "end";

    return 0;
}