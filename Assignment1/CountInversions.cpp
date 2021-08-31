#include<iostream>

using namespace std;

int main() {
	int array[100], n, count = 0;
	cout<<"Enter No of elements: ";
	cin>>n;
	cout<<"Enter Elements: ";
	for(int i=0;i<n;i++) cin>>array[i];
	
	//Loop throught the array
	for(int i=0;i<n-1;i++) {
		for(int j=i+1;j<n;j++) {
			//Check the number of elements that are less than the current element for each element
			if(array[i]>array[j]) {
				count++;
				printf("(%d, %d)\n", array[i], array[j]);
			}
			
		}
	}
	cout<<"Inversion Count = "<<count;
}
