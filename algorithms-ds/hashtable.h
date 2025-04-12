#ifndef GUARD_HASHTABLE_H
#define GUARD_HASHTABLE_H
#include <bitset>
#include <utility>

static const size_t TBLINIT = 1009; // arbitary prime
static const int TBLGROW = 2;
static const int BUCKETAVG = 4;

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
	
	size_t tblsize;
	size_t nentry;
	
	bool expandable;
	
	typedef unsigned int (*hashfunc)(const K&);
	hashfunc hash;

protected:
	Entry* addfront(Entry* listp, const K& key, 
			 const V& val)
	{
		return new Entry{ key, val, listp };
	}
	
	void expand_tbl()
	{
		Entry** oldtbl = tbl;
		size_t old_tblsize = tblsize;
		tblsize *= TBLGROW;
		tbl = new Entry*[tblsize]();
		
		Entry *p;
		for (int i = 0; i != old_tblsize; i++) {
			if (oldtbl[i] == NULL)
				continue;
			for (p = oldtbl[i]; p != NULL; p = p->next)
				lookup(p->key, true, &p->val);
		}
	}

public:
	HashTable() 
		: tblsize(TBLINIT), tbl(new Entry*[TBLINIT]()), nentry(0), 
		  hash(nullptr), expandable(true)
	{
	}

	HashTable(size_t tblsize, hashfunc hash, bool expandable) 
		: tblsize(tblsize), tbl(new Entry*[tblsize]()), nentry(0), 
		  hash(hash), expandable(expandable)
	{
	}

	V* lookup(const K& key, bool create = false, 
			  const V* valp = NULL) 
	{
		Entry *listp, *p;
		size_t h = hash ? hash(key) : std::hash<K>{}(key);
		h %= tblsize;
		listp = tbl[h];

		for (p = listp; p != NULL; p = p->next) {
			if (p->key == key)
				return &p->val;
		}

		if (create) {
			listp = addfront(listp, key, *valp);
			tbl[h] = listp;
			nentry++;

			double avg = nentry / (double)tblsize;
			if (!expandable || avg <= BUCKETAVG) // no expansion
				return &listp->val;
			expand_tbl();
			return lookup(key); // table changed so search again
		}
		return NULL;
	}
};
#endif
