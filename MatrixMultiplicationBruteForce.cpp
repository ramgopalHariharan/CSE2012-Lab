#include<iostream>
#include<cstdlib>

using namespace std;

void input(int a[][10], int n) {
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cin>>a[i][j];
		}
	}
}

void generateMatrix(int a[][10], int n) {
	cout<<"\nGenerating Matrix Elements...\n";
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			a[i][j] = rand() % 10;
		}
	}
}

void display(int a[][10], int n) {
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout<<a[i][j]<<' ';
		}
		cout<<endl;
	}
}

void MatMulBruteForce(int a[][10], int b[][10], int n) {
	int c[n][10];
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			c[i][j] = 0;
			for(int k=0;k<n;k++) {
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
	display(c, n);
}


int main() {
	int a[10][10], b[10][10], c[10][10], n;
	n = 5;
//	cout<<"Enter Dimension of Square Matrrices: "; cin>>n;
	generateMatrix(a, n);
	generateMatrix(b, n);
	cout<<"\nMatrix A: \n"; display(a, n);
	cout<<"\nMatrix B: \n"; display(b, n);
	cout<<"\nMatrix C: \n";
	MatMulBruteForce(a, b, n);
	return 0;
}
