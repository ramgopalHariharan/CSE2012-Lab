#include<iostream>
#include<cstdlib>

using namespace std;

//Recursively find the Minimum element using Divide and Conquer
int MinDaC(int a[], int start, int end, int& count) {
	count++;
	//When the array size is one, retrun the element
	if(start == end) {
		return a[start];
	}
	else {
		int mid = (end-start)/2;
		//Split the arrray into left and right sub arrays 
		//and find the minimum of each sub array
		int left = MinDaC(a, start, start+mid, count);
		int right = MinDaC(a, start+mid + 1, end, count);
		//return the overall minimum of left and right sub arrays
		int min = (left <= right)? left:right;
		count++;
		return min;
	}
}

//Recursively find the Maximum element using Divide and Conquer
int MaxDaC(int a[], int start, int end, int& count) {
	count++;
	//When the array size is one, retrun the element
	if(start == end) {
		return a[start];
	}
	else {
		int mid = (end-start)/2;
		//Split the arrray into left and right sub arrays 
		//and find the maximum of each sub array
		int left = MaxDaC(a, start, start+mid, count);
		int right = MaxDaC(a, start+mid + 1, end, count);
		//return the overall maximum of left and right sub arrays
		int max = (left >= right)? left:right;
		count++;
		return max;
	}
}

//Call both min and max DaC functions, in constant time
int MinMaxDaC(int a[], int n) {
	int count = 0;
	int min = MinDaC(a, 0, n-1, count);
	int max = MaxDaC(a, 0, n-1, count);
	cout<<"Minimum Element: "<<min<<endl;
	cout<<"Maximum Element: "<<max<<endl;
	cout<<"Number of Comparisons = "<<count<<endl;
}

void GenerateArray(int a[], int n) {
	for(int i=0;i<n;i++) {
		a[i] = rand() % 900 + 100;
	}
}

void Display(int a[], int n) {
	cout<<"Array: \n";
	for(int i=0;i<n;i++) cout<<a[i]<<' ';
	cout<<endl;
}

int main() {
	cout<<"Enter Number of elements: ";
	int n, a[10000];
	cin>>n;
	GenerateArray(a, n);
	Display(a, n);
	MinMaxDaC(a, n);
	return 0;
}
