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
	node<Type> *head = new node<Type>;// add a dummy head to list
	head->link = list;
	Type val_list_1 = list->info;
	node<Type> *i = head;//i records the previous element of the founded location.
	node<Type> *q = i->link;// "q = i + 1"
	const node<Type> *p = subseq;
	while (i->link && !Equal) 
	{
		//reset
		Equal = true;
		q = i->link;
		p = subseq;
		while (p && Equal) 
		{			
			if (p->info == q->info) 
			{
				p = p->link;
				q = q->link;
			}
			else Equal = false;
		}
		if(!Equal)i = i->link;
	}
	//i points to the node before the found location
	//q points to the node after the subsequence in the list
	//remove if exists
   	if (Equal) 
	{
		p = i->link;

		//logically delete
		if (i == head)list = q;//the first few elements need to be removed			
		else i->link = q;//remove elements inside the list

		//physically remove
		while (p->link!=q)
		{
			const node<Type> *w = p;
			p = p->link;
			delete w;
		}
		delete head;
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