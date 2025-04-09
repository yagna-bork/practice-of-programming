#ifndef GUARD_QUICKSORT_H
#define GUARD_QUICKSORT_H
#include <utility>

template <class T>
void quicksort(T v[], int n) {
	if (n <= 1)
		return; // Already sorted

	int pivot = rand() % n;
	std::swap(v[pivot], v[0]);

	int last = 0;
	for (int i = 1; i != n; i++) {
		if (v[i] < v[0])
			std::swap(v[i], v[++last]);
	}
	std::swap(v[0], v[last]); // fix pivot to final pos
	quicksort<T>(v, last); // sort to left of pivot
	quicksort<T>(v+last+1, n-last-1); // and right
}
#endif
