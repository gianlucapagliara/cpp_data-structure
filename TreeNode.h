/*
 * TreeNode.h
 *
 *      Author: Gianluca Pagliara
 */

#ifndef SRC_TREENODE_H_
#define SRC_TREENODE_H_

#include <cstddef>

template <class T>
class TreeNode {
public:
	typedef T typevalue;
	TreeNode();
	TreeNode(typevalue);
	TreeNode(typevalue, TreeNode<T>*, TreeNode<T>*, TreeNode<T>*);
	~TreeNode() {};

	void setValue(typevalue);
	void setFirstChild(TreeNode<T>*);
	void setSibling(TreeNode<T>*);
	void setParent(TreeNode<T>*);

	typevalue getValue() const;
	TreeNode<T>* getFirstChild() const;
	TreeNode<T>* getSibling() const;
	TreeNode<T>* getParent() const;

	bool operator ==(TreeNode<T>);
	bool operator <=(TreeNode<T>);
private:
	typevalue _value;
	TreeNode<T>* _firstChild;
	TreeNode<T>* _sibling;
	TreeNode<T>* _parent;
};

template <class T>
TreeNode<T>::TreeNode(): _firstChild(NULL), _sibling(NULL), _parent(NULL) {}

template <class T>
TreeNode<T>::TreeNode(typevalue value): _value(value), _firstChild(NULL), _sibling(NULL), _parent(NULL) {}

template <class T>
TreeNode<T>::TreeNode(typevalue value, TreeNode<T>* fchild, TreeNode<T>* sibling, TreeNode<T>* parent): _value(value), _firstChild(fchild), _sibling(sibling), _parent(parent) {}


template <class T>
void TreeNode<T>::setValue(typevalue value) {
	_value = value;
}

template <class T>
void TreeNode<T>::setFirstChild(TreeNode<T>* child) {
	_firstChild = child;
}

template <class T>
void TreeNode<T>::setSibling(TreeNode<T>* sibling) {
	_sibling = sibling;
}

template <class T>
void TreeNode<T>::setParent(TreeNode<T>* parent) {
	_parent = parent;
}

template <class T>
typename TreeNode<T>::typevalue TreeNode<T>::getValue() const {
	return _value;
}

template <class T>
TreeNode<T>* TreeNode<T>::getFirstChild() const {
	return _firstChild;
}

template <class T>
TreeNode<T>* TreeNode<T>::getSibling() const {
	return _sibling;
}

template <class T>
TreeNode<T>* TreeNode<T>::getParent() const {
	return _parent;
}

template <class T>
bool TreeNode<T>::operator ==(TreeNode<T> n) {
	return _value == n.getValue();
}

template <class T>
bool TreeNode<T>::operator <=(TreeNode<T> n) {
	return _value <= n.getValue();
}



#endif /* SRC_TREENODE_H_ */
