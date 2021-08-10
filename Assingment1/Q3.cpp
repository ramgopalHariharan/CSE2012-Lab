#include<iostream>

using namespace std;

int findPoint(int a[], int n, bool order) {
	int i=0;
	if(order) {
		while(a[i]>a[i+1]) i++;
	}
	else {
		while(a[i]<a[i+1]) i++;
	}
	int split = i;
	if(order) {
		while(i<n) {
			if(a[i]>a[i+1]) return -1;
			i++;
		}
	}
	else {
		while(i<n) {
			if(a[i]<a[i+1]) return -1;
			i++;
		}
	}
	return split;
}

int main() {
	int array[100], n;
	cout<<"Enter No of elements: ";
	cin>>n;
	cout<<"Enter Elements: ";
	for(int i=0;i<n;i++) cin>>array[i];
	int split = findPoint(array, n, array[0]>array[1]);
	if(split == -1) {
		cout<<"No Point found";
	}
	else {
		cout<<"Split point = "<<split;
	}
}
