/*
Ramgopal Hariharan
20BCE0249
ramgopal.hariharan2020@vitstudent.ac.in
*/

//kth smallest and kth largest element

#include<iostream>
#define MAXSIZE 100

using namespace std;

void input(int a[], int& n) {
	cout<<"Enter Number of elements: ";
	cin>>n;
	if(n>MAXSIZE) {
		cout<<"Array size too large\n";
		input(a, n);
	}
	cout<<"Enter Array elements: ";
	for(int i=0;i<n;i++) {
		cin>>a[i];
	}
}

int main() {
	int k;
	int n, a[MAXSIZE];
	input(a, n);
	cout<<"Enter value of k: ";
	cin>>k;
	if(k<1 || k>n) {
		cout<<"Invalid Value of k!";
		return 1;
	}
	for(int i=0;i<n-1;i++) {
		int x = i;
		for(int j=i+1;j<n;j++) {
			if(a[j]<a[x]) {
				x=j;
			}
			int t = a[x];
			a[x] = a[i];
			a[i] = t;
		};
	}
	cout<<k<<"th smallest element = "<<a[k-1]<<endl;
	cout<<k<<"th largest element = "<<a[n-k]<<endl;
	cout<<endl;
	
}
