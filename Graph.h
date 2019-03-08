/*
 * Graph.h
 *
 *      Author: Gianluca Pagliara
 */

#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include "LinkedList.h"

template<class P, class N>
class _Arc {
public:
	N _from;
	N _to;
	P weight;
};


template<class E, class P, class N>
class Graph {
public:
	//Types
	typedef E Label;
	typedef P Weight;
	typedef N Node;

	typedef _Arc<Weight, Node> Arc;
	typedef LinkedList<Node*> NodeList;
	typedef typename LinkedList<Node*>::position NodeListPos;
	typedef LinkedList<Arc> ArcList;

	//Operators
	virtual bool isEmpty() const = 0;
	virtual void insertNode(Node&) = 0;
	virtual void insertArc(Node, Node, Weight) = 0;
	virtual void deleteNode(Node) = 0;
	virtual void deleteArc(Node, Node) = 0;
	virtual bool existNode(Node) = 0;
	virtual bool existArc(Node, Node) = 0;
	virtual NodeList adjacents(Node) const = 0;
	virtual NodeList node_list() const = 0;
	virtual Label readLabel(Node) const = 0;
	virtual void writeLabel(Node, Label) = 0;
	virtual Weight readWeight(Node, Node) const = 0;
	virtual void writeWeight(Node, Node, Weight) = 0;

	virtual int numberNodes() = 0;
	virtual int numberArcs() = 0;

	virtual ~Graph(){};

};



#endif /* SRC_GRAPH_H_ */
