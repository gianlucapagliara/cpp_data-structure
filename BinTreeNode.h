/*
 * BinTreeNode.h
 *
 *      Author: Gianluca Pagliara
 */

#ifndef SRC_BINTREENODE_H_
#define SRC_BINTREENODE_H_

#include <cstddef>

template <class T>
class BinTreeNode {
public:
	typedef T typevalue;

	BinTreeNode();
	BinTreeNode(typevalue);
	BinTreeNode(typevalue, BinTreeNode<T>*, BinTreeNode<T>*, BinTreeNode<T>*);
	~BinTreeNode() {};

	void setValue(typevalue);
	void setLeft(BinTreeNode<T>*);
	void setRight(BinTreeNode<T>*);
	void setParent(BinTreeNode<T>*);

	typevalue getValue() const;
	BinTreeNode<T>* getLeft() const;
	BinTreeNode<T>* getRight() const;
	BinTreeNode<T>* getParent() const;

	bool operator ==(BinTreeNode<T>);
	bool operator <=(BinTreeNode<T>);
private:
	typevalue _value;
	BinTreeNode<T>* _left;
	BinTreeNode<T>* _right;
	BinTreeNode<T>* _parent;
};

template <class T>
BinTreeNode<T>::BinTreeNode(): _left(NULL), _right(NULL), _parent(NULL) {}

template <class T>
BinTreeNode<T>::BinTreeNode(typevalue value): _value(value), _left(NULL), _right(NULL), _parent(NULL) {}

template <class T>
BinTreeNode<T>::BinTreeNode(typevalue value, BinTreeNode<T>* left, BinTreeNode<T>* right, BinTreeNode<T>* parent): _value(value), _left(left), _right(right), _parent(parent) {}


template <class T>
void BinTreeNode<T>::setValue(typevalue value) {
	_value = value;
}

template <class T>
void BinTreeNode<T>::setLeft(BinTreeNode<T>* left) {
	_left = left;
}

template <class T>
void BinTreeNode<T>::setRight(BinTreeNode<T>* right) {
	_right = right;
}

template <class T>
void BinTreeNode<T>::setParent(BinTreeNode<T>* parent) {
	_parent = parent;
}

template <class T>
typename BinTreeNode<T>::typevalue BinTreeNode<T>::getValue() const {
	return _value;
}

template <class T>
BinTreeNode<T>* BinTreeNode<T>::getLeft() const {
	return _left;
}

template <class T>
BinTreeNode<T>* BinTreeNode<T>::getRight() const {
	return _right;
}

template <class T>
BinTreeNode<T>* BinTreeNode<T>::getParent() const {
	return _parent;
}

template <class T>
bool BinTreeNode<T>::operator ==(BinTreeNode<T> n) {
	return _value == n.getValue();
}

template <class T>
bool BinTreeNode<T>::operator <=(BinTreeNode<T> n) {
	return _value <= n.getValue();
}


#endif /* SRC_BINTREENODE_H_ */
