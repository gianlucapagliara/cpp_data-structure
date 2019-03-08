/*
 * Queue.h
 *
 *      Author: Gianluca Pagliara
 */

#include "LinkedList.h"

#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

template <class T>
class Queue {
public:

	//Constructors and destructor
	Queue() { _pList = new LinkedList<T>; };
	Queue(const Queue<T>& q) { _pList = new LinkedList<T>(*(q._pList)); };
	~Queue() { _pList->~LinkedList(); delete _pList; };

	//Operators
	void create() { _pList->create(); };
	bool isEmpty() const { return _pList->isEmpty(); };
	void enqueue(const T& data) { _pList->insert(data, _pList->begin()); };
	T dequeue() {
		T value = _pList->read(_pList->last());
		_pList->erase(_pList->last());
		return value;
	};
	T peek() const { return _pList->read(_pList->last()); }; //read last element, without remove it
	int size() const { return _pList->_length; };
	void printQueue() const { _pList->printList(); };

	//Operators overload
	Queue<T>& operator=(const Queue<T>& q) { *_pList = *(q._pList); return *this; };
	bool operator==(const Queue<T>& q) const { return *_pList == *(q._pList); };
	template <class U>
	friend std::ostream& operator <<(std::ostream& o, const Queue<U>& q) { o << *(q._pList); return o; };

private:
	LinkedList<T>* _pList;
};


#endif /* SRC_QUEUE_H_ */
