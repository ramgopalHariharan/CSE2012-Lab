/*
Ramgopal Hariharan
20BCE0249
ramgopal.hariharan2020@vitstudent.ac.in
*/

//Quick Sort

#include<iostream>
#define MAXSIZE 10000
#define defaultArray 545, 2, 442, 6, 20, 54, 93, 42, 8, 15, 669, 48
#define defaultSize 12

using namespace std;

void input(int a[], int& n) {
	cout<<"Enter Size of array: "; cin>>n;
	if(n==-1){
		n = defaultSize;
		return;
	}
	cout<<"Enter Array Elements: \n";
	for(int i=0;i<n;i++) {
		cin>>a[i];
	}
	cout<<"\nArray accepted...\n\n";
}

void disp(int a[], int n) {
	cout<<"\nArray A: ";
	for(int i=0;i<n;i++) {
		cout<<a[i]<<' ';
	}
	cout<<endl;
}

void quicksort(int a[],int l, int r) {
	if(r-l <= 0) {
		return;
	}
	int lo = l;
	int hi = r;
	int pivot = a[r];
	while(true) {
		while(a[lo]<pivot) {
			lo++;
		}
		while(hi>0 && a[--hi]>pivot);
		if(lo>=hi) {
			break;	
		}
		else {
			int t = a[lo];
			a[lo] = a[hi];
			a[hi] = t;
		}
	}
	int t = a[lo];
	a[lo] = a[r];
	a[r] = t;
	quicksort(a, l, lo-1);
	quicksort(a, lo+1, r);
}

int main() {
	int a[MAXSIZE] = {defaultArray};
	int n = defaultSize;
	input(a, n);
	disp(a, n);
	cout<<"\nQuick Sorting....\n";
	quicksort(a, 0, n-1);
	disp(a, n);
}

