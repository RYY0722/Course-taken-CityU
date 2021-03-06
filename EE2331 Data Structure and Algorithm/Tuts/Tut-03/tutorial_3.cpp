// Student name: 
// Student ID  : 

/*
Submission deadline: Friday, 21 Feb 2020, 12 noon.

Upload your .cpp file to Canvas.

Put down your name and student ID at the top of your program file.
10% marks will be deducted if your program file does not contain your name and ID.

Submitted program that cannot be compiled (with syntax errors) by Visual Studio
will receive no more than 30% marks.

If your program crashes or infinite-loop when executed with Visual Studio,
you should state the problem at the top of your program file
(right below student name and ID); otherwise significant percentage (30% or more)
of marks will be deducted.

Late submissions or submissions by other means are not accepted.
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// -------------------------------------------- functions to be implemented by you
void longest_block(const int* a, int n, int& start, int& len)
{
	start = 0;
	len = n > 0 ? 1 : 0;
	if (n == 1 || n == 0)return;
	int i = 0;
	bool done = false;//if n <= 0, return already
	int j = i + 1;
	while (!done)
	{
		if (j > i + 1) return;
		j = (i + 1) % n;
		//if j in the last round > j in this round(i+1)
		//then, after this round of searching, no need to count any more
		//otherwise in the next round, left will start at j+1 that is [0,n-1]
		//again, which has been done already.
		while (a[j] == a[i]) {
			j++;
			if (j - i == n) break;
			//all the elements are the same. Break, otherwise, forever loop
			//also have reached the max of possible length
			j %= n;
	/*		if (j >= n) {
				done = true;
				j %= n;
			}
			This part is no need. Because if j >- n, this round is still needed.
			In the next round, done = j > i + 1; will detect this situation and return immediately
			*/
		}
		if ((j - i + n) % n> len) {
			start = i;
			len = (j - i + n) % n;
		}
		i = j % n; // move to the next element
		if(!done)done = i == start;
	}
}

void longestSubSeq_NoDup(const int* a, int n, int& start, int& len)
{
	start = 0;
	len = n > 0 ? 1 : 0;
	if (n == 1 || n == 0)return;
	int i = 0;
	int left = start;//store the current head
	bool done = false;//if n <= 0, return already
	int j = 0;
	while (!done)
	{
		j = i - 1;
/*		for (; i - left >= 0 && j >= left && a[j] != a[i]; j--);
		//case 1: i >= left, search range of j should be from [left,n-1]
		for (; i - left < 0 && (j >= left || j < i) && a[j] != a[i]; j = (j - 1 + n) % n);
		//case 2: i < left, search range is [0,i-1] and [left,n-1]
		(j < left) && (i < j || left <= i)
		*/
		for (int k = 0; k < (i - left + n) % n&&a[j] != a[i]; k++, j = (j - 1 + n) % n);
		if ((i <= j && j < left)||((left < i || j <left) && i < j)) {//no duplicate element on the "left"
			int temp = i - j == n ? n : (i - j + n) % n;
			//	int temp = (i - j > n) || (i - j < 0) ? (i - j + n) % n : i - j;
			if (temp > len) {
				start = left;
				len = temp;
			}
		}
		else left = j + 1;
		i = (i + 1) % n; // move to the next element
		if (left < start)return;
		//left < start means that counting starts between 0 and start again
		//which should have been done previously
		done = i == start;
	}
}

// -------------------------------------------------- functions given to you
void printArray(const char *header, const int* a, int n)
{
	cout << header << ", size = " << n << endl;
	for (int i = 0; i < n; i++)
	{
		if (i > 0 && i % 10 == 0)
			cout << endl;
		cout << setw(4) << a[i] << ", ";
	}
	cout << endl << endl;
}


void printSeq(const int *a, int n, int start, int len)
{
	cout << "subsequence: ";
	for (int i = 0; i < len; i++)
		cout << a[(start + i) % n] << ", ";
	cout << endl;
}

void test_longest_block(const char *header, const int *a, int n)
{
	printArray(header, a, n);
	int start, len;
	longest_block(a, n, start, len);
	cout << "Longest block:\n";
	cout << "start index = " << start << ", block len = " << len << endl;
	cout << "----------------------------------------------------------\n";
}

void part_1()
{
	cout << "Part_1:\n\n";

	int a[] = { 1, 2, 2, 3, 3, 4, 4, 4, 6, 6, 6, 5, 5, 5, 5, 5, 2, 0, 1, 3 };
	int n = 20;

	int b[] = { 1, 1, 3, 3, 1, 4, 4, 4, 0, 8, 6, 6, 5, 5, 5, 5, 2, 1, 1, 1 };
	int m = 20;

	int c[] = { 3, 3, 3, 3};
	int p = 4;

	int d[] = { 2 };
	int q = 1;

	test_longest_block("a[]", a, n);
	test_longest_block("b[]", b, m);
	test_longest_block("c[]", c, p);
	test_longest_block("d[]", d, q);
	test_longest_block("d[]", d, 0);  // empty array
}

void test_longestSubSeq_NoDup(const char *prefix, const int *a, int n)
{
	printArray(prefix, a, n);
	int start, len;
	longestSubSeq_NoDup(a, n, start, len);
	cout << "Longest subsequence with no duplicate value:\n";
	cout << "start index = " << start << ", subSeq len = " << len << endl;
	printSeq(a, n, start, len);
	cout << "----------------------------------------------------------\n";
}

void part_2()
{
	cout << "\n==========================================================\n";
	cout << "Part_2:\n\n";

	int a[] = { 1, 2, 3, 0, 2, 7, 3, 4, 5, 6, 4, 8, 0, 2, 3, 1, 6, 8, 3, 2 };
	int n = 20;

	int b[] = { 5, 9, 7, 4, 5, 7, 3, 4, 5, 6, 4, 0, 9, 0, 4, 1, 6, 8, 3, 2 };
	int m = 20;

	int c[] = { 3, 3, 3, 3 };
	int p = 4;

	int d[] = { 1, 0, 2, 3 };
	int q = 4;

	int e[] = { 2 };
	int r = 1;

	test_longestSubSeq_NoDup("a[]", a, n);
	test_longestSubSeq_NoDup("b[]", b, m);
	test_longestSubSeq_NoDup("c[]", c, p);
	test_longestSubSeq_NoDup("d[]", d, q);
	test_longestSubSeq_NoDup("e[]", e, r);
	test_longestSubSeq_NoDup("e[]", e, 0);  // empty array
}

int main()
{
	part_1();
	part_2();

	system("pause");
	return 0;
}