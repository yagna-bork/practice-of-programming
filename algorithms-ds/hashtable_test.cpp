#include <iostream>
#include "hashtable.h"

using std::cout; using std::cerr; using std::endl;

const int MULTIPLIER = 37;
const size_t NBUCKET = 1009; // first prime greater than 1000

size_t hash(char* s) 
{
	unsigned char h, *p;
	
	h = 0;
	for (p = (unsigned char *) s; *p != '\0'; p++) {
		h = h * MULTIPLIER + *p;
	}
	return h % NBUCKET;
}

int main() {
	HashTable<char*, int> map;
	int v = 10;
	map.lookup("yagna", true, &v);
	v = 8;
	map.lookup("diti", true, &v);
	v = 5;
	map.lookup("krishna", true, &v);
	v = 0;
	map.lookup("heli", true, &v);

	v = *(map.lookup("diti"));
	cout << v << endl;

	cout << "hash(hello, world!) = " 
		 << hash("Hello, world!") << endl;
    return 0;
}
