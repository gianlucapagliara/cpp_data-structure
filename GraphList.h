/*
 * GraphList.h
 *
 *      Author: Gianluca Pagliara
 */

#ifndef SRC_GRAPHLIST_H_
#define SRC_GRAPHLIST_H_


#include "Graph.h"
#include "LinkedList.h"
#include "stdio.h"

class GraphNode{
public:
	GraphNode(int i){
		idNode = i;
	};
	GraphNode(){};
	int getId(){ return idNode; }
	void setId(int id) {idNode = id;}
private:
	int idNode;
};


template<class P>
class ArcInfo {
public:
	P weight;
	GraphNode _to;
};


template<class E, class P>
class NodeInfo {
public:
	E   label;
	bool empty;
	void* info;
	LinkedList<ArcInfo<P> > arcs;

	NodeInfo(){
		info = 0;
		empty = true;
	}
};



template<class E, class P>
class GraphList : public Graph<E, P, GraphNode > {
public:
	// Types
	typedef E Label;
	typedef P Weight;
	typedef GraphNode Node;
	typedef _Arc<Weight, Node> Arc;
	typedef Graph<Label, Weight, Node> Graph;
	typedef typename Graph::NodeList NodeList;
	typedef typename Graph::NodeListPos NodeListPos;

	// Constructors and destructor
	GraphList(int);
	~GraphList();

	// Operators
	bool isEmpty() const;
	void insertNode(GraphNode&);
	void insertArc(Node, Node, Weight);
	void deleteNode(Node);
	void deleteArc(Node, Node);
	bool existNode(Node);
	bool existArc(Node, Node);
	NodeList adjacents(Node) const;
	NodeList node_list() const ;
	Label readLabel(Node) const ;
	void writeLabel(Node, Label) ;
	Weight readWeight(Node, Node) const ;
	void writeWeight(Node, Node, Weight) ;

	int numberNodes(){
		return _nNode;
	};
	int numberArcs(){
		return _nArc;
	};


private:
	NodeInfo<E,P>* _matrix;
	int _dimension;
	int _nNode;
	int _nArc;
};


template<class E, class P>
GraphList<E, P>::GraphList(int dim){
	_dimension = dim;
	_nNode = 0;
	_nArc = 0;
	_matrix = new NodeInfo<E,P>[_dimension];
	for (int i=0; i<_dimension; i++)
		_matrix[i].arcs.create();
}

template<class E, class P>
GraphList<E, P>::~GraphList() {
	delete [] _matrix;
}

template<class E, class P>
bool GraphList<E, P>::isEmpty() const {
	return (_nNode == 0);
}

template<class E, class P>
void GraphList<E, P>::insertNode(Node& N) {
	int n = 0;
	if (_nNode < _dimension){
		while (_matrix[n].empty == false)
			n++;
		_nNode++;
		_matrix[n].empty = false;
	}
	N.setId(n);
}

template<class E, class P>
void GraphList<E, P>::insertArc(Node from, Node to, P weight) {
	ArcInfo<P> I;
	I.weight = weight;
	I._to = to;
	_matrix[from.getId()].arcs.insert(I, _matrix[from.getId()].arcs.begin());
	_nArc++;
}


template<class E, class P>
void GraphList<E, P>::deleteNode(Node n) {
	// Bisogna controllare prima che non ci siano archi uscenti o entranti in n
	bool del = true;
	int i;
	// Archi uscenti
	if (!_matrix[n.getId()].arcs.isEmpty())
		del = false;
	//Archi entranti
	for (i=0; i < _dimension && del; i++) {
		if(!_matrix[i].empty && !_matrix[i].arcs.isEmpty()) {
			typename LinkedList<ArcInfo<P> >::position p;
			p = _matrix[i].arcs.begin();
			while (!_matrix[i].arcs.isEnded(p) && del){
				if(_matrix[i].arcs.read(p)._to.getId() == n.getId())
					del = false;
				else
					p = _matrix[i].arcs.next(p);
			}
		}
	}
	if (del) {
		// la lista  matrice[n.getId()].archi e' vuota;
		_matrix[n.getId()].empty = true;
		_nNode--;
	}
}

