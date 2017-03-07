#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

template<class T>
class DLLNode {
public:
    DLLNode() {
        next = prev = 0;
    }
    DLLNode(const T& el, DLLNode *n = 0, DLLNode *p = 0) {
        info = el; next = n; prev = p;
    }
    T info;
    DLLNode *next, *prev;
};

template<class T>
class DoublyLinkedList {
public:
    DoublyLinkedList() {
        head = tail = 0;
    }
    void addToDLLTail(const T&);
    T deleteFromDLLTail();
    ~DoublyLinkedList() {
        clear();
    }
    bool isEmpty() const {
        return head == 0;
    }
    void clear();
    void setToNull() {
        head = tail = 0;
    }
    void addInMiddle(const T&);
    void addToDLLHead(const T&);
    T deleteFromDLLHead();
    T& firstEl();
    T* find(const T&) const;
protected:
    DLLNode<T> *head, *tail;
    friend ostream& operator<<(ostream&, const DoublyLinkedList<T>&);
};

template<class T>
void DoublyLinkedList<T>::addToDLLHead(const T& el) {
    if (head != 0) {
        head = new DLLNode<T>(el,head,0);
        head->next->prev = head;
    }
    else head = tail = new DLLNode<T>(el);
}

template<class T>
void DoublyLinkedList<T>::addToDLLTail(const T& el) {
    if (tail != 0) {
        tail = new DLLNode<T>(el,0,tail);
        tail->prev->next = tail;
    }
    else head = tail = new DLLNode<T>(el);
}

template<class T>
T DoublyLinkedList<T>::deleteFromDLLHead() {
    T el = head->info;
    if (head == tail) { // if only one DLLNode on the list;
        delete head;
        head = tail = 0;
    }
    else {              // if more than one DLLNode in the list;
        head = head->next;
        delete head->prev;
        head->prev = 0;
    }
    return el;
}

template<class T>
T DoublyLinkedList<T>::deleteFromDLLTail() {
    T el = tail->info;
    if (head == tail) { // if only one DLLNode on the list;
        delete head;
        head = tail = 0;
    }
    else {              // if more than one DLLNode in the list;
        tail = tail->prev;
        delete tail->next;
        tail->next = 0;
    }
    return el;
}

template<class T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll) {
    for (DLLNode<T> *tmp = dll.head; tmp != 0; tmp = tmp->next)
        out << tmp->info << ' ';
    return out;
}

template<class T>
T* DoublyLinkedList<T>::find(const T& el) const {
    for (DLLNode<T> *tmp = head; tmp != 0 && !(tmp->info == el);  // overloaded ==
            tmp = tmp->next);
    if (tmp == 0)
        return 0;
    else return &tmp->info;
}

template<class T>
void DoublyLinkedList<T>::addInMiddle(const T& el) {
    if (head != 0) {
        if (head->next != 0) {
            int i = 1;
            for (DLLNode<T> *tmp = head; tmp->next != 0; i++, tmp = tmp->next);
            for (tmp = head, i = i/2; i; i--, tmp = tmp->next);
            tmp->prev = tmp->prev->next = new DLLNode<T>(el,tmp,tmp->prev);
        }
        else head->next = tail = new DLLNode<T>(el,0,head);
    }
    else head = tail = new DLLNode<T>(el);
}

template<class T>
T& DoublyLinkedList<T>::firstEl() {
    return head->info;
}

template<class T>
void DoublyLinkedList<T>::clear() {
    for (DLLNode<T> *tmp; head != 0; ) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

#endif
