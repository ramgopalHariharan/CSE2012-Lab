// C++ program to get maximum and minimum
// values of an expression
#include <iostream>
#include<vector>
using namespace std;
// method prints minimum and maximum value
// obtainable from an expression
void MinAndMaxValueOfExpDP(char exp[])
{
	int n;
	vector<int> num;
	vector<char> opr;
	int tmp = 0;
	//Calculate size of expression
	for(n=0;exp[n]!='\0';n++);
	// store operator and numbers in different vectors
	for (int i = 0; i < n; i++)
	{
		if (exp[i] == '+' || exp[i] == '-')
		{
			//Push the operator
			opr.push_back(exp[i]);
			//Convert the number string to an int and push it
			num.push_back(tmp);
			//reset the number string
			tmp = 0;
		}
		else
		{
			tmp*=10;
			//add the digit to the number string
			tmp += (exp[i]-48);
		}
	}
	// storing last number in vector
	num.push_back(tmp);

	//len = number of numbers in expression
	int len = num.size();
	int minVal[len][len];
	int maxVal[len][len];

	// initializing minval and maxval 2D array
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			minVal[i][j] = INT_MAX;
			maxVal[i][j] = -INT_MAX;

			// initializing main diagonal by num values
			if (i == j)
				minVal[i][j] = maxVal[i][j] = num[i];
		}
	}

	// Looping similar to matrix chain multiplication
	// and updating both 2D arrays
	for (int x = 2; x < len+1; x++) //x is size of updatable window
	{
		//i is current row
		for (int i = 0; i < len - x + 1; i++)
		{
			int j = i + x - 1;
			//j is current column
			for (int k = i; k < j; k++)
			{
				int minTmp = INT_MAX, maxTmp = -INT_MAX;
				// if current operator is '+', updating tmp
				// variable by addition
				if(opr[k] == '+')
				{
					minTmp = minVal[i][k] + minVal[k + 1][j];
					maxTmp = maxVal[i][k] + maxVal[k + 1][j];
				}

				// if current operator is '-', updating tmp
				// variable by subtraction
				else if(opr[k] == '-')
				{
					minTmp = minVal[i][k] - minVal[k + 1][j];
					maxTmp = maxVal[i][k] - maxVal[k + 1][j];
				}

				// updating array values by tmp variables
				if (minTmp < minVal[i][j])
					minVal[i][j] = minTmp;
				if (maxTmp > maxVal[i][j])
					maxVal[i][j] = maxTmp;
			}
		}
	}

	// last element of first row will store the result
	cout << "Minimum value : " << minVal[0][len - 1]
		<< ", Maximum value : " << maxVal[0][len - 1];
}

// Driver code to test above methods
int main()
{
	cout<<"Name: Ramgopal Hariharan\nReg No: 20BCE0249\n\n";
	char expression[100];
	cout<<"Enter the expression: ";
	cin>>expression;
	MinAndMaxValueOfExpDP(expression);
	return 0;
}
