#ifndef GUARD_EXPOSORT_H
#define GUARD_EXPOSORT_H
#include <algorithm>

template <class T>
bool issorted(T* perm[], int n) {
	if (n <= 1)
		return true; // Already sorted
	for (int i = 1; i != n; i++) {
		if (*perm[i] < *perm[i-1])
			return false;
	}
	return true;
}

template <class T>
bool _exposort(T v[], int idx, T* perm[], int nfree) {
	// idx is the current elem of v being examined and
	// nfree is number of free spaces in perm for it
	if (nfree == 0)
		return issorted<T>(perm, idx);

	for (int i=0, j=0; j != nfree; i++) {
		if (perm[i] != nullptr)
			continue; // not free, try another spot

		perm[i] = v + idx;
		bool issorted = _exposort<T>(v, idx+1, perm, nfree-1);
		if (issorted)
			return true;
		perm[i] = nullptr;

		j++;
	}
	return false;
}

/*
 * Exponential time sort n elements of v.
 */
template<class T>
void exposort(T v[], int n)
{
	T* permutation[n];
	std::fill(permutation, permutation+n, nullptr);

	_exposort<T>(v, 0, permutation, n);

	T cpy[n];
	for (int i = 0; i != n; i++)
		cpy[i] = *permutation[i];
	std::copy(cpy, cpy + n, v);
}
#endif
