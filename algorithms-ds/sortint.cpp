#include <iostream>
#include "quicksort.h"
#include "exposort.h"
#include <iterator>
#include <algorithm>
#include <cstdlib>

using std::cout; using std::cerr; using std::endl;

int main(int argc, char* argv[]) {
	if (argc <= 1)
		cerr << "usage: sortint [-s] int1 ... intn" << endl;

	bool slow = false;
	if (strcmp(argv[1], "-s") == 0)
		slow = true;
	if (slow && argc == 2)
		cerr << "usage: sortint [-s] int1 ... intn" << endl;

	int beg = slow ? 2 : 1;
	int n = argc - beg;
	int v[n];
	std::transform(argv + beg, argv + argc, v, atoi);
	if (slow)
		exposort<int>(v, n);
	else
		quicksort<int>(v, n);

	std::ostream_iterator<int> out(std::cout, " ");
	std::copy(v, v + n, out);
	std::cout << std::endl;
	return 0;
}
