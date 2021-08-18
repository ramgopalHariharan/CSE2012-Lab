#include<iostream>
#include<cstdlib>

using namespace std;

void MinMaxIterative(int a[], int n) {
	int max = -32767, min = 327267;
	int count = 0;
	//Loop through all of the elements of the array
	for(int i=0;i<n;i++) {
		count++;
		//If current element is greater than the maximum value, 
		//change the maximum value
		if(a[i] > max) {
			
			max = a[i];
		}
		count++;
		//If current element is lesser than the minimum value,
		//change the minimum value
		if(a[i] < min) {
			
			min = a[i];
		}
	}
	cout<<"Minimum Element = "<<min<<endl;
	cout<<"Maximum Element = "<<max<<endl;
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
	MinMaxIterative(a, n);
	return 0;
}
