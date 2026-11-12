#include <cctype>
#include <iostream>
#include <queue>
#include <stack>
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

    string preLeftString = preString.substr(1, leftCounts); // 跳过根节点，取出左子树的前序序列
    string inLeftString = inString.substr(0, leftCounts);
    string preRightString = preString.substr(leftCounts + 1);
    string inRightString = inString.substr(leftCounts + 1);

    root->left = getBiTreeFromPreAndIn(preLeftString, inLeftString);
    root->right = getBiTreeFromPreAndIn(preRightString, inRightString);

    return root;
}

// 判断字符是否为加、减、乘、除运算符，返回判断结果
bool isOperator(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

// 释放 root 指向的整棵树
void destroyBiTree(BiTreeNode *root) {
    if (root == nullptr) {
        return;
    }
    destroyBiTree(root->left);
    destroyBiTree(root->right);
    delete root;
}

// 输出 root 的完全括号化中缀表达式，叶子直接输出
void printExpression(const BiTreeNode *root) {
    if (root == nullptr) {
        return;
    }
    if (root->left == nullptr && root->right == nullptr) {
        cout << root->value;
        return;
    }
    cout << '(';
    printExpression(root->left);
    cout << root->value;
    printExpression(root->right);
    cout << ')';
}

// 从前缀表达式 text 建树，返回根指针
BiTreeNode *getBiTreeFromPre(const string &text) {
    stack<BiTreeNode *> nodes;
    // 从右往左读，遇到运算符时，左右子树已经在栈中
    for (size_t pos = text.size(); pos > 0; pos = pos - 1) {
        char ch = text[pos - 1];
        if (isspace(ch)) {
            continue;
        }
        BiTreeNode *node = new BiTreeNode(ch);
        if (isOperator(ch)) {
            // 前缀倒着处理时，先出栈的是左子树
            node->left = nodes.top();
            nodes.pop();
            node->right = nodes.top();
            nodes.pop();
        }
        nodes.push(node);
    }
    return nodes.top();
}

// 从后缀表达式 text 建树，返回根指针
BiTreeNode *getBiTreeFromPost(const string &text) {
    stack<BiTreeNode *> nodes;
    // 从左往右读，遇到运算符时，将栈顶的两棵树合成一棵树
    for (size_t pos = 0; pos < text.size(); pos = pos + 1) {
        char ch = text[pos];
        if (isspace(ch)) {
            continue;
        }
        BiTreeNode *node = new BiTreeNode(ch);
        if (isOperator(ch)) {
            // 后缀顺着处理时，先出栈的是右子树
            node->right = nodes.top();
            nodes.pop();
            node->left = nodes.top();
            nodes.pop();
        }
        nodes.push(node);
    }
    return nodes.top();
}

// 返回运算符 symbol 的优先级，乘除高于加减，括号返回 0
int getPriority(char symbol) {
    if (symbol == '*' || symbol == '/') {
        return 2;
    }
    if (symbol == '+' || symbol == '-') {
        return 1;
    }
    return 0;
}

// 从中缀表达式 text 建树，返回根指针
// 先根据括号和优先级转成后缀，再复用后缀建树函数
BiTreeNode *getBiTreeFromIn(const string &text) {
    stack<char> ops;
    string post;
    for (size_t pos = 0; pos < text.size(); pos = pos + 1) {
        char ch = text[pos];
        if (isspace(ch)) {
            continue;
        }
        if (ch == '(') {
            ops.push(ch);
        } else if (ch == ')') {
            // 输出括号里的运算符，再丢弃左括号
            while (ops.top() != '(') {
                post.push_back(ops.top());
                ops.pop();
            }
            ops.pop();
        } else if (isOperator(ch)) {
            // 优先输出更高或相同优先级的运算符，保证同级运算从左向右
            while (!ops.empty()) {
                char top = ops.top();
                if (top == '(') {
                    break;
                }
                if (getPriority(top) < getPriority(ch)) {
                    break;
                }
                post.push_back(top);
                ops.pop();
            }
            ops.push(ch);
        } else {
            post.push_back(ch);
        }
    }
    // 所有操作数读完后，输出栈中剩余的运算符
    while (!ops.empty()) {
        post.push_back(ops.top());
        ops.pop();
    }
    return getBiTreeFromPost(post);
}

// 按 symbol 对 leftValue 和 rightValue 做一次整数运算，返回结果
int easyCalculator(int leftValue, int rightValue, char symbol) {
    if (symbol == '+') {
        return leftValue + rightValue;
    }
    if (symbol == '-') {
        return leftValue - rightValue;
    }
    if (symbol == '*') {
        return leftValue * rightValue;
    }
    return leftValue / rightValue;
}

// 计算 root 表达式树的整数值，返回结果
int calculateTree(const BiTreeNode *root) {
    if (root->left == nullptr && root->right == nullptr) {
        // 将叶子中的数字字符转成整数，例如 '3' 转成 3
        return root->value - '0';
    }

    // 先算左右子表达式，再用当前节点的运算符计算结果
    int leftValue = calculateTree(root->left);
    int rightValue = calculateTree(root->right);
    return easyCalculator(leftValue, rightValue, root->value);
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
