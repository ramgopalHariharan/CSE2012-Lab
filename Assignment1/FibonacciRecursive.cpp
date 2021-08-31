#include<iostream>

using namespace std;

int fibonacciRecursive(int n) {
	//Base Cases when n=0 and n=1
	if(n==0) return 0;
	if(n==1) return 1;
	//Retruns sum of two previuos terms recursively
	return (fibonacciRecursive(n-1) + fibonacciRecursive(n-2));
}

int main() {
	cout<<"Enter n: ";
	int n; cin>>n;
	cout<<"F(n) = "<<fibonacciRecursive(n);
	return 0;
}


