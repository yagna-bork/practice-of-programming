#ifndef GUARD_MARKOVCHAIN_H
#define GUARD_MARKOVCHAIN_H
#include <algorithm>
#include <fstream>

namespace markovchain {
	const size_t NPREF = 2;
	static const size_t NHASH = 4093;

	struct Suffix {
		const char* suffix;
		Suffix *next;
	};

	class States {
	protected:
		struct State {
			const char *pref[NPREF];
			Suffix *suffix;
			State *next;
		};
		
		State *tbl[NPREF];

	protected:
		unsigned int hash(const char * pref[]);

		/* add to prefix table */
		State *addfront(State *listp, const char* pref[NPREF]);

	public:
		States()
		{
			std::fill(tbl, tbl + NHASH, nullptr);
		}
		
		Suffix *lookup(const char *pref[NPREF], bool create);
	};

	/* add word to suffix list */
	Suffix *addfront(Suffix *listp, const char *s);
	
	/* read input; build prefix table */
	void build(const char *pref[NPREF], std::fstream& f);
	
	/* associate suffix with prefix; advance prefix */
	void add(const char *pref[NPREF], const char *suffix);
}
#endif
