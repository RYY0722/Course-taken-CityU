// Student name: 
// Student ID  : 

/*
	Submission deadline: Friday, 6 March 2020, 12 noon.

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
#include <string>
#include <cstdlib>
#include "my_bsearch.h"
#include<cmath>

using namespace std;
string getCurDate();
string adjustYear(const string& date, int y);

// Acceptable to use global variable that is read only.
// today is a constant global variable, set to the date of current local time.
const string today = getCurDate();  

struct person
{
	string dob;     // date of birth, yyyy-mm-dd
	char gender;    // 'F' for female, 'M' for male
	double income;

	// Define your own public member function(s) if appropriate.
};

ostream& operator<<(ostream& os, const person& p)
{
	os << p.dob << ' ' << p.gender << ' ' << p.income << endl;
	return os;
}

// Other supporting functions required in your design.


int qcompare(const void * a, const void * b)//sorted by income
{
	return (*(person*)b).income - (*(person*)a).income;
}
int mycompare(const void * a, const void * b)
{

	return (*(person*)a).dob<(*(person*)b).dob;
}

void analyse(person *list, int n)
{
	// Analyse persons that belong to the age-groups 20-29, 30-39, 40-49, 50-59, and 60-69.
	// You may assume that the above age-groups are fixed in this exercise.

	// Find the average income of perons in the top quartile of the above age-groups.
	// Print the results to standard output. (See the jpeg file for the requirements).

	// If there are k persons in a group, the number of persons in the top-quartile is k/4.
	// That is the 25% of persons with highest income in the group.

	// If you want to sort the array, use the qsort() function to do the sorting.
	// If you want to search the array, use the bsearch_first() function defined in "my_bsearch.h"
//	string today = "2020-03-02";
	cout << "Reference date is " << today << endl << endl; 

	//find 20 and 69 to reduce the search and sort range
	person key = { today,'F',0 };
	key.dob.assign(today).replace(0, 4, to_string(stoi(today.substr(0, 4)) - 20));//to find 20
	person *upper = (person *)bsearch_first(&key, list, n, sizeof(person), mycompare);//the oldest person(inclusive)
	person *lower;//the youngest person(inclusive)
	key.dob.assign(today).replace(0, 4, to_string(stoi(today.substr(0, 4)) - 70));
	
	person *oldest = (person *)bsearch_first(&key, list, upper-list+1, sizeof(person), mycompare);
	n = upper - oldest + 1;//the new length is from oldest to lower
	//oldest: the youngest 69, upper: the oldest one of 19

	for (int i = 3; i <= 7; i++) {
		lower = upper - 1;//the one before the last one in the last group = youngest one in the current group
		int age = i * 10;

		//find upper (the older bound)	
		key.dob.assign(today).replace(0, 4, to_string(stoi(today.substr(0, 4)) - age));

		upper = (person *)bsearch_first(&key, oldest, n, sizeof(person), mycompare);
		if (upper->dob.substr(5) == today.substr(5))upper += 1;//this person is exactly i*10 years old and should be excluded.
		n = upper - oldest + 1;//search range should be reduced
		
//		cout << "Test range:" << endl;
//		cout << upper->dob << '\t' << lower->dob << endl;

//sort the specific part of list
		qsort(upper, lower - upper + 1, sizeof(person), qcompare);
	
		int quantile = (lower - upper + 1) / 4;
		double inc = 0;
		for (int j = 0; j < quantile; j++) {
			inc += upper[j].income;
			
		}
		cout << "Average income of persons in the top-quartile of the age-group "
			<< (i - 1) * 10 << " to " << (i * 10 - 1) << " = " << inc / quantile << endl << endl;
		
	}
	
	// Print the sorted list to a file for debugging/testing purpose.
	// Disable the printing in your submitted program.
/*	string outfile_name = "sorted-list-" + today + ".txt";
	ofstream outfile(outfile_name);
	outfile << "n " << n << endl;
	for (int i = 0; i < n; i++)
		outfile << setw(4) << i << " : " << list[i];
	outfile.close();*/
	

}

// -------------------------------------------------- functions given to you

person* readDataFile(string filename, int& n)
{
	ifstream infile;
	infile.open(filename);
	if (infile.is_open() == false)
	{
		cout << "Cannot open data file" << endl;
		system("pause");
		exit(0);
	}
	
	string temp;
	infile >> temp >> n;

	person *list = new person[n];
	for (int i = 0; i < n; i++)
		infile >> list[i].dob >> list[i].gender >> list[i].income;

	infile.close();
	return list;
}

string adjustYear(const string& date, int y)
{
	// Return a string that represents the date where 
	// the year is adjusted by adding the value y.

	return to_string(stoi(date.substr(0, 4)) + y) + date.substr(4);
}

string getCurDate()
{
	// Return a string that represents the date of current time in the format yyyy-mm-dd.

	time_t cur = time(NULL);
	struct tm* date = localtime(&cur);
	int year = 1900 + date->tm_year;
	int month = 1 + date->tm_mon;
	int day = date->tm_mday;

	char s[11];
	itoa(year, s, 10);  // itoa(int value, char *buffer, int radix)
	s[4] = '-';
	s[5] = month / 10 + '0';
	s[6] = month % 10 + '0';
	s[7] = '-';
	s[8] = day / 10 + '0';
	s[9] = day % 10 + '0';
	s[10] = '\0';
	return string(s);
}

int main()
{
	int n = 0;
	person *list = readDataFile("persons.txt", n);
	analyse(list, n);
	system("pause");
	return 0;
}