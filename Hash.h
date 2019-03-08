/*
 * Hash.h
 *
 *      Author: Gianluca Pagliara
 */

#ifndef SRC_HASH_H_
#define SRC_HASH_H_

#include "LinkedList.h"
#include "Dictionary.h"
#include <string>
using std::string;

template<class T>
class Hash {
public:
	size_t operator()(const T the_key) const;
};

/* a specialization with type string */
template<>
class Hash<string> {
public:
	size_t operator()(const string the_key) const {
		unsigned long hash_value = 0;
		int length = (int) the_key.length();
		for (int i=0; i<length; i++)
			hash_value = 5 * hash_value + the_key.at(i);
		return size_t(hash_value);
	}
	/*
	size_t H(string k) {
		long double C = 0.6180339887498949;
		long double b = k[0] * C;
		for (int j=1; j<k.size(); j++) {
			b = fmod(((b * 256) + (k[j])) * C, 1);
		}
		return (((long double) divisor) * b);
	};

	size_t H1(string k) {
		int b = k[0];
		for (int j=1; j<k.size(); j++) {
			b = ((b * 256) + (k[j])) % divisor;
		}
		return b;
	};
	*/
};

/*
template<>
class Hash<int> {
	size_t hash(int c){ return abs(c); };
	size_t hash(char c){ return std::abs(c); };
}
*/


template<class K, class E>
class hash_table: public Dictionary<K,E> {
public:
	typedef pair<K,E> mypair;
	typedef LinkedList<mypair> PairList;
	typedef typename LinkedList<mypair>::position PairPos;

	// Constructor and destructor
	hash_table(int);
	~hash_table(){
		for(int i=0; i<divisor; i++)
			table[i].~LinkedList();
		delete table;
	};

	// Operators
	bool empty() const{ return (dsize == 0); };
	int size() const{ return dsize; };

	void insert(const K& k, const E& e);
	void erase(const K& k);
	void remove(const K&);
	void modify(const K&, const E&);

	bool search(const K&, const E&) const;
	E find(const K&) const;

	int hash(const K&) const;
private:
	PairList* table;    // the hash table
	Hash<K> h;		            // maps type K to nonnegative integer
	int dsize;		                // number of pairs in dictionary
	int divisor;		            // hash function divisor
};

template<class K, class E>
hash_table<K,E>::hash_table(int the_divisor) {
	divisor = the_divisor;
	dsize = 0;

	table = new PairList [divisor];
	for (int i=0; i<divisor; i++)
		table[i].create();
}

template<class K, class E>
int hash_table<K,E>::hash(const K& k) const {
	return (h(k) % divisor);
}

template<class K, class E>
void hash_table<K,E>::insert(const K& k, const E& e){
	int p = hash(k);
	bool find = NULL;
	PairPos pos;
	pos = table[p].begin();
	while(!table[p].isEnded(pos) && !find) {
		if(table[p].read(pos)._key == k) {
			find = true;
		}
		else
			pos = table[p].next(pos);
	}
	if (!find) {
		table[p].insert(mypair(k, e), table[p].begin());
		dsize++;
	}
}

template<class K, class E>
void hash_table<K,E>::modify(const K& k, const E& e) {
	int p = hash(k);
	bool find = false;
	PairPos pos;
	pos = table[p].begin();
	while(!table[p].isEnded(pos) && !find) {
		if(table[p].read(pos)._key == k) {
			find = true;
			table[p].write(mypair(k, e),pos);
		}
		else
			pos = table[p].next(pos);
	}
}

template<class K, class E>
bool hash_table<K,E>::search(const K& k, const E& e) const {
	int p = hash(k);
	bool find = false;
	PairPos pos;
	pos = table[p].begin();
	while(!table[p].isEnded(pos) && !find) {
		if(table[p].read(pos)._key == k && table[p].read(pos)._value == e)
			find = true;
		else
			pos = table[p].next(pos);
	}
	return find;
}

template<class K, class E>
E hash_table<K,E>::find(const K& k) const {
	int p = hash(k);
	bool find = false;
	E value;
	PairPos pos;
	pos = table[p].begin();
	while(!table[p].isEnded(pos) && !find) {
		if(table[p].read(pos)._key == k) {
			find = true;
			value = table[p].read(pos)._value;
		} else
			pos = table[p].next(pos);
	}
	return value;
}

template<class K, class E>
void hash_table<K,E>::remove(const K& k){
	int p = hash(k);
	bool find = false;
	PairPos pos;
	pos = table[p].begin();
	while(!table[p].isEnded(pos) && !find) {
		if(table[p].read(pos)._key == k)
			find = true;
		else
			pos = table[p].next(pos);
	}
	if(find) {
		table[p].erase(pos);
		dsize--;
	}
}

#endif /* SRC_HASH_H_ */
