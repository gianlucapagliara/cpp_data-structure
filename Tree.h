/*
 * Tree.h
 *
 *      Author: Gianluca Pagliara
 */

#ifndef SRC_TREE_H_
#define SRC_TREE_H_

#include "TreeNode.h"

template <class T>
class Tree {
public:
	//Types
	typedef T typevalue;
	typedef TreeNode<T>* Node;

	// Constructors and destructor
	Tree();
	~Tree();

	//Operators
	void create();
	bool isEmpty() const;

	Node getRoot() const;
	Node getParent(Node) const;
	Node getFirstChild(Node) const;
	Node getNextSibling(Node) const;

	void insertRoot(Node);
	void insertRoot(typevalue);
	void insertFirstChild(Node);
	void insertFirstChild(Node, Node);
	void insertFirstChild(Node, typevalue);
	void insertSibling(Node);
	void insertSibling(Node, Node);
	void insertSibling(Node, typevalue);

	bool isLeaf(Node) const; // equivalent to say that node has no child
	bool isLastSibling(Node) const; // equivalent to say that node has no sibling

	typevalue readValue (Node) const;
	void writeValue (Node, typevalue);

	void eraseSubtree(Node);
	void eraseChildren(Node);
	void eraseSiblings(Node n);
	void copySubtree(const Tree<T>&, Node, Node);
	void insertFirstSubtree (Node, Tree&);
	void insertSiblingSubtree (Node, Tree&);

	void print(Node) const; // stampa il sottoalbero a partire dal nodo
	int height (Node) const; // restituisce l'altezza del nodo
	int count (Node) const; // restituisce il numero di nodi nel sottoalbero a partire dal nodo

	// Visita
	void visitaPreordine(Node);
	void visitaPostordine(Node);
	void visitaSimmetrica(Node, int);
	void visitaAmpiezza(Node);

private:
	bool belongsTo(Node) const;
	Node _root;
};

template <class T>
Tree<T>::Tree() {
	create();
}

template <class T>
Tree<T>::~Tree() {
	eraseSubtree(getRoot());
}

template <class T>
void Tree<T>::create() {
	_root = NULL;
}

template <class T>
bool Tree<T>::isEmpty() const {
	return _root == NULL;
}

template <class T>
typename Tree<T>::Node Tree<T>::getRoot() const {
	return _root;
}

template <class T>
typename Tree<T>::Node Tree<T>::getParent(Node n) const {
	Node p = NULL;
	if(!isEmpty() && n != _root) {
		p = n->getParent();
	}
	return p;
}

template <class T>
typename Tree<T>::Node Tree<T>::getFirstChild(Node n) const {
	return n->getFirstChild();
}

template <class T>
typename Tree<T>::Node Tree<T>::getNextSibling(Node n) const {
	return n->getSibling();
}

template <class T>
bool Tree<T>::isLeaf(Node n) const {
	return n->getFirstChild()==NULL;
}

template <class T>
bool Tree<T>::isLastSibling(Node n) const {
	return n->getSibling()==NULL;
}

template <class T>
void Tree<T>::insertRoot(Node root) {
	if (isEmpty()){
		_root=root;
		_root->setFirstChild(NULL); // non ha figli
		_root->setSibling(NULL); // non ha figli
		_root->setParent(NULL); // non ha genitore
	}
}
template <class T>
void Tree<T>::insertRoot(typevalue value) {
	if (isEmpty()){
		Node root = new TreeNode<T>();
		_root=root;
		_root->setValue(value);
		_root->setFirstChild(NULL); // non ha figli
		_root->setSibling(NULL); // non ha figli
		_root->setParent(NULL); // non ha genitore
	}
}

template <class T>
void Tree<T>::insertFirstChild(Node n) {
	Node child = new TreeNode<T>();
	if(isLeaf(n)) {
		n->setFirstChild(child);
	} else {
		child->setSibling(n->getFirstChild());
		n->setFirstChild(child);
	}
	child->setParent(n);
}

template <class T>
void Tree<T>::insertFirstChild(Node n, Node child) {
	if(isLeaf(n)) {
		n->setFirstChild(child);
	} else {
		child->setSibling(n->getFirstChild());
		n->setFirstChild(child);
	}
	child->setParent(n);
}

template <class T>
void Tree<T>::insertFirstChild(Node n, typevalue value) {
	insertFirstChild(n);
	n->getFirstChild()->setValue(value);
}

template <class T>
void Tree<T>::insertSibling(Node n) {
	Node sibling = new TreeNode<T>();
	if(isLastSibling(n)) {
		n->setSibling(sibling);
	} else {
		sibling->setSibling(n->getSibling());
		n->setSibling(sibling);
	}
	sibling->setParent(n->getParent());
}

template <class T>
void Tree<T>::insertSibling(Node n, Node sibling) {
	if(isLastSibling(n)) {
		n->setSibling(sibling);
	} else {
		sibling->setSibling(n->getSibling());
		n->setSibling(sibling);
	}
	sibling->setParent(n->getParent());
}

template <class T>
void Tree<T>::insertSibling(Node n, typevalue value) {
	insertSibling(n);
	n->getSibling()->setValue(value);
}

template <class T>
typename Tree<T>::typevalue Tree<T>::readValue(Node n) const {
	typevalue value;
	if(n != NULL) {
		value = n->getValue();
	}
	return value;
}

template <class T>
void Tree<T>::writeValue(Node n, typevalue value) {
	if(n != NULL) {
		n->setValue(value);
	}
}

template <class T>
void Tree<T>::insertFirstSubtree(Node n, Tree& t) {
	if(n != NULL) {
		Node firstChild = new TreeNode<T>();
		copySubtree(t, t.getRoot(), firstChild);
		insertFirstChild(n, firstChild);
	}
}

