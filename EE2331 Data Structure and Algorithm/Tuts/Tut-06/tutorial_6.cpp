// Student name: 
// Student ID  : 

/*
	Submission deadline: Friday, 13 March 2020, 12 noon

	We shall use the data structure vector<T> in this exercise.
	http://www.cplusplus.com/reference/vector/vector/

	Study the notes and watch the videos that explain vector, and
	recursion and backtracking.

	The storage capacity of a vector is expanded automatically when more
	elements are added to it.
	You can access an element in a vector using the subscript operator,
	e.g. v[i] references the element at index i of vector v.

	Operators that are relevant to this exercise:
		push_back(item) : add the item at the end of the vector
		pop_back()      : remove the last item in the vector
		back()          : get the last item in the vector
		size()          : return the number of items in the vector
		empty()         : return true if the vector is empty, otherwise return false
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>
#include<ctime>

using namespace std;

struct tube  // Implement the member functions add() and pop()
{
	unsigned len;          // length of the tube
	unsigned avail_space;  // vacant space in the tube
	vector<unsigned> list; // cylindrical pins added to the tube

	tube(unsigned size)  // constructor
	{
		len = avail_space = size;
	}

	
	bool add(unsigned e)
	{
		// Return true if a cylindrical pin with length e can be added to list
		// of the tube (appen at the end), otherwise return false.
		if (avail_space >= e) { 
			list.push_back(e);
			avail_space -= e;
			return true;
		}
		else return false;
	}

	void pop()
	{
		// Remove the last pin in the list from the tube.
		list.pop_back();
	}
	
};

ostream& operator<<(ostream& os, const tube& t)
{
	// Function to print a tube.

	os << "len = " << t.len << ", pins : ";
	for (int i = 0; i < t.list.size(); i++)
		os << t.list[i] << ", ";
	
	os << endl;
	return os;
}


// Other supporting functions required in your design

bool trail(const vector<unsigned>&sortedpins, int i, vector<tube>&tubes, int tubeLen) 
{
	//base case 1: no solution
	if (sortedpins[0] > tubeLen)return false;

	//base case 2: have traversed all the elements
	if (i >= sortedpins.size())return true;

	int k = 0;
	bool noInsert = true;
	//true if the current pin cannot be inserted into any current tubes

	while (k < tubes.size() && noInsert) {
		noInsert = !tubes[k++].add(sortedpins[i]);
	}
	if (noInsert) {//have to create a new tube
		tube t(tubeLen);
		t.add(sortedpins[i]);
		tubes.push_back(t);
	}
	return trail(sortedpins, i+1, tubes, tubeLen);
}
void packing(const vector<unsigned>& pins, unsigned tubeLen)
{
	// Determine the minimum number of tubes requried to store all
	// the cylindrical pins.
	// Print the results to standard output (reference the pdf file).

	// Use a vector to store the tube in your program.
	vector<tube> tubes;  // the vector is empty initially
	
	cout << "tubeLen = " << tubeLen << " cm" << endl;
	// Your codes
	vector<unsigned>sortedpins;
	sortedpins.assign(pins.begin(), pins.end());
	sort(sortedpins.begin(), sortedpins.end());
	reverse(sortedpins.begin(), sortedpins.end());

/*	tube t(tubeLen);
	t.add(sortedpins[0]);
	tubes.push_back(t);*/
	// Sample statements to define a tube and add it to the vector
	//   tube t(tubeLen);   
	//   tubes.push_back(t);
	


	// Statements to print the results, if a solution is found.	
	if (trail(sortedpins, 0, tubes, tubeLen)) 
	{
		unsigned spaceUsed = 0;
		unsigned count = 0;
		for (unsigned i = 0; i < tubes.size(); i++)
		{
			cout << "Tube " << i + 1 << " : " << tubes[i];
			spaceUsed += tubes[i].len - tubes[i].avail_space;
			count += tubes[i].list.size();
		}
		unsigned totalSpace = tubes.size() * tubeLen;
		double utilization = totalSpace > 0 ? spaceUsed * 100.0 / totalSpace : 0;
		cout << "Total no. of pins = " << count << "; space utilization = " << utilization << "%\n";

	}
	else cout << "No solution" << endl;
}

int main()
{	
	clock_t startTime, endTime;
	startTime = clock();
	
	unsigned a[] = {4, 10, 7, 12, 6, 10, 10, 8, 5, 13, 13, 11, 3, 14};	
	unsigned n = 14;

	vector<unsigned> pins;
	for (unsigned i = 0; i < n; i++)
		pins.push_back(a[i]);
	cout << "Lengths of cylindrical pins (cm) :" << endl;
	for (unsigned i = 0; i < pins.size(); i++)
	{
		if (i > 0 && i % 10 == 0)
			cout << endl;
		cout << setw(3) << pins[i] << ", ";
	}
	cout << endl << endl;


	// *** Question to think about ***
	//    Possible way to enhance computation efficiency ?
	//    Results for this test data set can be obtained in less than 1 second.



	// DO NOT modify this for-loop.
	for (unsigned tubeLen = 22; tubeLen >= 13; tubeLen -= 3)
	{
		cout << "-----------------------------------------------------\n";
		packing(pins, tubeLen);
	}
	 cout << "\n=====================================================\n";
 unsigned b[] = { 3, 5, 6, 3, 3, 4 };
 unsigned m = 6;

 pins.clear();
 for (int i = 0; i < m; i++)
   pins.push_back(b[i]);

 packing(pins, 12);
	endTime = clock();
//	cout << endl << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;

	system("pause");
	return 0;
}