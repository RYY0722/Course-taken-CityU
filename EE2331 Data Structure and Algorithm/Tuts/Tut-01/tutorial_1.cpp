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
	char *working, *pointing;
	working = pointing = a;
	int  i = 0;
	for (; *working != '\0'; working++) {
		if (*working != ' ') {
			*pointing = *working;
			pointing++;
		}
	}
	*pointing = '\0';
}

void convertNum2Text(int num, char *a, int &currentPos) {
	char temp[4] = { 0 };
	int tempNum = num, cnt = 0;
	if (tempNum == 0) a[currentPos++] = '0';
	while (tempNum >= 1) {
		temp[cnt++] = toHex(tempNum % 16);
		tempNum /= 16;
	}
	int i = 0;
	tempNum = cnt;
	for (cnt -= 1; cnt >= 0; cnt--, i++) {
		a[i + currentPos] = temp[cnt];
	}
	a[i + currentPos + 1] = '\0';
	currentPos += tempNum;
	// cout<<endl<<a;
}
char* bin2Text_IPv6(const unsigned char *v) {
	char *a = new char[40];

	int numericForm[8];
	int i = 0, j = 0, temp = 0;//temp vars
	for (; i < 16; i++, j++) {
		numericForm[j] = int(v[i]) * 16 * 16;
		++i;
		numericForm[j] += int(v[i]);
	}

	//showing every element of the array numericForm 
	/*for(int i=0;i<8;i++){
	cout<<hex<<numericForm[i]<<':';
	}*/
	//numericForm is 8-number array, the dec form of ipv6
	//then, find the starPos and the max length of zeros
	int count = 0;
	int max = 0, startPos = 0;
	for (i = 0; i<9; i++) {
		if (numericForm[i] == 0 && i != 8) {
			//i<9 instead of 8 && one more restriction "i!=8" are added to deal with the situation that the longest zeros string ends at the end of the numarray, i.e.i=8 
			count++;
		}
		else {
			if (max<count) {
				if (max == 1)
					startPos = i - count + 1;
				else {
					startPos = i - count;
					max = count;
				}
			}
			count = 0;
		}
	}
	//showing the max and startPos(for testing)
	//cout<<"max is "<<max<<endl<<"startPos is "<<startPos<<endl;
	//max length of zeros is found, starPos is found

	//the following aims at manipulating the output char array a
	int currentPos = 0;
	bool flag = false;//indicating that do not need to compress
	if (max > 1)flag = true;
	for (i = 0; i<8; i++) {
		if (i != startPos) {
			convertNum2Text(numericForm[i], a, currentPos);
			if (i != 7)a[currentPos++] = ':';
		}
		else if (max != 1 && flag) {//if flag is false, that means max is <=1
			//which means there is no need to compress, i.e. add one more ':' 
			//and skip some positions.
			a[currentPos++] = ':';
			if (i == 0) a[currentPos++] = ':';
			i += max - 1;//this is not i+=max because in the for loop i is incremented by 1
		}


	}
	a[currentPos] = '\0';
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
	/*unsigned char在计算机中使用补码存储，例如
	unsigned char a = 0xF7;
	a在计算机中存储的方式为：11110111*/
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