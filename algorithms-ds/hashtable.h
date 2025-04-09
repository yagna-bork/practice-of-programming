#ifndef GUARD_HASHTABLE_H
#define GUARD_HASHTABLE_H
#include <bitset>
#include <utility>

static const size_t TBLSIZE = 1024; // arbitary

template <class K, class V>
class HashTable
{
protected:
	struct Entry {
		K key;
		V val;
		Entry* next;
	};
	Entry** tbl;	

protected:
	Entry* addfront(Entry* listp, const K& key, 
			 const V& val)
	{
		return new Entry{ key, val, listp };
	}
	
public:
	HashTable(): 
		tbl(new Entry*[TBLSIZE]())
	{
	}

	V* lookup(const K& key, bool create = false, 
			  const V* valp = NULL) 
	{
		Entry *listp, *p;
		size_t hash = std::hash<K>{}(key) % TBLSIZE;
		listp = tbl[hash];

		for (p = listp; p != NULL; p = p->next) {
			if (p->key == key)
				return &p->val;
		}

		if (create) {
			listp = addfront(listp, key, *valp);
			tbl[hash] = listp;
			return &listp->val;
		}
		return NULL;
	}
};
#endif
