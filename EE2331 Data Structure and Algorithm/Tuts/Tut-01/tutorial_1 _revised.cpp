// Student name: 
// Student ID  : 
/*
Submission deadline: Thursday, 23 Jan 2020, 5 pm

Part-1 : simple operations on char array.
Part-2 : conversion of IPv6 address from binary to text format.

Upload your .cpp file to Canvas.

Put down your name and student ID at the top of your program file.
10% marks will be deducted if your program file does not contain your name and ID.

Submitted program that cannot be compiled (with syntax errors) by Visual Studio
will receive no more than 30% marks.

Late submissions or submissions by other means are not accepted.
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include<cstring>


using namespace std;
char toHex(unsigned d);
char* bin2Text_IPv6(const unsigned char *v);
// ------------------------------------ functions to be implemented by student
void trim(char *a)
{
	// Remove leading and trailing white-space characters in a[].
	// Example:
	//		char a[] = "  Test 1  2 3   ";
	//		After trimming, a[] = "Test 1  2 3";

	// Your codes.
	int head = 0, tail = strlen(a) - 1;
	int i = 0;
	for (; a[head] == ' '; head++);
	for (; a[tail] == ' '; tail--);
	for (; head <= tail; i++, head++) {
		a[i] = a[head];
	}
	a[i] = '\0';
}
void squeeze(char *a)
{
	// Remove all white-space characters in a[].
	// Example:
	//		char a[] = "  Test 1  2 3   ";
	//		After squeezing, a[] = "Test123";

	// Your codes.
	int working, pointing;
	working = pointing = 0;
	int  i = 0;
	for (; a[working] != '\0'; working++) {
		if (a[working] != ' ') {
			a[pointing] = a[working];
			pointing++;
		}
	}
	a[pointing] = '\0';
}

void convertIPv6address_hex2string(const unsigned char *v, char a[])
//self-defined fcn: edited from the given fcn: void printIPv6address_hex(const unsigned char *v)
{
	int j = 0, i = 0;
	for (; i < 16; i++, j++)
	{
		a[j] = toHex(v[i] / 16);
		a[++j] = toHex(v[i] % 16);
		if (i % 2 && i < 14)
			a[++j] = ':';
	}
	a[j] = '\0';
	//	cout << a<< endl;
}
char* bin2Text_IPv6(const unsigned char *v) {
	char *a = new char[40];
	//a = { 0 };

	//covert the hex array into an quivalent but char array, i.e seems to be the same
	convertIPv6address_hex2string(v, a);

	//now the apperance of a is the same as the unsigned char array, but with ':'

	//delete all zeros, but not compressing,and find the startPos and length(max) of the longest zeros
	bool isZeros = false;
	int charPos = 0, temp = 0;
	int count = 0, startPos = 0, max = 0;
	int i = 0, j = 0;
	for (; i < 40; i++) {//a[39] is '\0', actually it is meaningless to consider this char
		//but it is added because it can be used to test the final
		if (a[i] == ':') {
			a[charPos++] = a[i++];//skip ':'
		}
		temp = i;
		isZeros = (a[j = i] == '0') && (a[++j] == '0') && (a[++j] == '0') && (a[++j] == '0');
		if (isZeros && i != 39) {
			//if i is 39, isZeros will be false because the following 3 char and a[39] itself are not 0
			a[charPos++] = '0';
			i += 3;//skip all the 0s, it should jump to the 4 th position after the first 0,
			// but there is i++ in the for loop, therefore i+=3 instead of 4
			count++;
		}
		else {
			//compare the current accumulated length and the history max length
			if (max<count) {
				max = count;
				if (i != 39)
					startPos = charPos - 2 * max;
				else {
					//if i is 39, charPos should not be added any more, 
					//i.e. no more character should be added to the string
					a[charPos] = '\0';
					startPos = charPos - 2 * max + 1;
					//if i is 39, charPos will be pointing exactly at the end of the array
					//while in other cases, charPos will be the index of the most newly added
					//value plus 1. 
				}
			}
			//judging max & count should be earlier than changing array a because 
			//it will be more troublesome to consider how many characters are added 
			//in the following while loop

			count = 0;
			while (a[i] == '0'&&i<temp + 3)i++;
			//i<temp+3 to make sure this iteration stop right before ':'
			while (i<temp + 3)a[charPos++] = a[i++];
			a[charPos++] = a[i];
		}
	}
	a[charPos] = '\0';

	//the preceeding 0s are deleted, and max_length and start_Position are found

	// compressing 
	for (i = 0, charPos = 0; a[i] != '\0'; i++) {
		if (i == startPos && max > 1) {// if max<1, do not need to compress
			//if i is startPos, just use ':' to replace the original char
			if (startPos == 0)a[charPos++] = ':';//if the targeted 0s start at index 0,
			a[charPos++] = ':';
			i += 2 * max - 1;
			//-1: because i++ in the for loop
		}
		else {
			a[charPos++] = a[i];//otherwise, just copy the value
			//i should not be incremented because this situation does not need deleting 0
			//so this should be a one by one scanning, and it is already incremented in the loop 
		}
	}
	a[charPos] = '\0';
	return a;
}

// ------------------------------------ functions given to student

void test1(char *a, char *b)
{
	cout << "-------------------------------------\n";

	cout << "Character array: \"" << a << '\"' << endl;
	trim(a);
	cout << "After trimming : \"" << a << '\"' << endl;
	squeeze(b);
	cout << "After squeezing: \"" << b << '\"' << endl;
}

void part_1()
{
	cout << "Part-1: char array\n\n";

	char a1[] = "Testing    ";
	char a2[] = "Testing    ";
	test1(a1, a2);

	char b1[] = "   Test";
	char b2[] = "   Test";
	test1(b1, b2);

	char c1[] = "   Test  1   2 3  ";
	char c2[] = "   Test  1   2 3  ";
	test1(c1, c2);

	char d1[] = "  ";
	char d2[] = "  ";
	test1(d1, d2);

	char e1[] = "";
	char e2[] = "";
	test1(e1, e2);
}

char toHex(unsigned d)
{
	// Precondition: 0 <= d <= 15

	if (d >= 10)
		return d - 10 + 'a';
	return d + '0';
}

void printIPv6address_hex(const unsigned char *v)
{
	cout << "IPv6 address (bin)  ";
	for (int i = 0; i < 16; i++)
	{
		cout << toHex(v[i] / 16) << toHex(v[i] % 16);
		if (i % 2 && i < 14)
			cout << ':';
	}
	cout << endl;
}

void test2(unsigned char *v)
{
	cout << "-----------------------------------------------------------\n";
	printIPv6address_hex(v);
	char *a = bin2Text_IPv6(v);
	cout << "IPv6 address (text) " << a << endl << endl;
	delete[] a;
}

void part_2()
{
	cout << "\n===========================================================\n";
	cout << "Part-2: IPv6 address\n\n";

	// An IPv6 address (in binary) is represented by an array of unsigned char of size 16.
	unsigned char v1[] = { 0x12, 0x34, 0x0a, 0xbc, 0x00, 0x00, 0x00, 0x78, 0xff, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x05 };
	unsigned char v2[] = { 0x20, 0x01, 0x0d, 0xb8, 0x00, 0xa3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x08 };
	unsigned char v3[] = { 0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned char v4[] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x70, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04 };
	unsigned char v5[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
	unsigned char v6[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	test2(v1);
	test2(v2);
	test2(v3);
	test2(v4);
	test2(v5);
	test2(v6);
}

int main()
{
	part_1();
	part_2();

	system("pause");
	return 0;
}