template<class E, class P>
void GraphList<E, P>::deleteArc(Node from, Node to){
	typename LinkedList<ArcInfo<P> >::position p;
	p = _matrix[from.getId()].arcs.begin();
	bool found = false;
	while (!_matrix[from.getId()].arcs.isEnded(p) && !found){
		if (_matrix[from.getId()].arcs.read(p)._to.getId() == to.getId())
			found = true;
		else
			p = _matrix[from.getId()].arcs.next(p);
	}
	if (found)
		_matrix[from.getId()].arcs.erase(p);
	_nArc--;
}

template<class E, class P>
bool GraphList<E, P>::existNode(Node n){
	bool found = false;
	if(!_matrix[n.getId()].empty)
		found = true;
	return found;
}

template<class E, class P>
bool GraphList<E, P>::existArc(Node n1, Node n2){
	typename LinkedList<ArcInfo<P> >::position p;
	p = _matrix[n1.getId()].arcs.begin();
	bool found = false;
	while (!_matrix[n1.getId()].arcs.isEnded(p) && !found){
		if (_matrix[n1.getId()].arcs.read(p)._to.getId() == n2.getId())
			found = true;
		else
			p = _matrix[n1.getId()].arcs.next(p);
	}
	return found;
}

template<class E, class P>
typename GraphList<E, P>::NodeList GraphList<E, P>::adjacents(Node n) const{
	NodeList list;

	typename LinkedList<ArcInfo<P> >::position p;
	p = _matrix[n.getId()].arcs.begin();

	while (!_matrix[n.getId()].arcs.isEnded(p)){
		list.insert(new GraphNode(_matrix[n.getId()].arcs.read(p)._to.getId()), list.begin());
		p = _matrix[n.getId()].arcs.next(p);
	}
	return list;

}

template<class E, class P>
typename GraphList<E, P>::NodeList GraphList<E, P>::node_list() const {
	NodeList list;
	for (int i = 0; i < _dimension; i++)
		if (!_matrix[i].empty)
			list.insert(new GraphNode(i), list.begin());
	return list;
}

template<class E, class P>
E GraphList<E, P>::readLabel(Node n) const {
	return _matrix[n.getId()].label;
}

template<class E, class P>
void GraphList<E, P>::writeLabel(Node n, E label) {
	_matrix[n.getId()].label = label;
}

template<class E, class P>
P GraphList<E, P>::readWeight(Node from, Node to) const {
	P weight;
	typename LinkedList<ArcInfo<P> >::position p;
	p = _matrix[from.getId()].arcs.begin();
	bool found = false;
	while (!_matrix[from.getId()].arcs.isEnded(p) && !found){
		if (_matrix[from.getId()].arcs.read(p)._to.getId() == to.getId())
			found = true;
		else
			p = _matrix[from.getId()].arcs.next(p);
	}
	if (found)
		weight = _matrix[from.getId()].arcs.read(p).weight;
	return weight;
}

template<class E, class P>
void GraphList<E, P>::writeWeight(Node from, Node to, P weight) {
	typename LinkedList<ArcInfo<P> >::position p;
	p = _matrix[from.getId()].arcs.begin();
	bool found = false;
	while (!_matrix[from.getId()].arcs.isEnded(p) && !found){
		if (_matrix[from.getId()].arcs.read(p)._to.getId() == to.getId())
			found = true;
		else
			p = _matrix[from.getId()].arcs.next(p);
	}
	if (found){
		ArcInfo<P> I;
		I.weight = weight;
		I._to = to;
		_matrix[from.getId()].arcs.write(I,p);
	}
}


#endif /* SRC_GRAPHLIST_H_ */
