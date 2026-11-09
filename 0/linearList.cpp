#include <iostream>

// 9.24 作业（在注释的array代码后面）
template <class T> struct chainNode {
    T element;
    chainNode<T> *next;

    chainNode() : element(), next(nullptr) {}

    chainNode(const T &value, chainNode<T> *link = nullptr) : element(value), next(link) {}
};

template <class T> class linearList {
  public:
    virtual ~linearList() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &get(int theIndex) const = 0;
    virtual int indexOf(const T &theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T &theElement) = 0;
    virtual void output(std::ostream &out) const = 0;
};

// 以下是上周作业，本周作业在下面
// template <class T> class arrayList : public linearList<T> {
//   protected:
//     void checkIndex(int theIndex) const; // 检查索引是否有效
//     T *element;
//     int arrayLength; // 一维数组容量
//     int listSize;    // 线性表的元素个数

//   public:
//     arrayList(int initialCapacity = 10);
//     arrayList(const arrayList<T> &) = default;
//     ~arrayList() { delete[] element; }

//     // ADT 方法
//     bool empty() const { return listSize == 0; }
//     int size() const { return listSize; }
//     T &get(int theIndex) const;
//     int indexOf(const T &theElement) const;
//     void erase(int theIndex);
//     void insert(int theIndex, const T &theElement);
//     void output(std::ostream &out) const;

//     // 其它方法
//     int capacity() const { return arrayLength; }
//     void trimToSize(); // 把数组容量缩减为 max{1, listSize}
//     void push_back(const T &theElement);
//     void pop_back();
//     void swap(arrayList<T> &theList);
//     void merge(const arrayList<T> &a, const arrayList<T> &b);
//     void split(arrayList<T> &a, arrayList<T> &b) const;
// };

// // 5，时间复杂度为 O(listSize)
// template <class T> void arrayList<T>::trimToSize() {
//     int newLength = listSize;
//     if (newLength < 1) {
//         newLength = 1;
//     }
//     if (newLength == arrayLength) {
//         return;
//     }

//     T *newElement = new T[newLength];
//     for (int index = 0; index < listSize; index++) {
//         newElement[index] = element[index];
//     }
//     delete[] element;
//     element = newElement;
//     arrayLength = newLength;
// }

// // 11. 时间复杂度为 O(listSize)
// template <class T> void arrayList<T>::push_back(const T &theElement) {
//     if (listSize == arrayLength) {
//         int newLength = arrayLength * 2;
//         if (newLength < 1) {
//             newLength = 1;
//         }

//         T *newElement = new T[newLength];
//         for (int index = 0; index < listSize; index++) {
//             newElement[index] = element[index];
//         }
//         delete[] element;
//         element = newElement;
//         arrayLength = newLength;
//     }
//     element[listSize] = theElement;
//     listSize++;
// }

// // 12. 时间复杂度为 O(1)
// template <class T> void arrayList<T>::pop_back() {
//     if (listSize == 0) {
//         return;
//     }
//     element[--listSize] = T();
// }

// // 13. 时间复杂度为 O(1)
// template <class T> void arrayList<T>::swap(arrayList<T> &theList) {
//     if (this == &theList) {
//         return;
//     }

//     T *tempElement = element;
//     element = theList.element;
//     theList.element = tempElement;

//     int temp = arrayLength;
//     arrayLength = theList.arrayLength;
//     theList.arrayLength = temp;

//     int tempSize = listSize;
//     listSize = theList.listSize;
//     theList.listSize = tempSize;
// }

// // 29. 时间复杂度：O(a.listSize + b.listSize)
// template <class T> void arrayList<T>::merge(const arrayList<T> &a, const arrayList<T> &b) {
//     int newSize = a.listSize + b.listSize;
//     int newLength = newSize;
//     if (newLength < 1) {
//         newLength = 1;
//     }
//     T *newElement = new T[newLength];

//     int indexA = 0;
//     int indexB = 0;
//     for (int indexNew = 0; indexNew < newSize; indexNew++) {
//         bool aFinished = indexA == a.listSize;
//         bool bFinished = indexB == b.listSize;
//         bool takeFromA = bFinished;
//         if (!aFinished && !bFinished) {
//             takeFromA = !(b.element[indexB] < a.element[indexA]);
//         }
//         if (takeFromA) {
//             newElement[indexNew] = a.element[indexA];
//             indexA++;
//         } else {
//             newElement[indexNew] = b.element[indexB];
//             indexB++;
//         }
//     }

//     delete[] element;
//     element = newElement;
//     arrayLength = newLength;
//     listSize = newSize;
// }

