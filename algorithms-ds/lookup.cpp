#include <cstring>

int lookup(char* word, char* words[], int nword)
{
	int low, high, mid, cmp; 
	low = 0;
	high = nword - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		cmp = strcmp(word, words[mid]);
		if (cmp < 0)
			high = mid - 1;
		else if (cmp > 0)
			low = mid + 1;
		else // Word found
			return mid;
	}
	return -1; // Word not found
}
