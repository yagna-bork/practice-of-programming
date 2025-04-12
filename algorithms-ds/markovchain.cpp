#include <unordered_map>
#include <deque>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include "list.h"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cstdlib>

using std::unordered_map; using std::deque; 
using std::string; using std::istream;
using std::cout; using std::endl; using std::vector;
using std::cin; using std::fstream;
using std::ostream_iterator; using std::transform;
using std::cerr;

static const size_t NHASH = 4009; // TODO think
static const int MULTIPLIER = 37;
static const size_t NPREF = 2;
static const int MAXGEN = 10000;

class stringset {
protected:
	listitem<string> *set[NHASH];

protected:
	unsigned int hash(const string& s) const
	{
		unsigned char h = 0;
		for (int i = 0; i != s.size(); i++)
			h = h * MULTIPLIER + ((unsigned char) s[i]);
		return h % NHASH;
	}

public:
	string *insert(const string& s)
	{
		unsigned int h = hash(s);
		listitem<string>* listp = set[h]; 
		listitem<string>* p;
		for (p = listp; p != NULL; p = p->next) {
			if (p->val == s)
				return &p->val;
		}
		listp = addfront(listp, s);
		set[h] = listp;
		return &listp->val;
	}
};

typedef deque<string*> Prefix;

struct PrefixHash {
	size_t operator()(const Prefix& pref) const
	{
		size_t addr;
		unsigned char byte;

		size_t h = 0;
		for (int i = 0; i != pref.size(); i++) {
			string *p = pref[i];
			size_t addr = (size_t) p;
			for (int b = 0; b != sizeof(p); b++) {
				byte = (unsigned char) (addr>>b);
				h = h * MULTIPLIER + byte;
			}
		}
		return h;
	}
};

struct PrefixEq {
	bool operator()(const Prefix& a, 
					const Prefix& b) const
	{
		return std::equal(a.cbegin(), a.cend(), 
						  b.cbegin());
	}
};

unordered_map<
	Prefix, vector<string*>, PrefixHash, PrefixEq
> prefixtab;
stringset words; /* set of words encountered */

void add(Prefix& pref, string& suffix)
{
	string *sp = words.insert(suffix);
	if (pref.size() == NPREF) { // pref fully initialised
		prefixtab[pref].push_back(sp);
		pref.pop_front();
	}
	pref.push_back(sp);
}

void build(Prefix& pref, istream& in)
{
	string buf;	
	while (in >> buf)
		add(pref, buf);
}

void build(Prefix& pref, istream& in, int n)
{
	string buf;	
	for (int i = 0; i != n; i++) {
		if ( !(in>>buf) )
			break;
		add(pref, buf);
	}
}

void generate();

int main(int argc, char* argv[])
{
	if (argc != 3) {
		cerr << "usage: markovchain file positive-integer" 
			 << endl;
		return 1;
	}
	char* fname = argv[1];
	unsigned seed = atoi(argv[2]);

	srand(seed);

	Prefix pref;
	fstream f(fname);
	build(pref, f);
	f.close();
	
	// TODO tidy main and make multiple files

	// set pref to first NPREF words of input
	pref.clear();
	f = fstream("chapter.txt");
	build(pref, f, NPREF);
	f.close();
	
	for (int i = 0; i != NPREF; i++)
		cout << *pref[i] << " ";

	// generate output
	for (int i = 0; i != MAXGEN; i++) {
		vector<string*>& suffixes = prefixtab[pref];
		string* suffix = suffixes[rand() % suffixes.size()];
		cout << *suffix << " ";
		pref.pop_front();
		pref.push_back(suffix);
	}
}