// // 30. 时间复杂度：O(listSize)
// template <class T> void arrayList<T>::split(arrayList<T> &a, arrayList<T> &b) const {
//     int evenSize = (listSize + 1) / 2;
//     int oddSize = listSize / 2;
//     int evenLength = evenSize;
//     if (evenLength < 1) {
//         evenLength = 1;
//     }
//     int oddLength = oddSize;
//     if (oddLength < 1) {
//         oddLength = 1;
//     }
//     T *evenElement = new T[evenLength];
//     T *oddElement = new T[oddLength];

//     for (int index = 0; index < listSize; index++) {
//         if (index % 2 == 0) {
//             evenElement[index / 2] = element[index];
//         } else {
//             oddElement[index / 2] = element[index];
//         }
//     }

//     delete[] a.element;
//     a.element = evenElement;
//     a.arrayLength = evenLength;
//     a.listSize = evenSize;

//     delete[] b.element;
//     b.element = oddElement;
//     b.arrayLength = oddLength;
//     b.listSize = oddSize;
// }

template <class T> class chain : public linearList<T> {
  public:
    chain();
    chain(const chain<T> &);
    ~chain();
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int index) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T &theElement);
    void output(std::ostream &out) const;
    void split(chain<T> &a, chain<T> &b) const;

  protected:
    chainNode<T> *firstNode;
    int listSize;
};

// 时间复杂度：O(n)
template <class T> void chain<T>::split(chain<T> &a, chain<T> &b) const {
    while (!a.empty()) {
        a.erase(0);
    }
    while (!b.empty()) {
        b.erase(0);
    }

    chainNode<T> *node = firstNode;
    int index = 0;
    while (node != nullptr) {
        if (index % 2 == 1) {
            a.insert(a.size(), node->element);
        } else {
            b.insert(b.size(), node->element);
        }
        node = node->next;
        index++;
    }
}

template <class T> class extendedChain : public chain<T> {
  public:
    virtual ~extendedChain() = default;
    virtual void clear() = 0;                        // 清表
    virtual void push_back(const T &theElement) = 0; // 插到表尾
    void circularShift(int i);
};

template <class T> void extendedChain<T>::clear() {
    while (this->firstNode != NULL) {
        chainNode<T> *nextNode = this->firstNode->next;
        delete this->firstNode;
        this->firstNode = nextNode;
    }
    this->listSize = 0;
}

template <class T> void extendedChain<T>::circularShift(int i) {
    if (this->listSize == 0) {
        return;
    }
    i %= this->listSize;
    if (i == 0) {
        return;
    }

    chainNode<T> *tail = this->firstNode;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    chainNode<T> *node = this->firstNode;
    for (int index = 1; index < this->listSize - i; index++) {
        node = node->next;
    }

    tail->next = this->firstNode;
    this->firstNode = node->next;
    node->next = nullptr;
}

template <class T> class circularList : public linearList<T> {
  public:
    circularList();
    circularList(const circularList<T> &list);
    ~circularList();
    circularList<T> &operator=(const circularList<T> &list);
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int index) const;
    int indexOf(const T &value) const;
    void erase(int index);
    void insert(int index, const T &value);
    void output(std::ostream &out) const;
    void clear();
    void push_back(const T &value);
    void split(circularList<T> &a, circularList<T> &b) const;
    void circularShift(int i);
    void reverse();

    template <class U> friend void meld(circularList<U> &a, circularList<U> &b, circularList<U> &c);
    template <class U> friend void merge(circularList<U> &a, circularList<U> &b, circularList<U> &c);

  protected:
    chainNode<T> *headerNode;
    chainNode<T> *lastNode;
    int listSize;
};

template <class T> circularList<T>::circularList() {
    headerNode = new chainNode<T>();
    headerNode->next = headerNode;
    lastNode = headerNode;
    listSize = 0;
}

template <class T> circularList<T>::circularList(const circularList<T> &list) : circularList() {
    chainNode<T> *node = list.headerNode->next;
    while (node != list.headerNode) {
        push_back(node->element);
        node = node->next;
    }
}

template <class T> circularList<T>::~circularList() {
    clear();
    delete headerNode;
}

template <class T> circularList<T> &circularList<T>::operator=(const circularList<T> &list) {
    circularList<T> copy(list);
    chainNode<T> *header = headerNode;
    chainNode<T> *last = lastNode;
    int count = listSize;

    headerNode = copy.headerNode;
    lastNode = copy.lastNode;
    listSize = copy.listSize;
    copy.headerNode = header;
    copy.lastNode = last;
    copy.listSize = count;
    return *this;
}

