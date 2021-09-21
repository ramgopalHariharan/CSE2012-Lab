#include<iostream>

using namespace std;

//Returns maximum of two integers
int max(int x, int y) {
	return (x>y)? x : y;
}

//Returns LCS of a[0...n-1] and b[0...m-1] strings
int LCS(char a[], char b[], int n, int m) {
	int DP[n+1][m+1];
	char lcs[20];
	for(int i=0;i<=n;i++) {
		DP[i][0] = 0;
	}
	for(int j=0;j<=m;j++) {
		DP[0][j] = 0;
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(a[i-1]==b[j-1]) DP[i][j] = DP[i-1][j-1] + 1;
			else DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
		}
	}
	
	cout<<endl;
	for(int i=-1;i<=n;i++) {
		for(int j=-1;j<=m;j++) {
			if(i+j==-2) cout<<"  ";
			else if(i+j==-1) cout<<"  ";
			else if(i==-1) cout<<b[j-1]<<' ';
			else if(j==-1) cout<<a[i-1]<<' ';
			else cout<<DP[i][j]<<' ';
		}
		cout<<endl;
	}
	cout<<endl;
	int k = DP[n][m];
	lcs[k] = '\0'; k--;
	for(int j=m, i=n;j>0;j--) {
		if(DP[i][j] == DP[i-1][j-1] + 1){
			lcs[k] = a[i-1];
			i--;
			k--;
		}	
	}
	
	cout<<"Longest Common Substring: "<<lcs<<endl;
	return DP[n][m]; 
}

int main() {
	cout<<"LCS By Dynamic Programming\nRamgopal Hariharan\n20BCE0249\n\n";
	char C[20];
	char T[20];
	int m, n;
	cout<<"Enter String 1(Content): ";
	scanf("%20s", C);
	cout<<"Enter String 2(Text): ";
	scanf("%20s", T);
	for(n=0;C[n]!='\0';n++);
	for(m=0;T[m]!='\0';m++);
	int L = LCS(C, T, n, m);
	cout<<"Length of Longest Common Substring: "
		<<L<<endl;
	cout<<"Plagiarism Percentage: "<<(float)(L*100)/m<<endl;
	return 0;
}
