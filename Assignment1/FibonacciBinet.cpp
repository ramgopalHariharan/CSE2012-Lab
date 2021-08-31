#include<iostream>
#include<cmath>
//Define roots of the equation
#define root1 ((1+sqrt(5))/2)
#define root2 ((1-sqrt(5))/2)

using namespace std;

int main() {
	float term1 = 1, term2 = 1;
	cout<<"Enter n: ";
	int n; cin>>n;
	//Raise roots to the nth power using repeated multiplication
	//this gives the algorithm a time complexity of O(n)
	for(int i=0;i<n;i++) {
		term1 *= root1;
		term2 *= root2;
	}
	//Calculate final value using Binet's formula
	float f = (term1 - term2) / sqrt(5);
	cout<<"F(n) = "<<f;
	return 0;
}


