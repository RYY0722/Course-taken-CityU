// Student name: 
// Student ID  : 
#include<iostream>
using namespace std;

#ifndef my_bsearch_h
#define my_bsearch_h
void* bsearch_first(const void* key, const void* base, unsigned n, unsigned size,
	int(*compare)(const void *, const void *))
{
	// Return the address of the first element in the array that is greater
	// than or equal to the search key (according to the compare function). 
	// If the search key is greater than all elements in the array, return the
	// address that corresponds to the (hypothetical) element at index n.

	//assert: a[mid]<item<=a[high]
	int low = -1, high = n;//high is the one after the youngest person within the group
	int mid = (low + high) / 2;//mid is a valid index,bcs i<j-1 and j<n
	char *base1 = (char *)base;
	while (low < high - 1) {
		mid = (low + high) / 2;
		//	if (((person*)base)[mid].dob < *(string*)key)

		if (compare((base1 + mid*size),key))
			low = mid;
		else high = mid;
	}
	//postcondition: low==high-1 & a[mid]<item<=a[high]

	return (base1 + high*size);//(person*)
}


#endif
