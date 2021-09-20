#include<iostream>
#include<cmath>
#include<cstdlib>
#include<time.h>
#define N 5
#define INF 1000000

using namespace std;

void input(int d[], int n) {
	cout<<"Enter Dimensions: ";
	for(int i=0;i<n;i++) cin>>d[i];
}
void display(int a[][N]) {
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			if(i>j) printf("%-5s ", "-");
			else printf("%-5d ", a[i][j]);
		}
		cout<<endl;
	}
}

void parenthesise(int s[][N], int i, int j) {
	if(i==j) cout<<" M"<<i<<" ";
	else {
		cout<<"(";
		parenthesise(s, i, s[i][j]);
		parenthesise(s, s[i][j]+1, j);
		cout<<")";
	}
}


void MatChainMultiply(int dimensions[], int n) {
	int arr[N][N], s[N][N];
	for(int i=0;i<n;i++) {
		arr[i][i] = 0;
	}
	for(int r=1;r<n;r++) {
		for(int i=0;i<n-r;i++) {
			int j = i+r;
			arr[i][j] = INF;
			for(int k=i;k<j;k++) {
				int q = arr[i][k]+arr[k+1][j]+dimensions[i]*dimensions[k+1]*dimensions[j+1];
				if(arr[i][j] > q) {
					arr[i][j] = q;	
					s[i][j] = k;
				}
				
			}
		}
	}
	display(arr);
	cout<<endl;
	parenthesise(s, 0, N-1);
	cout<<endl;
}

void generateDim(int dimensions[]) {
	srand(time(0));
	for(int i=0;i<N+1;i++) {
		dimensions[i] = (rand()%8 + 1)*5;
	}
}

display(int a[]) {
	for(int i=0;i<N+1;i++) {
		cout<<a[i]<<' ';
	}
	cout<<endl;
}

int main() {
	//N Matrix Chain Requires N+1 Dimensions so that the conditions for multiplication can be satisfied
	int dimensions[N+1];
//	input(dimensions, N+1);
	generateDim(dimensions);
	display(dimensions);
	long product = 0;
	cout<<"No of Multiplications if we brute force Multiply \nwithout parenthisisation = ";
	for(int i=1;i<N;i++) {
		product += dimensions[0]*dimensions[i]*dimensions[i+1];
	}
	cout<<product<<endl;
	MatChainMultiply(dimensions, N);
	return 0;
}