template <class T>
void Tree<T>::insertSiblingSubtree(Node n, Tree& t) {
	if(n != NULL && n!=_root) {
		Node sibling = new TreeNode<T>();
		copySubtree(t, t.getRoot(), sibling);
		insertSibling(n, sibling);
	}
}

template <class T>
void Tree<T>::copySubtree(const Tree& t, Node c, Node n) {
	if(!t.isEmpty()) {
		writeValue(n, t.readValue(c));
		if(!t.isLeaf(c)) {
			Node child = new TreeNode<T>();
			n->setFirstChild(child);
			child->setParent(n);
			copySubtree(t, t.getFirstChild(c), child);
			Node next = t.getFirstChild(c);
			Node prevChild = child;
			while(!t.isLastSibling(next)) {
				next = t.getNextSibling(next);
				child = new TreeNode<T>();
				prevChild->setSibling(child);
				child->setParent(n);
				copySubtree(t, next, child);
				prevChild = child;
			}
		}
	}
}

template <class T>
void Tree<T>::eraseSubtree(Node n){
	if (n != NULL) {
		if (n != _root) {
			Node parent = n->getParent();
			if (getFirstChild(parent)==n){ // it's the first child
				if(isLastSibling(n)) {
					//it hasn't siblings
					parent->setFirstChild(NULL);
				} else { // it has siblings
					parent->setFirstChild(n->getSibling());
				}
			} else{ // it isn't the first child
				// searching the "left" sibling of n
				Node prevSibling = getFirstChild(parent);
				while(prevSibling->getSibling() != n) {
					prevSibling = prevSibling->getSibling();
				}
				if(isLastSibling(n)) {
					prevSibling->setSibling(NULL);
				} else {
					prevSibling->setSibling(getNextSibling(n));
				}
			}
		} else {
			_root = NULL; // if n is root
		}
		if(!isLeaf(n)) {
			eraseChildren(n);
		}
		delete n;
	}
}

template <class T>
void Tree<T>::eraseChildren(Node n){
	if (n != NULL) {
		if(!isLeaf(n)) {
			eraseSiblings(getFirstChild(n));
			eraseSubtree(getFirstChild(n));
		}
	}
}

template <class T>
void Tree<T>::eraseSiblings(Node n) {
	if (n != NULL) {
		if(n != _root) {
			Node parent = n->getParent();
			if(getFirstChild(parent) != n) {
				Node prevFirstChild = getFirstChild(parent);
				Node prevSibling = prevFirstChild;
				while(getNextSibling(prevSibling) != n) {
					prevSibling = getNextSibling(prevSibling);
				}
				prevSibling->setSibling(prevFirstChild);
				parent->setFirstChild(n);
				Node temp = NULL;
				if(!isLastSibling(n)) {
					Node temp = n->getSibling();
				}
				n->setSibling(prevFirstChild->getSibling());
				prevFirstChild->setSibling(temp);
			}
			Node current = n->getSibling();
			Node temp = NULL;
			while(current != NULL) {
				temp = current->getSibling();
				eraseSubtree(current);
				n->setSibling(temp);
				current = n->getSibling();
			}
		}
	}
}

template <class T>
void Tree<T>::print(Node n) const {
	std::cout << "{";
	if(!isEmpty() && n != NULL) {
		Node t = n;
		Queue<Node> q;
		q.create();
		q.enqueue(t);
		while(!q.isEmpty()) {
			t = q.peek();
			std::cout << readValue(t) << ":  ";
			q.dequeue();
			if(!isLeaf(t)) {
				q.enqueue(getFirstChild(t));
				t = getFirstChild(t);
				std::cout << readValue(t) << " ";
				while(!isLastSibling(t)) {
					t = getNextSibling(t);
					q.enqueue(t);
					std::cout << readValue(t) << " ";
				}
			} else {
				std::cout << "Leaf";
			}
			std::cout << "\n";
		}
	}
	std::cout << "}";
}

template <class T>
int Tree<T>::height(Node n) const {
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
int Tree<T>::count(Node n) const {
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
			if(!isLeaf(t)) {
				q.enqueue(getFirstChild(t));
				t = getFirstChild(t);
				count++;
				while(!isLastSibling(t)) {
					t = getNextSibling(t);
					q.enqueue(t);
					count++;
				}
			}
		}
	}
	return count;
}


template <class T>
void Tree<T>::visitaPreordine(Node n) {
	if(!isEmpty() && n != NULL) {
		//esamina n
		Node t = getFirstChild(n);
		while(t!=NULL) {
			visitaPreordine(t);
			t = getNextSibling(t);
		}
	}
}

template <class T>
void Tree<T>::visitaPostordine(Node n) {
	if(!isEmpty() && n != NULL) {
		Node t = getFirstChild(n);
		while(t!=NULL) {
			visitaPostordine(t);
			t = getNextSibling(t);
		}
		//esamina n
	}
}

template <class T>
void Tree<T>::visitaSimmetrica(Node n, int i) {
	if(!isEmpty() && n != NULL) {
		Node t = getFirstChild(n);
		for(int k = 0; k < i && t!=NULL; k++) {
			visitaSimmetrica(t);
			t = getNextSibling(t);
		}
		//esamina n
		while(t != NULL) {
			visitaSimmetrica(t, i);
			t = getNextSibling(t);
		}
	}
}

template <class T>
void Tree<T>::visitaAmpiezza(Node n) {
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
			while(t!=NULL) {
				q.enqueue(t);
				t = getNextSibling(t);
			}
		}
	}
}

#endif /* SRC_TREE_H_ */
