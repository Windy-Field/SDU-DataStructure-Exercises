#include <cctype>
#include <stack>
#include <string>
using namespace std;

// 表达式树的节点：value 存操作数或运算符，left、right 指向左右孩子
struct BiTreeNode {
    char value;
    BiTreeNode *left;
    BiTreeNode *right;

    // 用 symbol 建立一个没有孩子的节点
    BiTreeNode(char symbol) {
        value = symbol;
        left = nullptr;
        right = nullptr;
    }
};

// 判断 symbol 是否为加、减、乘、除运算符，返回判断结果
bool isOperator(char symbol) { return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/'; }

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

// 返回 symbol 的运算优先级：乘除为 2，加减为 1，其他字符为 0
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
            // 先输出括号里的运算符，再丢弃左括号
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
