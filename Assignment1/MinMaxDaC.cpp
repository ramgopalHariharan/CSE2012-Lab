#include<iostream>
#include<cstdlib>

using namespace std;

void MinMaxDaC(int a[],int i,int j, int& count, int& max, int& min) {
	if (i==j){ max = min = a[i];} //One Element Base Case
	else if (i==j-1) // Two Elements Base Case
    {
    	count++;
        if (a[i] < a[j]) {max = a[j]; min = a[i];}
        else {max = a[i]; min = a[j];}
    }
    else
    {
        // Find where to split the set.
        int max1 = -32767, min1 = 32767;
		int mid = ( i + j )/2;
        // Maximum and Minimum of the two SubProblens
        MinMaxDaC(a, i, mid, count, max, min );
        MinMaxDaC(a, mid+1, j, count, max1, min1 );
        // Combine the solutions of the SubProblems.
        count+=2;
        if (max < max1) max = max1;
        if (min > min1) min = min1;
    }
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
	int min = 32767, max = -32767, count = 0;
	MinMaxDaC(a, 0, n-1, count, max, min);
	cout<<"Maximum Element = "<<max<<endl;
	cout<<"Minimum Element = "<<min<<endl;
	cout<<"Number of Comparisons = "<<count;
	return 0;
}
