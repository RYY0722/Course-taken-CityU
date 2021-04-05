// Student name: 
// Student ID  : 

/*
	Submission deadline: Friday, 3 April 2020, 12 noon.

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
#include <fstream>
#include <string>
#include <stack>
#include <cmath>  // pow(double x, double y), compute the value of x to power y

using namespace std;
struct item
{
	float operand;
	int count;
	char oprtr;
};

// Other supporting functions required in your design.

float cal(char opr, float f1, float f2) {
	float result = 0;
	if (opr == '+') result = f1 + f2;
	if (opr == '-') result = f1 - f2;
	if (opr == '*') result = f1 * f2;
	if (opr == '/') result = f1 / f2;
	if (opr == '$') result = pow(f1, f2);
	return result;

}

double evaluate_prefix(const string& expr)
{
	// Your codes

	// If you need hints, a briefing video will be posted on Panopto on Monday.

	// The input expression may contain 5 operators:
	//	+ : addition
	//	- : subtraction
	//	* : multiplication
	//	/ : division
	//	$ : exponentiation

	
	stack<item> items;
	int i = 0;
	float operand = 0;
	while (expr[i] != '\0')
	{
		while (isspace(expr[i]) && expr[i] != '\0') i++;
		if (expr[i] == '\0') break;//in case there are multiple 0s at the end
		if ((expr[i] > '9' || expr[i] < '0')&& isspace(expr[i + 1]))
		{//is an operator
			item p;
			p.oprtr = expr[i];
			p.count = 0;
			items.push(p);
			i++;
		}
		else
		{
			int j = i;
			while (expr[j] != '\0' && !isspace(expr[j]))j++;			
			operand = stof(expr.substr(i, j - i));
			i = j;
			while (!items.empty())
			{
				if (items.top().count == 0)
				{
					items.top().operand = operand;
					items.top().count++;
					break;
				}
				else
				{//there is already an operand within the operator
					float temp = items.top().operand;
					operand = cal(items.top().oprtr, temp, operand);//store the res back to operand
					items.pop();//delete the operator that has been calculated
				}
			}
			
		}
		
		
	}
	
	return operand;
}

int main()
{	
	cout << "----- Evaluate Prefix Expression -----" << endl << endl;

	ifstream infile("prefix_expr.txt");
	if (!infile.is_open())
	{
		cout << "Error: cannot open prefix_expr.txt" << endl;
		system("pause");
		exit(0);
	}

	string prefix_expr;
	while (getline(infile, prefix_expr))
	{		
		double value = evaluate_prefix(prefix_expr);
		cout << "prefix expression: " << prefix_expr << " = " << value << endl << endl;
	}
	infile.close();

	system("pause");
	exit(0);
}