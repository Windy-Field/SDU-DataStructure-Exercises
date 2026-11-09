#include <iostream>
using namespace std;

class List {
  public:
    int number;
    List *next;
    List() = default;
    List(int number, List *ptr) : number(number), next(ptr) {}
    // ~List() { delete next; } // 这里千万不能写析构函数！
};

List *createSortedList(List *head) {  // 一般传入的都是 nullptr
    List dummy = List(INT_MIN, head); // 这里不该用指针，应该用 List，这样才会自动释放，不造成内存泄露
    while (1) {
        int number;
        cin >> number;
        if (number == 0) {
            break;
        }
        List *p = new List(number, nullptr);
        List *read = &dummy;
        while (read->next != nullptr) { // 这里 read 永远不可能是 nullptr
            if (read->number <= p->number && read->next->number > p->number) {
                p->next = read->next;
                read->next = p;
                break;
            }
            read = read->next;
        }
        if (read->next == nullptr) {
            read->next = p;
        }
    }

    return dummy.next;
}

List *mergeList(List *head1, List *head2) {
    printf("mergence\n");

    List dummy = List(INT_MIN, nullptr);
    List *write = &dummy;
    List *read1 = head1, *read2 = head2;
    while (read1 != nullptr && read2 != nullptr) {
        if (read1->number < read2->number) {
            write->next = read1;
            read1 = read1->next;
        } else {
            write->next = read2;
            read2 = read2->next;
        }
        write = write->next;
    }
    if (read1 == nullptr) {
        write->next = read2;
    } else {
        write->next = read1;
    }
    return dummy.next;
}

List *insertList(List *head, int number) {
    printf("insert\n");
    printf("insertion\n");
    List dummy = List(INT_MIN, head);
    List *p = new List(number, nullptr);
    List *read = &dummy;
    while (read->next != nullptr) { // 这里 read 永远不可能是 nullptr
        if (read->number <= p->number && read->next->number > p->number) {
            p->next = read->next;
            read->next = p;
            break;
        }
        read = read->next;
    }
    if (read->next == nullptr) {
        read->next = p;
    }
    return dummy.next;
}

int findListPosition(List *head, int number) {
    List *read = head;
    int pos = 0;
    while (read != nullptr) {
        if (read->number == number) {
            return pos;
        }
        ++pos;
        read = read->next;
    }

    return -1;
}

List *deleteList(List *head, int pos) {
    printf("delete\n");
    printf("deletion\n");
    if (pos == -1) {
        return head;
    }
    List dummy = List(INT_MIN, head);
    List *find = &dummy;
    for (int i = 0; i < pos; i++) {
        find = find->next;
    }
    List *toDelete = find->next;
    find->next = find->next->next;
    delete toDelete;
    return dummy.next;
}

void printList(List *head) {
    List *p = head;
    if (p == nullptr) {
        printf("(nul)\n");
        return;
    }

    bool isFirst = true;
    while (p != nullptr) {
        if (isFirst) {
            printf("%d", p->number);
            isFirst = false;
        } else {
            printf(",%d", p->number);
        }
        p = p->next;
    }
    printf("\n");
}

int main() {
    cout << "input1" << endl;
    List *head1 = nullptr;
    head1 = createSortedList(head1);
    cout << "output1" << endl;
    printList(head1);

    cout << "input2" << endl;
    List *head2 = nullptr;
    head2 = createSortedList(head2);
    cout << "output2" << endl;
    printList(head2);

    List *head3 = mergeList(head1, head2);
    printList(head3);

    int insertNumber;
    cin >> insertNumber;
    head3 = insertList(head3, insertNumber); // 要记得更新 head3！
    printList(head3);

    int deleteNumber;
    cin >> deleteNumber;
    int pos = findListPosition(head3, deleteNumber);
    head3 = deleteList(head3, pos);
    printList(head3);

    printf("find\n");
    printf("position\n");
    int searchNumber;
    cin >> searchNumber;
    pos = findListPosition(head3, searchNumber);
    printf("%d\n", pos + 1);

    printf("end");
    return 0;
}