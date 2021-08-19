#include<iostream>

using namespace std;

//Multiply the Matrix By [1 1 / 1 0] Square matrix
void Multiply(int f[][2]) {
	int a = f[0][0], b = f[0][1], c = f[1][0], d = f[1][1];
	f[0][0] = a+b;
	f[0][1] = a;
	f[1][0] = c+d;
	f[1][1] = d;
}

//Caluculates F(n) using Knuths algorithm
int FibonacciKnuths(int n) {
	int f[2][2] = {1, 0, 0, 1};
	//Multiply it by the [1 1 / 1 0] square matrix n times
	for(int i=0;i<n;i++) {
		Multiply(f);
	}
	//Return f(n) which is the top right corner element
	//according to knuths algotithm
	return f[0][1];
}

int main() {
	int n;
	cout<<"Enter n: "; cin>>n;
	cout<<"F(n) = "<<FibonacciKnuths(n);
	return 0;
}


