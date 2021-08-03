/*
Ramgopal Hariharan
20BCE0249
ramgopal.hariharan2020@vitstudent.ac.in
*/

//Factorial Using Recursion

#include<iostream>

using namespace std;

long factorial(int number) {
	if(number==1) return 1;
	else return number*factorial(number-1);
}

int main() {
	int x;
	cout<<"Enter Number:";
	cin>>x;
	cout<<"Factorial of x: "<<factorial(x);
	return 0; 
}