template <class T> T &circularList<T>::get(int index) const {
    chainNode<T> *node = headerNode->next;
    for (int position = 0; position < index; position++) {
        node = node->next;
    }
    return node->element;
}

template <class T> int circularList<T>::indexOf(const T &value) const {
    chainNode<T> *node = headerNode->next;
    for (int index = 0; index < listSize; index++) {
        if (node->element == value) {
            return index;
        }
        node = node->next;
    }
    return -1;
}

template <class T> void circularList<T>::erase(int index) {
    chainNode<T> *previous = headerNode;
    for (int position = 0; position < index; position++) {
        previous = previous->next;
    }
    chainNode<T> *node = previous->next;
    previous->next = node->next;
    if (node == lastNode) {
        lastNode = previous;
    }
    listSize--;
    delete node;
}

template <class T> void circularList<T>::insert(int index, const T &value) {
    chainNode<T> *previous = headerNode;
    for (int position = 0; position < index; position++) {
        previous = previous->next;
    }
    chainNode<T> *node = new chainNode<T>(value, previous->next);
    previous->next = node;
    if (previous == lastNode) {
        lastNode = node;
    }
    listSize++;
}

template <class T> void circularList<T>::output(std::ostream &out) const {
    chainNode<T> *node = headerNode->next;
    for (int index = 0; index < listSize; index++) {
        if (index > 0) {
            out << ' ';
        }
        out << node->element;
        node = node->next;
    }
}

template <class T> void circularList<T>::clear() {
    while (headerNode->next != headerNode) {
        chainNode<T> *node = headerNode->next;
        headerNode->next = node->next;
        delete node;
    }
    lastNode = headerNode;
    listSize = 0;
}

template <class T> void circularList<T>::push_back(const T &value) {
    chainNode<T> *node = new chainNode<T>(value, headerNode);
    lastNode->next = node;
    lastNode = node;
    listSize++;
}

template <class T> void circularList<T>::split(circularList<T> &a, circularList<T> &b) const {
    a.clear();
    b.clear();

    chainNode<T> *node = headerNode->next;
    for (int index = 0; index < listSize; index++) {
        if (index % 2 == 1) {
            a.push_back(node->element);
        } else {
            b.push_back(node->element);
        }
        node = node->next;
    }
}

template <class T> void circularList<T>::circularShift(int i) {
    if (listSize == 0) {
        return;
    }
    i %= listSize;
    if (i == 0) {
        return;
    }

    chainNode<T> *node = headerNode->next;
    for (int index = 1; index < listSize - i; index++) {
        node = node->next;
    }
    lastNode->next = headerNode->next;
    headerNode->next = node->next;
    node->next = headerNode;
    lastNode = node;
}

// 时间复杂度：O(n)
template <class T> void circularList<T>::reverse() {
    chainNode<T> *previous = headerNode;
    chainNode<T> *node = headerNode->next;
    lastNode = node;
    while (node != headerNode) {
        chainNode<T> *next = node->next;
        node->next = previous;
        previous = node;
        node = next;
    }
    headerNode->next = previous;
}

template <class T> void meld(circularList<T> &a, circularList<T> &b, circularList<T> &c) {
    c.clear();

    bool takeA = true;
    while (!a.empty() || !b.empty()) {
        circularList<T> *source;
        if (!a.empty() && (takeA || b.empty())) {
            source = &a;
        } else {
            source = &b;
        }
        chainNode<T> *node = source->headerNode->next;
        source->headerNode->next = node->next;
        source->listSize--;
        if (source->empty()) {
            source->lastNode = source->headerNode;
        }

        node->next = c.headerNode;
        c.lastNode->next = node;
        c.lastNode = node;
        c.listSize++;
        takeA = !takeA;
    }
}

template <class T> void merge(circularList<T> &a, circularList<T> &b, circularList<T> &c) {
    c.clear();

    while (!a.empty() || !b.empty()) {
        circularList<T> *source;
        if (a.empty()) {
            source = &b;
        } else if (b.empty()) {
            source = &a;
        } else if (b.headerNode->next->element < a.headerNode->next->element) {
            source = &b;
        } else {
            source = &a;
        }
        chainNode<T> *node = source->headerNode->next;
        source->headerNode->next = node->next;
        source->listSize--;
        if (source->empty()) {
            source->lastNode = source->headerNode;
        }

        node->next = c.headerNode;
        c.lastNode->next = node;
        c.lastNode = node;
        c.listSize++;
    }
}
