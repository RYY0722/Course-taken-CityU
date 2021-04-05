// Student name: 
// Student ID  : 

/*
	Submission deadline: Friday, 20 March, 12 noon.
	
	Upload your .cpp file to Canvas.

	Put down your name and student ID at the top of your program file.
	10% marks will be deducted if your program file does not contain your name and ID.

	Submitted program that cannot be compiled (with syntax errors) by Visual Studio
	will receive no more than 30% marks.

	If your program crashes when executed with Visual Studio, you should state the
 	problem at the top of your program file (right below student name and ID); otherwise
	significant percentage (30% or more) of marks will be deducted.

	Late submissions or submissions by other means are not accepted.
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

template<class Type>
struct node
{
	Type info;
	node<Type> *link;
};

template<class Type>
bool findAndRemove(node<Type>*& list, const node<Type>* subseq)
{
	// If subseq is found in input list, return true and remove the 
	// first instance of the subseq in the list.
	// If subseq is not found, return false.

	// Your codes
	bool Equal = false;

	node<Type> *precursor = nullptr;//i records the previous element of the founded location.
							//i is null if the matched sequence starts at the beginning
	node<Type> *current = list;// "q = i + 1"
	const node<Type> *p = subseq;
	node<Type>*working = current;
	while (current && !Equal)
	{
		//reset
		Equal = true;		
		p = subseq;
		working = current;
		while (p && Equal) 
		{	
			
			if (p->info == working->info) 
			{
				p = p->link;
				working = working->link;
			}
			else Equal = false;
		}
		if (!Equal) {
			precursor = current;
			current = current->link;
		}
	}
	//precursor points to the node before the found location
	//working points to the node after the subsequence in the list
	//remove if exists
    	if (Equal) 
	{
		//logically delete
		if (!precursor) //i = null, matching starts at 1st element
		{
			p = list;
			list = working;
		}
		else
		{
			p = precursor->link;
			precursor->link = working;//remove elements inside the list
		}
		//p records the start of elements needed to be removed

		//physically remove
		while (p->link!=working)
		{
			const node<Type> *w = p;
			p = p->link;
			delete w;
		}
		
	}
	

	return Equal;  
}

// ------------------------------------ functions given to you

template<class Type>
void printList(const char *label, const node<Type> *list)
{
	cout << label << " { ";
	const node<Type> *p = list;
	while (p != nullptr)
	{
		cout << p->info;
		if (p->link != nullptr)
			cout << ", ";
		 
		p = p->link;
	}
	cout << " }" << endl;
}

template<class Type>
node<Type>* createList(const Type a[], int n)
{
	if (n == 0)
		return nullptr;

	node<Type> *p, *r;
	p = r = new node<Type>;
	p->info = a[0];
	for (int i = 1; i < n; i++)
	{
		r->link = new node<Type>;
		r = r->link;
		r->info = a[i];
	}
	r->link = nullptr;
	return p;
}

int main()
{	
	cout << "Find and remove a subsequnce from a list" << endl << endl;
	int a[] = {1, 1, 1, 2, 4, 2, 3, 5, 0, 8, 3 };  
	int na = 11;

	int b[] = {1, 1, 2, 4};  
	int nb = 4;

	node<int> *listA = createList(a, na);
	node<int> *listB = createList(b, nb);

	printList("listA:", listA);
	printList("lisbB:", listB);
	cout << "\nfindAndRemove(listA, listB)\n";
	bool success = findAndRemove(listA, listB);
	if (success)
		printList("listA:", listA);
	else
		cout << "listB is not found in listA\n";

	cout << "\nfindAndRemove(listA, listB)\n";
	success = findAndRemove(listA, listB);
	if (success)
		printList("listA:", listA);
	else
		cout << "listB is not found in listA\n";

	int c[] = {1, 2, 3};  
	int nc = 3;
	node<int> *listC = createList(c, nc);

	cout << endl;
	printList("listC:", listC);
	cout << "findAndRemove(listA, listC)\n";
	success = findAndRemove(listA, listC);
	if (success)
		printList("listA:", listA);
	else
		cout << "listC is not found in listA\n";

	int d[] = {5, 0, 8, 3};
	int nd = 4;
	node<int> *listD = createList(d, nd);

	cout << endl;
	printList("listD:", listD);
	cout << "findAndRemove(listA, listD)\n";
	success = findAndRemove(listA, listD);
	if (success)
		printList("listA:", listA);
	else
		cout << "listD is not found in listA\n";

	cout << endl;
	system("pause");
	return 0;
}