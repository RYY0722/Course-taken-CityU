// Student name: 
// Student ID  : 

/*
Submission deadline: Friday, 28 Feb 2020, 12 noon.

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
#include<ctime>

using namespace std;
struct person
{
	string dob;     // date of birth, yyyy-mm-dd
	char gender;    // 'F' for female, 'M' for male
	double income;
};

ostream& operator<<(ostream& os, const person& p)
{
	os << p.dob << ' ' << p.gender << ' ' << p.income << endl;
	return os;
}

//convert char[] to decimal num


//judge if it is within the age reange
// Use of global variable is acceptable if it is read only.
const string today = "2020-03-02";
// --------------------------------------- functions to be implemented by student

// You may define other supporting functions, if required.

void analyse(const person *list, int n, int age_L, int age_H)
{
	// preconditions: list[] is sorted by dob in ascending order,
	//                n = length of list, and age_H >= age_L    

	// age_L and age_H (inclusive) define an age-group.
	// Age is determined as of today (a constant value is used in this exercise).

	// Find the average income of females, and average income of males in the age-group.
	// Print the results to standard output.

	// Do not traverse the array from the beginning using sequential search.
	// Use binary search to locate a person within the age-group,
	// and then process persons in the age-group sequentially.

	// For age_L = 50, age_H = 59, and today = "2020-02-24", process persons  
	// that were born after 1960-02-24, and were born on or before 1970-02-24.
	// Do not hardcode the dates in your program. 
	// Values of age_L, age_H and today may vary.

	// Your codes.

	string eldest, youngest;
	eldest.assign(today).replace(0, 4, to_string(stoi(today.substr(0, 4)) - age_H - 1));//substitute the year to get the birth date of the eldest person (exclusive) 
	youngest.assign(today).replace(0, 4, to_string(stoi(today.substr(0, 4)) - age_L));//get the birth date of the youngest person (inclusive) 

	int start = 0, end = 0;
	
	//calculate the data
	int num[2] = { 0 };
	double inc[2] = { 0.0 };
	//find the last person within the age group
	int low = -1, high = n;//high is the one after the youngest person within the group
	while (low < high - 1) {
		int mid = (low + high) / 2;//mid is a valid index,bcs i<j-1 and j<n
		if (list[mid].dob <= youngest) 
			low = mid;
		else high = mid;
	}

	end = high - 1;
	for (start = end; list[start].dob > eldest; start--) {
		int temp = list[start].gender == 'F'; //temp is 1 if female	
		num[temp]++;
		inc[temp] += list[start].income;
	}
	start += 1;

	// 	Other print statements required. See the jpeg file for the requirements.
	cout << "Reference date is " << today << endl << endl;
	cout << "Index range of persons in the age-group " << age_L << " to " << age_H << ":\n";
	cout << "Start index = " << start << " to end index (inclusive) = " << end << endl;
	cout << "list[start] : " << list[start];
	cout << "list[end] : " << list[end] << endl << endl;
	cout << "Number of females in the age-group " << age_L << " to " << age_H << " = " << num[1] << endl;
	cout << "Average income of females in the age-group = " << inc[1] / num[1] << endl;
	cout << endl;
	cout << "Number of males in the age-group " << age_L << " to " << age_H << " = " << num[0]  << endl;
	cout << "Average income of males in the age-group = " << inc[0] / num[0] << endl << endl;

}

// -------------------------------------------------- functions given to student

person* readDataFile(string filename, int& n)
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
	infile >> temp >> n;

	person *list = new person[n];
	for (int i = 0; i < n; i++)
		infile >> list[i].dob >> list[i].gender >> list[i].income;

	return list;
}

int main()
{
	// Put the data file "persons.txt" in the working directory of your project.
	// Suppose your project is located at c:\myProject,
	// put the data file in c:\myProject\myProject
	clock_t startTime, endTime;
	startTime = clock();	
	int n = 0;
	person *list = readDataFile("persons.txt", n);  // DO not modify this statement
	analyse(list, n, 40, 49);
	endTime = clock();
//	cout << endl << "Time is "<<(double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
	system("pause");
	return 0;
}