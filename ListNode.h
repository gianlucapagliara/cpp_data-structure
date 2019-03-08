/*
 * Node.h
 *
 *      Author: Gianluca Pagliara
 */
#include <cstddef>

#ifndef SRC_NODE_H_
#define SRC_NODE_H_


// Node class
template <class T>
class ListNode {
public:
    ListNode(): _pNext(NULL), _pPrev(NULL) {};
    ListNode(T data): _data(data), _pNext(NULL), _pPrev(NULL){};
    ListNode(T data, ListNode* prev, ListNode* next): _data(data), _pNext(prev), _pPrev(next){};
    ~ListNode() {} ;

    void setData(T data) { _data = data; };
    void setNext(ListNode<T>* next) { _pNext = next; };
    void setPrev(ListNode<T>* prev) { _pPrev = prev; };

    T getData() { return _data; };
    ListNode* getNext() { return _pNext; };
    ListNode* getPrev() { return _pPrev; };

private:
	T _data;
    ListNode* _pNext;
    ListNode* _pPrev;
};


#endif /* SRC_NODE_H_ */
