#ifndef GUARD_LIST_H
#define GUARD_LIST_H

template <class T>
struct listitem {
	T val;	
	listitem<T>* next;
};

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
#endif
