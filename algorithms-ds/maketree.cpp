#include "tree.h"
#include <iostream>
#include <string>

using std::cout; using std::cerr; using std::endl;
using std::string;

void printstr(const string& s)
{
	cout << s << " ";
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		cerr << "usage: maketree val1 ... valn" << endl;
		return 1;
	}
	
	TreeNode<string> *root = NULL;
	for (int i = 1; i != argc; i++)
		root = insert(root, string(argv[i]));
	applyinorder(root, printstr);
	cout << endl;
	return 0;
}
