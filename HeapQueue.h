/*
 * HeapQueue.h
 *
 *      Author: Gianluca Pagliara
 */

#ifndef HEAP_H
#define HEAP_H

template <class T>
class Item {
public:
	Item(T value, int priority, int pos) {
		this->_value = value;
		this->_priority = priority;
		this->_pos = pos;
	}

	int getPos() const { return _pos; };
	int getPriority() const { return _priority; };
	T getValue() const { return _value; };

	void setPos(int pos) { _pos = pos; };
	void setPriority(int priority) { _priority = priority; };
	void setValue(T value) { _value = value; };

private:
	T _value;
	int _priority;
	int _pos;
};

template <class T>
class HeapQueue {
public:
	// Constructors and destructors
	HeapQueue(int);
	~HeapQueue();

	//Operators
	int size() const;
	T min() const;

	Item<T>* insert(T, int);

	void minHeapRestore(int);
	void fixUp(int);

	void deleteMin();

	void decrease(Item<T>*, int);

private:
	void swap(int, int);

	int parent(int i) { return i / 2; };  // integer division
	int left(int i) { return 2 * i; };
	int right(int i) { return (2 * i) + 1;};

	int _used;
	int _max;
	Item<T>** _heap;
};

template <class T>
HeapQueue<T>::HeapQueue(int n) : _used(0), _max(n), _heap(0) {
	_heap = new Item<T>*[_max];
};

template <class T>
HeapQueue<T>::~HeapQueue(){
	for (int i=0; i<size(); i++) {
		deleteMin();
	}

	delete[] _heap;
}

template <class T>
int HeapQueue<T>::size() const {
	return _used;
}

template <class T>
T HeapQueue<T>::min() const {
	if (_used == 0) {
		return 0;
	}

	return _heap[0]->getValue();
}

template <class T>
Item<T>* HeapQueue<T>::insert(T value, int priority) {
	if (_used >= _max) {
		return 0;
	}

	Item<T>* new_item = new Item<T>(value, priority, _used);
	_heap[_used] = new_item;

	fixUp(_used);

	_used++;

	return new_item;
};

template <class T>
void HeapQueue<T>::fixUp(int i) {
	while (i > 0 && _heap[i]->getPriority() < _heap[parent(i)]->getPriority()) {
		swap(i, parent(i));
		i = parent(i);
	}
}

template <class T>
void HeapQueue<T>::minHeapRestore(int i) {
	int min = i;
	if (left(i) < _used && _heap[left(i)]->getPriority() < _heap[min]->getPriority()) {
		min = left(i);
	}

	if (right(i) < _used && _heap[right(i)]->getPriority() < _heap[min]->getPriority()) {
		min = right(i);
	}

	if (i != min) {
		swap(i, min);
		minHeapRestore(min);
	}
};

template <class T>
void HeapQueue<T>::deleteMin() {
	if (_used == 0) {
		return;
	}

	_used--;
	swap(0, _used);

	delete _heap[_used];  // deallocate item

	minHeapRestore(0);
}

template <class T>
void HeapQueue<T>::decrease(Item<T>* x, int p) {
	if (p > x->_priority) {
		return;
	}
	x->_priority = p;
	fixUp(x->_pos);
};

template <class T>
void HeapQueue<T>::swap(int i, int j) {
	Item<T>* tmp = _heap[i];
	_heap[i] = _heap[j];
	_heap[j] = tmp;
	_heap[i]->setPos(i);
	_heap[j]->setPos(j);
};

# endif
