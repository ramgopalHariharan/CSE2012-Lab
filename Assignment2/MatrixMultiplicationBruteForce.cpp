#include<iostream>
#include<cstdlib>

using namespace std;

int multCount = 0;

void input(int a[][20], int n) {
	cout<<"Enter elements : \n";
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cin>>a[i][j];
		}
	}
}

void generateMatrix(int a[][20], int n) {
	cout<<"\nGenerating Matrix Elements...\n";
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			a[i][j] = rand() % 10;
		}
	}
}

void display(int a[][20], int n) {
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout<<a[i][j]<<' ';
		}
		cout<<endl;
	}
}

void MatMulBruteForce(int a[][20], int b[][20], int n) {
	int c[n][20];
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			c[i][j] = 0;
			for(int k=0;k<n;k++) {
				multCount++;
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
	display(c, n);
}


int main() {
	cout<<"Brute Force Multiplication: \n\n";
	int a[20][20], b[20][20], c[20][20], n;
	n = 4;
//	cout<<"Enter Dimension of Square Matrrices: "; cin>>n;
//	input(a, n);
//	input(b, n);
	generateMatrix(a, n);
	generateMatrix(b, n);
	cout<<"\nMatrix A: \n"; display(a, n);
	cout<<"\nMatrix B: \n"; display(b, n);
	cout<<"\nMatrix C: \n";
	MatMulBruteForce(a, b, n);
	cout<<"Multiplication Count = "<<multCount<<endl;
	return 0;
}
