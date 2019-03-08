/*
 * LinkedList.h
 *
 *      Author: Gianluca Pagliara
 */
#include <cstddef>
#include <iostream>

#include "ListNode.h"

#ifndef SRC_LINKEDLIST_H_
#define SRC_LINKEDLIST_H_


// List class
template <class T>
class LinkedList {
public:
	// Types
    typedef ListNode<T>* position;
    typedef T valueType;

    //Constructors and destructor
    LinkedList();
    LinkedList(const LinkedList<T>&);
    ~LinkedList();

    //Operators
    void create();
    bool isEmpty() const;
    valueType read(position) const;
    void write(const valueType&, position);
    position begin() const;
    position last() const;
    bool isEnded(position) const;
    position next(position) const;
    position previous(position) const;
    void insert(const valueType&, position);
    void insertAfter(const valueType& value, position p);
    void erase(position);
    int size() const { return _length; };
    void printList() const;

    //Operators overload
    LinkedList<T>& operator=(const LinkedList<T>&); // the assignment operator
    bool operator==(const LinkedList<T> &) const; // tests two list for equality
    template <class U>
    friend std::ostream& operator <<(std::ostream&, const LinkedList<U>&);
private:
    ListNode<T>* _pIndex;
    int _length;
};



template<class T>
LinkedList<T>::LinkedList() {
	_pIndex = new ListNode<T>;
	_length = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	_pIndex = new ListNode<T>;
	_length = 0;

	if(!list.isEmpty()) {
		position p = list.begin();
		do {
			insertAfter(list.read(p), last());
			p = list.next(p);
		} while ( !list.isEnded(p) );
	}
}

template<class T>
LinkedList<T>::~LinkedList() {
	while (!isEmpty())
		erase(begin());
	delete _pIndex;

}

template<class T>
void LinkedList<T>::create() {
	if (!isEmpty()) {
		while (!isEmpty())
			erase(begin());
	}
	_pIndex = new ListNode<T>;
	_length = 0;
}


template<class T>
bool LinkedList<T>::isEmpty() const {
	return _length == 0;
}

template<class T>
typename LinkedList<T>::position LinkedList<T>::begin() const {
	if (!isEmpty())
		return _pIndex->getNext();
	else return NULL;
}

template<class T>
typename LinkedList<T>::position LinkedList<T>::last() const {
	if (!isEmpty())
		return _pIndex->getPrev();
	else return NULL;
}

template<class T>
typename LinkedList<T>::position LinkedList<T>::next(position p) const {
	if (p != last())
		return (p->getNext());
	else return NULL;
}

template<class T>
typename LinkedList<T>::position LinkedList<T>::previous(position p) const {
	if (p != begin())
		return (p->getPrev());
	else return NULL;
}

template<class T>
bool LinkedList<T>::isEnded(position p) const {
	return (p == NULL);
}

template<class T>
typename LinkedList<T>::valueType LinkedList<T>::read(position p) const {
	if (!isEnded(p))
		return (p->getData());
}

template<class T>
void LinkedList<T>::write(const valueType& value, position p) {
	if (!isEnded(p))
		p->setData(value);
}


template<class T>
void LinkedList<T>::insert(const valueType& value, position p) {
	position t = new ListNode<T> (value);

	if(isEmpty()) {
		_pIndex->setNext(t);
		_pIndex->setPrev(t);
	} else if (p == begin()) {
		t->setNext(p);
		p->setPrev(t);
		_pIndex->setNext(t);
	} else {
		t->setNext(p);
		t->setPrev(p->getPrev());
		p->getPrev()->setNext(t);
		p->setPrev(t);
	}

	_length++;
}

template<class T>
void LinkedList<T>::insertAfter(const valueType& value, position p) {
	position t = new ListNode<T> (value);

	if(isEmpty()) {
		_pIndex->setNext(t);
		_pIndex->setPrev(t);
	} else if (p == last()) {
		t->setPrev(p);
		p->setNext(t);
		_pIndex->setPrev(t);
	} else {
		t->setPrev(p);
		t->setNext(p->getNext());
		p->getNext()->setPrev(t);
		p->setNext(t);
	}

	_length++;
}

template<class T>
void LinkedList<T>::erase(position p) {
	if (!isEmpty() && !isEnded(p)) {
		if(p == begin()) {
			_pIndex->setNext(p->getNext());
		} else if(p == last()) {
			_pIndex->setPrev(p->getPrev());
		} else {
			p->getPrev()->setNext(p->getNext());
			p->getNext()->setPrev(p->getPrev());
		}
		delete p;
		_length--;
	}
}

template <class T>
void LinkedList<T>::printList() const {
	std::cout << *this;
}

template <class T>
std::ostream& operator<< (std::ostream& o, const LinkedList<T>& l){
	if (l.isEmpty())
		o << "(null)";
	else {
		typename LinkedList<T>::position p;
		p = l.begin();
		o << "(";
		do {
			o << l.read(p);
			p = l.next(p);
			if (p != NULL)
				o << ", ";
		}while (p != NULL);
		o << ")";
	}
	return o;
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list) {
	_pIndex = new ListNode<T>;
	_length = 0;

	if(this!= &list && !list.isEmpty()) {
		position p = list.begin();
		do {
			insertAfter(list.read(p), last());
			p = list.next(p);
		} while ( !list.isEnded(p) );
	}
	return *this;
}

template<class T>
bool LinkedList<T>::operator==(const LinkedList<T> &list) const {
	if (list.size() != _length)
		return false;
	position p, pList;
	p = begin();
	pList = list.begin();
	while (!isEnded(p)) {
		if (p->getData() != pList->getData())
			return false;
		p = p->getNext();
		pList = pList->getNext();
	}
	return true;
}


#endif /* SRC_LINKEDLIST_H_ */
