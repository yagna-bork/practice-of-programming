#include <iostream>
#include "tree.h"
#include <iterator>
#include <algorithm>

using std::cout; using std::cerr; using std::endl;

int main(int argc, char* argv[]) 
{
	if (argc <= 1) {
		cerr << "usage: treesort item1 ... itemN" 
			 << endl;
		return 1;
	}

	int n = argc - 1;
	int v[n];
	for (int i = 1; i != argc; i++)
		v[i-1] = argv[i];
	treesort(v, n);
	std::ostream_iterator<int> out(cout, " ");	
	std::copy(v, v + n, out);
	cout << endl;
	return 0;
}
