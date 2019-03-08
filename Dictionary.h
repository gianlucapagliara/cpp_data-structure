/*
 * Dictionary.h
 *
 *      Author: Gianluca Pagliara
 */

#ifndef SRC_DICTIONARY_H_
#define SRC_DICTIONARY_H_

/* A dictionary is a collection of pairs of the form (k,v), where k is a key and v is the value
 * associated with the key k (equivalently, v is the value whose key is k).
 */

/* The pair */
template<class K, class E>
class pair {
public:
	// methods
	pair(){};
	pair(const K& k, const E& e): _key(k), _value(e) {};
	pair(const pair<K,E>& the_pair): _key(the_pair._key), _value(the_pair._value){};
	K _key;
	E _value;
};


template <class K, class E>
class Dictionary {

public:
	virtual ~Dictionary() {}

	// return true iff the dictionary is empty
	virtual bool empty() const = 0;
	// return the number of pairs in the dictionary
	virtual int size() const = 0;
	// insert the pair p into the dictionary
	virtual void insert(const K& k, const E& e) = 0;
	// return the value of key k
	virtual E find(const K& k) const = 0;
	// delete the pair
	virtual void remove(const K& k) = 0;
	// modify the value of the pair with key k to e
	virtual void modify(const K& k, const E& e) = 0;
};


#endif /* SRC_DICTIONARY_H_ */
