#include <bits/stdc++.h>
using namespace std;

// 队列接口，T 表示元素类型，具体操作由子类实现。
template <class T> class Queue {
  public:
    // 通过基类指针删除对象时，也能调用子类的析构函数。
    virtual ~Queue() {}

    // 返回队列是否为空。
    virtual bool empty() const = 0;

    // 返回队列中的元素个数。
    virtual int size() const = 0;

    // 返回队首元素的引用，调用前队列应非空。
    virtual T &front() = 0;

    // 返回队尾元素的引用，调用前队列应非空。
    virtual T &back() = 0;

    // 删除队首元素，调用前队列应非空。
    virtual void pop() = 0;

    // 将 element 加入队尾。
    virtual void push(const T &element) = 0;
};

// 用循环数组存储队列，通过最后一次操作区分队空和队满。
template <class T> class ArrayQueue : public Queue<T> {
  private:
    T *queue;
    int arrayLength;
    int queueFront; // 队首元素的位置
    int queueBack;  // 下一次入队的位置
    bool lastOp;    // true 表示 push，false 表示 pop

  public:
    ArrayQueue(int capacity = 10) {
        arrayLength = capacity;
        queue = new T[arrayLength];
        queueFront = 0;
        queueBack = 0;
        // 初始队列为空，按最后一次操作为 pop 处理
        lastOp = false;
    }

    // 释放队列使用的数组
    ~ArrayQueue() override { delete[] queue; }

    // 返回队列是否为空
    bool empty() const override { return queueFront == queueBack && lastOp == false; }

    // 返回队列中的元素个数
    int size() const override {
        if (queueFront == queueBack && lastOp == true) {
            return arrayLength;
        }
        return (queueBack - queueFront + arrayLength) % arrayLength;
    }

    // 返回队首元素的引用，调用前队列应非空
    T &front() override { return queue[queueFront]; }

    // 计算并返回队尾元素
    T &back() override {
        int last = (queueBack - 1 + arrayLength) % arrayLength;
        return queue[last];
    }

    // 删除队首元素
    void pop() override {
        queueFront = (queueFront + 1) % arrayLength;
        lastOp = false;
    }

    // 将 element 加入队尾，且数组满时将容量扩大一倍
    void push(const T &element) override {
        // 两个位置相等且最后一次操作为 push，说明数组已满
        if (queueFront == queueBack && lastOp == true) {
            int newLength = arrayLength * 2;
            T *newQueue = new T[newLength];

            // 按出队顺序复制，扩容后队首回到下标 0
            for (int index = 0; index < arrayLength; index++) {
                int position = (queueFront + index) % arrayLength;
                newQueue[index] = queue[position];
            }

            // 在释放旧数组前存入元素，允许传入队列中已有元素的引用
            newQueue[arrayLength] = element;
            delete[] queue;
            queue = newQueue;
            queueBack = arrayLength + 1;
            arrayLength = newLength;
            queueFront = 0;
            queueBack = queueBack % arrayLength;
        } else {
            queue[queueBack] = element;
            queueBack = (queueBack + 1) % arrayLength;
        }
        lastOp = true;
    }
};
