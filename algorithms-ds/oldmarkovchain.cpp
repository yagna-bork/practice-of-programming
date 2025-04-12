#include "markovchain.h"
#include <cstring>
#include <algorithm>
#include <string>

using namespace markovchain;

static const int MAXGEN = 10000; /* max number of output words */
static const int MULTIPLIER = 37;

unsigned int States::hash(const char* pref[NPREF])
{
	unsigned int h = 0;
	unsigned char *p;
	for (int i = 0; i != NPREF; i++) {
		for (p = (unsigned char *) pref[i]; *p != '\0'; p++)
			h = MULTIPLIER * h + *p;
	}
	return h % NHASH;
}

/* wrapper to make strcmp an std::BinaryPred */
bool strcmp2(const char *&s, const char *&t) 
{
	return strcmp(s, t) == 0;
}

Suffix *addfront(Suffix *listp, const char *s)
{
	return new Suffix{ s, listp };
}

/* adds a new state to the front of a list */
States::State *States::addfront(State *listp, 
								const char *pref[NPREF])
{
	State *state = new State;
	std::copy(pref, pref + NPREF, state->pref);
	state->suffix = nullptr;
	state->next = listp;
	return state;
}

Suffix *States::lookup(const char *pref[NPREF], bool create)
{
	bool match;
	unsigned int h = hash(pref);
	State *listp = tbl[h];

	for (State *p = listp; p != nullptr; p = p->next) {
		match = std::equal(p->pref, p->pref + NPREF, pref, 
						   strcmp2);
		if (match)
			return p->suffix;
	}

	if (create) {
		listp = addfront(listp, pref);
		tbl[h] = listp;
		return listp->suffix;
	}
	return nullptr;
}

void build(std::string buf, std::istream& f)
{
	char buf[100];

	while(!f.eof()) {
		f.get(buf, ' ');
	}
}

void add(const char *pref[NPREF], const char *suffix);
