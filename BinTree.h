/*
 * BinTree.h
 *
 *      Author: Gianluca Pagliara
 */

#ifndef SRC_BINTREE_H_
#define SRC_BINTREE_H_

#include "BinTreeNode.h"
#include "Queue.h"
#include <stdio.h>


template <class T>
class BinTree {
public:
	// Types
	typedef T typevalue;
	typedef BinTreeNode<T>* Node;

	//Constructors and destructor
	BinTree();
	~BinTree();

	// Operators
	void create();
	bool isEmpty() const;

	Node getRoot() const;
	Node getParent(Node) const;
	Node getLeftChild(Node) const;
	Node getRightChild(Node) const;

	void insertRoot(Node);
	void insertRoot(typevalue);
	void insertLeftChild(Node);
	void insertLeftChild(Node, Node);
	void insertLeftChild(Node, typevalue);
	void insertRightChild(Node);
	void insertRightChild(Node, Node);
	void insertRightChild(Node, typevalue);

	bool isLeftEmpty(Node) const;
	bool isRightEmpty(Node) const;
	bool isLeaf(Node) const;

	void copySubtree(const BinTree<T>&, Node, Node);
	void createBinTree(typevalue, const BinTree<T>&, const BinTree<T>&); // da testare
	void eraseSubtree(Node);

	typevalue readValue(Node) const;
	void writeValue(Node, typevalue);

	void print(Node) const; // stampa il sottoalbero a partire dal nodo
	int height (Node) const; // restituisce l'altezza del nodo
	int count (Node) const; // restituisce il numero di nodi nel sottoalbero a partire dal nodo

private:
	Node _root;

	// Visita
	void visitaPreordine(Node);
	void visitaPostordine(Node);
	void visitaSimmetrica(Node);
	void visitaAmpiezza(Node);
};

template <class T>
BinTree<T>::BinTree() {
	create();
}

template <class T>
BinTree<T>::~BinTree() {
	eraseSubtree(getRoot());
}

template <class T>
void BinTree<T>::create() {
	_root = NULL;
}

template <class T>
bool BinTree<T>::isEmpty() const {
	return _root == NULL;
}

template <class T>
typename BinTree<T>::Node BinTree<T>::getRoot() const {
	return _root;
}

template <class T>
typename BinTree<T>::Node BinTree<T>::getParent(Node n) const {
	Node p = NULL;
	if(!isEmpty() && n != _root) {
		p = n->getParent();
	}
	return p;
}

template <class T>
typename BinTree<T>::Node BinTree<T>::getLeftChild(Node n) const {
	return n->getLeft();
}

template <class T>
typename BinTree<T>::Node BinTree<T>::getRightChild(Node n) const {
	return n->getRight();
}

template <class T>
bool BinTree<T>::isLeftEmpty(Node n) const {
	return n->getLeft()==NULL;
}

template <class T>
bool BinTree<T>::isRightEmpty(Node n) const {
	return n->getRight()==NULL;
}

template <class T>
bool BinTree<T>::isLeaf(Node n) const {
	return isLeftEmpty(n) && isRightEmpty(n);
}

template <class T>
void BinTree<T>::insertRoot(Node root) {
	if (isEmpty()){
		_root=root;
		_root->setLeft(NULL);
		_root->setRight(NULL);
		_root->setParent(NULL);
	}
}

template <class T>
void BinTree<T>::insertRoot(typevalue value) {
	if (isEmpty()){
		Node root = new BinTreeNode<T>();
		_root=root;
		_root->setValue(value);
		_root->setLeft(NULL);
		_root->setRight(NULL);
		_root->setParent(NULL);
	}
}

template <class T>
void BinTree<T>::insertLeftChild(Node n) {
	if (isLeftEmpty(n)){
		Node left = new BinTreeNode<T>();
		n->setLeft(left);
		left->setLeft(NULL);
		left->setRight(NULL);
		left->setParent(n);
	}
}

template <class T>
void BinTree<T>::insertLeftChild(Node n, Node left) {
	if (isLeftEmpty(n)){
		n->setLeft(left);
		left->setLeft(NULL);
		left->setRight(NULL);
		left->setParent(n);
	}
}

template <class T>
void BinTree<T>::insertLeftChild(Node n, typevalue value) {
	if (isLeftEmpty(n)){
		insertLeftChild(n);
		getLeftChild(n)->setValue(value);
	}
}

template <class T>
void BinTree<T>::insertRightChild(Node n) {
	if (isRightEmpty(n)){
		Node right = new BinTreeNode<T>();
		n->setRight(right);
		right->setLeft(NULL);
		right->setRight(NULL);
		right->setParent(n);
	}
}

template <class T>
void BinTree<T>::insertRightChild(Node n, Node right) {
	if (isRightEmpty(n)){
		n->setRight(right);
		right->setLeft(NULL);
		right->setRight(NULL);
		right->setParent(n);
	}
}

template <class T>
void BinTree<T>::insertRightChild(Node n, typevalue value) {
	if (isRightEmpty(n)){
		insertRightChild(n);
		getRightChild(n)->setValue(value);
	}
}

