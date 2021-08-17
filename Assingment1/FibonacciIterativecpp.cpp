#include<iostream>

using namespace std;

int main() {
	int n;
	cout<<"Enter n: ";
	cin>>n;
	//Initialice f(0) and f(1) as a and b	
	//c = f(n)
	int a = 0, b = 1, c=0;
	//Loop from 2 to n
	for(int i=2;i<=n;i++) {
		//set f(n) as sum of f(n-1) and f(n-2)
		c = a + b;
		//update f(n-1) and f(n-2)
		a = b;
		b = c;
	}
	cout<<"F(n) = "<<c;
	return 0;
}


