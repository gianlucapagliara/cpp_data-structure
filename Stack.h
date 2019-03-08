/*
 * Stack.h
 *
 *      Author: Gianluca Pagliara
 */

#include "LinkedList.h"

#ifndef SRC_STACK_H_
#define SRC_STACK_H_

template <class T>
class Stack {
public:

	//Constructors and destructor
	Stack() { _pList = new LinkedList<T>; };
	Stack(const Stack<T>& s) { _pList = new LinkedList<T>(*(s._pList));};
	~Stack() { _pList->~LinkedList(); delete _pList;};

	//Operators
	void create() { _pList->create(); };
	bool isEmpty() const { return _pList->isEmpty(); };
	void push(const T& data) { _pList->insert(data, _pList->begin()); };
	T pop() {
		T value = _pList->read(_pList->last());
		_pList->erase(_pList->begin());
		return value;
	};
	T peek() const { return _pList->read(_pList->begin()); }; //read element on head, without remove it
	void write(const T& data) { _pList->write(data, _pList->begin()); };
	int size() const { return _pList->_length; };
	void printStack() const { _pList->printList(); };

	//Operators overload
	Stack<T>& operator=(const Stack<T>& s) { *_pList = *(s._pList); return *this; };
	bool operator==(const Stack<T>& s) const { return *_pList == *(s._pList); };
	template <class U>
	friend std::ostream& operator <<(std::ostream& o, const Stack<U>& s) { o << *(s._pList); return o; };
private:
	LinkedList<T>* _pList;
};


#endif /* SRC_STACK_H_ */
