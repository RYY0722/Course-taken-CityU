// Student name: 
// Student ID  : 

/*
	Submission deadline: Friday, 27 March, 12 noon.
	
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
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

template<class Type>
struct node
{
	Type info;
	node<Type> *link;
};

struct person
{
	string dob;
	char gender;
	double income;
};

// Design a functional class/struct to compare person by gender and then by income.
struct comparePerson
{
	// Your codes
	bool operator()(const person& a, const person& b)
	{
		if (a.gender != b.gender)return a.gender < b.gender;
		if (a.income != b.income)return a.income < b.income;
		return true;
	} 
} compPerson;

ostream& operator<<(ostream& os, const person& p)
{
	os << p.dob << ' ' << p.gender << ' ' << p.income << endl;
	return os;
}

template<class Type, class Compare>
node<Type>* merge(node<Type>* A, node<Type>* B, Compare comp)
{
	// Lists A and B are not empty. 
	// Lists A and B are sorted according to the compare function.

	// Merge A and B to produce a sorted list.
	// Existing nodes in A and B are linked together to form the merged list.
	// This function is used to support merge sort.

	// *** No new node is created. ***
	
	node<Type>*list = nullptr, *r = nullptr;//the start and end of the return list
	node<Type>*a = A, *b = B;
	//a and b are not null
	if (a && b)
	{
		//the first element should be from A
		if (comp(A->info, B->info))
		{
			list = A;
			a = A->link;
			b = B;
		}
		//the first element should be from B
		else
		{
			list = B;
			a = A;
			b = B->link;
		}
		r = list;//initialize r
		while (a && b)
		{
			if (comp(a->info, b->info))
			{
				r->link = a;
				a = a->link;
			}
			else
			{
				r->link = b;
				b = b->link;
			}
			r = r->link;
		}
		//copy the remaining
		if (a) r->link = a;
		else r->link = b;
	}
	//a is null or b is null
	else
	{
		if (a)list = a;
		else list = b;
	}

	return list;  
}

// Other functions required in your design
template<class Type>
node<Type>*getNextStart(node<Type>*& list)
{
	
	node<Type>*a = list, *b = list;
	//a is used to traverse the list, and b  move to the middle
	for (int i = 0; a->link ; i++)
	{
		if (i % 2) b = b->link;
		a = a->link;
	}
	a = b->link;
	b->link = nullptr;

	return a;
}

template<class Type, class Compare>
void msort_list(node<Type>*& list, Compare comp)
{
	// Sort the list using the merge sort algorithm.
	// Your sorting method should be stable.
	// Implement the sorting algorithm using recursion.

	// Your codes

	//separate it into 2
	node<Type>*nextSubList = getNextStart(list);

	//base case: there is no element in the list
	if (!nextSubList) return;

	msort_list(list, comp);
	msort_list(nextSubList, comp);
	list = merge(list,nextSubList, comp);
}

// ------------------------------------ functions given to you

template<class Type>
void printList(const char *label, const node<Type> *list)
{
	cout << label << endl;
	const node<Type> *p = list;
	while (p != nullptr)
	{
		cout << p->info;		 
		p = p->link;
	}
	cout << endl;
}

node<person>* readDataFile(const string& filename)
{
	ifstream infile;
	infile.open(filename);
	if (infile.is_open() == false)
	{
		cout << "Cannot open data file." << endl;
		system("pause");
		exit(0);
	}

	string temp;
	int n;
	infile >> temp >> n;

	node<person> *header = new node<person>;
	header->link = nullptr;
	node<person> *last = header;
	for (int i = 0; i < n; i++)
	{
		last->link = new node<person>;
		last = last->link;
		infile >> last->info.dob >> last->info.gender >> last->info.income;
	}
	last->link = nullptr;

	infile.close();
	node<person> *list = header->link;
	delete header;
	return list;
}

int main()
{	
	node<person> *list = readDataFile("tut-08-data.txt");
	printList("List of persons:", list);
	// The list is initially sorted by dob.

	// Sort the list by gender, and then by income using merge sort.
	// Your sorting method should be stable.
	msort_list(list, compPerson);
	printList("List of persons (sorted by gender and then by income):", list);
	cout << endl;

	system("pause");
	return 0;
}