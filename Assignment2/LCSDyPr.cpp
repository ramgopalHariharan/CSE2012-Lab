#include<iostream>

using namespace std;

void display(int arr[][20], int m, int n, char a[], char b[]) {
	for(int i=0;i<=m+1;i++) {
		for(int j=0;j<=n+1;j++) {
			if(i+j==0 || i+j==1) cout<<' ';
			else if(i==0) cout<<b[j-2];
			else if(j==0) cout<<a[i-2];
			else if(i+j==1) cout<<' ';
			else cout<<arr[i-1][j-1];
			cout<<' ';
		}
		cout<<endl;
	}
}

void LCSDyProg(char a[], char b[], int m, int n, char lcs[]) {
	int arr[20][20];
	for(int i=0;i<m;i++) arr[i][0] = 0;
	for(int j=0;j<n;j++) arr[0][j] = 0;
	for(int i=1;i<=m;i++) {
		for(int j=1;j<=n;j++) {
			if(a[i-1] == b[j-1])
				arr[i][j] = arr[i-1][j-1] + 1;
			else 
				arr[i][j] = (arr[i-1][j] > arr[i][j-1])?arr[i-1][j]:arr[i][j-1];
		}
	}
	cout<<"Array used for Dynamic programming: "<<endl;
	display(arr, m, n, a, b);
	cout<<"Length of LCS : "<<arr[m][n]<<endl;
	int k = 0;
	for(int j=0;j<n;j++) {
		if(arr[m][j] != arr[m][j+1]){
			lcs[k] = b[j];
			k++;
		}	
	}
	lcs[k] = '\0';
}

int main() {
	char a[20], b[20], lcs[20];
	int m, n;
	cout<<"Enter First String: "; cin>>a;
	cout<<"Enter Second String: "; cin>>b;
	for(m=0;a[m];m++);
	for(n=0;b[n];n++);
	LCSDyProg(a, b, m, n, lcs);
	cout<<"Longest Common Substring: "<<lcs<<endl;
	return 0;
}
