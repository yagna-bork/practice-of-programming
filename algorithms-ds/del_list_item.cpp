#include <iostream>
#include <cstring>
#include <string>

using std::cout; using std::cerr; using std::endl;
using std::string;

template <class T>
struct listitem {
	T val;	
	listitem<T>* next;
};

// add item to the front of list
template <class T>
listitem<T>* addfront(listitem<T>* list, const T& val)
{
	listitem<T>* new_item = new listitem<T>;
	new_item->val = val;
	new_item->next = list;
	return new_item;
}

template <class T>
listitem<T>* delitem(listitem<T>* listp, const T& val, 
					 int (*cmp)(const T& a, const T& b))
{
	listitem<T> *prev = NULL, *p;
	for (p = listp; p != NULL; prev = p, p = p->next) {
		if (cmp(p->val, val) == 0)
			break;
	}
	if (p != NULL) { // val found
		prev->next = p->next;		
		delete p;
	}
	return listp;
}

int streq(const string& a, const string& b) {
	if (a == b)
		return 0;
	else
		return 1;
};

int main(int argc, char* argv[])
{

	if (argc <= 2) {
		cerr << "usage: del_list_item todelete item1 ... itemN" 
			 << endl;
		return 1;
	}

	string todelete = argv[1];
	listitem<string>* list = NULL;
	for (int i = argc - 1; i >= 2 ; i--)
		list = addfront(list, string(argv[i]));
	delitem(list, todelete, streq);	
	
	for (listitem<string>* i = list; i != NULL; i = i->next) {
		cout << i->val << " ";
	}
	cout << endl;
	return 0;
}
