#include<iostream>
#include<vector>

using namespace std;

int main() {
	int array[100], n, count = 0;
	cout<<"Enter No of elements: ";
	cin>>n;
	cout<<"Enter Elements: ";
	for(int i=0;i<n;i++) cin>>array[i];
	for(int i=0;i<n-1;i++) {
		for(int j=i+1;j<n;j++) {
			if(array[i]>array[j]) {
				count++;
				printf("(%d, %d)\n", array[i], array[j]);
			}
			
		}
	}
	cout<<"Inversion Count = "<<count;
}
