#include <iostream>
#include "hashtable.h"

using std::cout; using std::cerr; using std::endl;

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
    return 0;
}
