#include <climits>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace myStack {

class CharStack {
  private:
    // 每个栈内元素是一个节点
    struct Node {
        char value;
        Node *next;
        Node(char character) {
            value = character;
            next = nullptr;
        }
    };

    Node *topNode;
    int stackSize;

  public:
    CharStack() {
        topNode = nullptr;
        stackSize = 0;
    }
    ~CharStack() { clear(); }

    void charPush(char character) {
        Node *newNode = new Node(character);
        newNode->next = topNode;
        topNode = newNode;
        ++stackSize;
    }

    char charPop() {
        if (topNode == nullptr) {
            stackSize = 0;
            return '\0';
        }
        char tem = topNode->value;
        Node *toDelete = topNode;
        topNode = topNode->next;
        delete toDelete;
        --stackSize;
        return tem;
    }

    int getSize() const { return stackSize; }

    bool isEmpty() const { return this->stackSize == 0; }

    void clear() {
        while (topNode != nullptr) {
            Node *removedNode = topNode;
            topNode = topNode->next;
            delete removedNode;
        }
        stackSize = 0;
    }
};

class IntStack {
  private:
    struct Node {
        int element;
        Node *next;
    };
    Node *topNode;
    int stackSize;

  public:
    IntStack() : topNode(nullptr), stackSize(0) {};
    ~IntStack() { clear(); }
    void intPush(int number) {
        Node *newNode = new Node;
        newNode->element = number;
        newNode->next = topNode;
        topNode = newNode;
        ++stackSize;
    }
    int intPop() {
        if (topNode == nullptr) {
            stackSize = 0;
            return INT_MIN;
        }
        int tem = topNode->element;
        Node *toDelete = topNode;
        topNode = topNode->next;
        delete toDelete;
        --stackSize;
        return tem;
    }

    void clear() {
        while (topNode != nullptr) {
            Node *toDelete = topNode;
            topNode = topNode->next;
            delete toDelete;
        }
        stackSize = 0;
    }
};
} // namespace myStack

using namespace myStack;

int easyCalculate(int x, int y, char ch) {
    if (ch == '+') {
        return x + y;
    } else if (ch == '-') {
        return y - x;
    } else if (ch == '*') {
        return x * y;
    } else {
        return y / x;
    }
}

int main() {
    CharStack *charStack = new CharStack;
    IntStack *intStack = new IntStack;
    cout << "input" << endl;
    string receive;
    cin >> receive;

    for (int i = 0; i < receive.size(); i++) {
        if (receive[i] == '(') {
            charStack->charPush(receive[i]);
            continue;
        }

        if (receive[i] >= '0' && receive[i] <= '9') {
            intStack->intPush(receive[i] - '0');
            char cur = charStack->charPop();
            if (cur == '*' || cur == '/') {
                int x = intStack->intPop();
                int y = intStack->intPop();
                intStack->intPush(easyCalculate(x, y, cur));
            } else if (cur != '\0') {
                charStack->charPush(cur);
            } else { // 若 cur == '\0'，则什么也不做
            }
            continue;
        }

        if (receive[i] == '+' || receive[i] == '-') {
            char cur = charStack->charPop(); // cur 可能是 '+'、'-'、'\0'、'('
            if (cur == '(') {                // 还回左括号
                charStack->charPush(cur);
            }
            if (cur == '+' || cur == '-') {
                int x = intStack->intPop();
                int y = intStack->intPop();
                intStack->intPush(easyCalculate(x, y, cur));
                charStack->charPush(receive[i]);
                continue;
            }
            charStack->charPush(receive[i]);
            continue;
        }

        if (receive[i] == '*' || receive[i] == '/') {
            charStack->charPush(receive[i]);
            continue;
        }

        if (receive[i] == ')') {
            while (1) {
                char cur = charStack->charPop();
                if (cur == '(') {
                    break;
                }
                int x = intStack->intPop();
                int y = intStack->intPop();
                intStack->intPush(easyCalculate(x, y, cur));
            }

            // 注意：如果没有下面这段代码，那么 8/(1*2)*4 会直接执行成 8/8 = 1！因此还要继续往前检查上一个运算符
            char cur = charStack->charPop();
            if (cur == '*' || cur == '/') {
                int x = intStack->intPop();
                int y = intStack->intPop();
                intStack->intPush(easyCalculate(x, y, cur));
                continue;
            } else if (cur != '\0') {
                charStack->charPush(cur);
            } else {
            }
        }
    }

    while (!charStack->isEmpty()) {
        int x = intStack->intPop();
        int y = intStack->intPop();
        intStack->intPush(easyCalculate(x, y, charStack->charPop()));
    }

    cout << "output" << endl << "=" << intStack->intPop() << endl << "end";
    delete charStack;
    delete intStack;

    return 0;
}