template <class T>
typename BinTree<T>::typevalue BinTree<T>::readValue(Node n) const {
	typevalue value;
	if(n != NULL) {
		value = n->getValue();
	}
	return value;
}

template <class T>
void BinTree<T>::writeValue(Node n, typevalue value) {
	if(n != NULL) {
		n->setValue(value);
	}
}

template <class T>
void BinTree<T>::createBinTree(typevalue rootValue, const BinTree<T>& leftTree, const BinTree<T>& rightTree) {
	if(isEmpty()) {
		Node root = new BinTreeNode<T>();
		root->setValue(rootValue);
		if(!leftTree.isEmpty()) {
			Node left = new BinTreeNode<T>();
			copySubtree(leftTree, leftTree.getRoot(), left);
			root->setLeft(left);
			left->setParent(root);
		}
		if(!rightTree.isEmpty()) {
			Node right = new BinTreeNode<T>();
			copySubtree(rightTree, rightTree.getRoot(), right);
			root->setRight(right);
			right->setParent(root);
		}
		_root = root;
	}
}

template <class T>
void BinTree<T>::copySubtree(const BinTree<T>& t, Node c, Node n) {
	if(!t.isEmpty()) {
		writeValue(n, t.readValue(c));
		if(!t.isLeftEmpty(c)) {
			Node left = new BinTreeNode<T>();
			n->setLeft(left);
			left->setParent(n);
			copySubtree(t, t.getLeftChild(c), left);
		}
		if(!t.isRightEmpty(c)) {
			Node right = new BinTreeNode<T>();
			n->setRight(right);
			right->setParent(n);
			copySubtree(t, t.getRightChild(c), right);
		}
	}
}

template <class T>
void BinTree<T>::eraseSubtree(Node n){
	if (n != NULL) {
		if (!isLeftEmpty(n)) {
			eraseSubtree(getLeftChild(n));
		}
		if (!isRightEmpty(n)) {
			eraseSubtree(getRightChild(n));
		}
		if (n != getRoot()) {
			Node parent = getParent(n);
			if (getLeftChild(parent)==n){
				parent->setLeft(NULL);// if n is left child
			} else{
				parent->setRight(NULL);// if n is right child
			}
		} else {
			_root = NULL; // if n is root
		}
		delete n;
	}
}

template <class T>
void BinTree<T>::print(Node n) const {
	if(!isEmpty() && n != NULL) {
		std::cout << n->getValue() << " (";
		if(!isLeftEmpty(n)) {
			print(getLeftChild(n));
		}
		std::cout << ") (";
		if(!isRightEmpty(n)) {
			print(getRightChild(n));
		}
		std::cout << ")";
	} else {
		std::cout << "()";
	}
}

template <class T>
int BinTree<T>::height(Node n) const {
	int altezza = 0;
	if(!isEmpty() && n != NULL) {
		Node t = n;
		altezza++;
		while (t != _root) {
			t = getParent(t);
			altezza++;
		}
	}
	return altezza;
}

template <class T>
int BinTree<T>::count(Node n) const {
	int count = 0;
	if(!isEmpty() && n != NULL) {
		Node t = n;
		Queue<Node> q;
		q.create();
		q.enqueue(t);
		count++;
		while(!q.isEmpty()) {
			t = q.peek();
			q.dequeue();
			if(!isLeftEmpty(t)) {
				q.enqueue(getLeftChild(t));
				count++;
			}
			if(!isRightEmpty(t)) {
				q.enqueue(getRightChild(t));
				count++;
			}
		}
	}
	return count;
}

template <class T>
void BinTree<T>::visitaPreordine(Node n) {
	if(!isEmpty() && n != NULL) {
		//esamina n
		if(!isLeftEmpty(n))
			visitaPreordine(getLeftChild(n));
		if(!isRightEmpty(n))
			visitaPreordine(getRightChild(n));
	}
}

template <class T>
void BinTree<T>::visitaPostordine(Node n) {
	if(!isEmpty() && n != NULL) {
		if(!isLeftEmpty(n))
			visitaPostordine(getLeftChild(n));
		if(!isRightEmpty(n))
			visitaPostordine(getRightChild(n));
		//esamina n
	}
}

template <class T>
void BinTree<T>::visitaSimmetrica(Node n) {
	if(!isEmpty() && n != NULL) {
		if(!isLeftEmpty(n))
			visitaSimmetrica(getLeftChild(n));
		//esamina n
		if(!isRightEmpty(n))
			visitaSimmetrica(getRightChild(n));
	}
}

template <class T>
void BinTree<T>::visitaAmpiezza(Node n) {
	if(!isEmpty() && n != NULL) {
		Node t = n;
		typevalue a;
		Queue<Node> q;
		q.create();
		q.enqueue(t);
		while(!q.isEmpty()) {
			t = q.peek();
			q.dequeue();
			a = t->getValue();
			//esamina a
			if(!isLeftEmpty(t))
				q.enqueue(getLeftChild(t));
			if(!isRightEmpty(t))
				q.enqueue(getRightChild(t));
		}
	}
}

#endif /* SRC_BINTREE_H_ */
