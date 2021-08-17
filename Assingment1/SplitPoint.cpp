#include<iostream>

using namespace std;

//Both functions return value of splitting point k if found
// else they return -1

//Check whether it increases and then decreases
int ascendingFindPoint(int a[], int n) {
	int i=0, j=n-1;
	//check if array is in ascending order from both sides
	while(a[i]<a[i+1]) i++;
	while(a[j]<a[j-1]) j--;
	if (i == j) return i;
	else return -1;
}

//Check whether array decreases and then increases
int descendingFindPoint(int a[], int n) {
	int i=0, j=n-1;
	//Check whether array is in descending order from both sides
	while(a[i]>a[i+1]) i++;
	while(a[j]>a[j-1]) j--;
	if (i == j) return i;
	else return -1;
}

int main() {
	int array[100], n;
	cout<<"Enter No of elements: ";
	cin>>n;
	cout<<"Enter Elements: ";
	for(int i=0;i<n;i++) cin>>array[i];
	int split = ascendingFindPoint(array, n);
	//if one of the functions return -1, check the other function
	if(split == -1) {
		split = descendingFindPoint(array, n);
		//if both return -1, No value of k is found
		if(split == -1) {
			cout<<"No Split Point (k) Found";
		}
		else {
			cout<<"Split point k = "<<split;
		}
	}
	else {
		cout<<"Split point k = "<<split;
	}
}
