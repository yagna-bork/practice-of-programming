#include "tree.h"
#include <iostream>
#include <string>

using std::cout; using std::cerr; using std::endl;
using std::string;

int main(int argc, char* argv[]) {
	if (argc <= 2) {
		cerr << "usage: lookuptree lookupval val1 ... valn" << endl;
		return 1;
	}
	
	TreeNode<string> *root = NULL;
	string tolookup = argv[1];
	for (int i = 2; i != argc; i++)
		root = insert(root, string(argv[i]));
	TreeNode<string> *pos = lookup(root, tolookup);
	if (pos == nullptr)
		cout << "not found" << endl;
	else
		cout << "found" << endl;
	return 0;
}
