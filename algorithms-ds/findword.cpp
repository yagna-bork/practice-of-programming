#include <iostream>
#include "lookup.h"
#include <algorithm>
#include <cstring>
#include <iterator> // REMOVE

int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cerr << "usage: findword word word1 ... wordn" 
				  << std::endl;
		return 1;
	}
	
	char* word = argv[1];	
	int nword = argc - 2;
	char* words[nword];
	for (int i = 2; i != argc; i++)
		words[i-2] = argv[i];
	
	std::sort(words, words+nword, strcmp);

	int found = lookup(word, words, nword);
	if (found != -1) {
		std::cout << word << " is in the list." << std::endl;
	} else {
		std::cout << word << " is not in the list." 
				  << std::endl;	
	}
	return 0;
}
