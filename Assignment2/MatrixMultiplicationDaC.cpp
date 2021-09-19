#include<iostream>
#include <stdlib.h>

using namespace std;

int multCount = 0;

void input(int[][20], int);
void display(int[][20], int);
void MatMulDaC(int[][20], int[][20], int[][20], int, int, int, int, int);
void MatAdd(int[][20], int[][20], int[][20], int, int, int);
void generateMatrix(int[][20], int);

int main() {
	cout<<"Divide and Conquer: \n\n";
	int a[20][20], b[20][20], c[20][20];
	int n=4;
	generateMatrix(a, n);
	generateMatrix(b, n);
//	cout<<"Enter Size of matrices: "; cin>>n;
//	input(a, n);
//	input(b, n);
	MatMulDaC(a, b, c, 0, 0, 0, 0, n);
	cout<<"A "; display(a, n);
	cout<<"B "; display(b, n);
	cout<<"C "; display(c, n);
	cout<<"Multiplication Count = "<<multCount<<endl;
	return 0;
}

//Multiplies parts of two matrices a and b with left top corners at a[i1, j1] and b[i2, j2]
// and places the result in c 
void MatMulDaC(int a[][20], int b[][20], int c[][20], int i1, int j1, int i2, int j2, int n) {
	//Base Case when n<=2, do brute force method
	if(n<=2) {
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				c[i][j] = 0;
				for(int k=0;k<n;k++) {
					multCount++;
					c[i][j] += a[i+i1][k+j1] * b[k+i2][j+j2];
				}
			}
		}
	}
	else {
		int d1[20][20], d2[20][20];
		
		//Calculating C[1][1] 
		MatMulDaC(a, b, d1, 0, 0, 0, 0, n/2);
		MatMulDaC(a, b, d2, 0, n/2, n/2, 0, n/2);
		MatAdd(d1, d2, c, 0, 0, n/2);
		
		//Calculating C[1][2] 
		MatMulDaC(a, b, d1, 0, 0, 0, n/2, n/2);
		MatMulDaC(a, b, d2, 0, n/2, n/2, n/2, n/2);
		MatAdd(d1, d2, c, 0, n/2, n/2);
		
		//Calculating C[2][1] 
		MatMulDaC(a, b, d1, n/2, 0, 0, 0, n/2);
		MatMulDaC(a, b, d2, n/2, n/2, n/2, 0, n/2);
		MatAdd(d1, d2, c, n/2, 0, n/2);
		
		//Calculating C[2][2] 
		MatMulDaC(a, b, d1, n/2, 0, 0, n/2, n/2);
		MatMulDaC(a, b, d2, n/2, n/2, n/2, n/2, n/2);
		MatAdd(d1, d2, c, n/2, n/2, n-n/2);
	}	
}

//Function to add a and b and place it in the part of c with left corner at vertex (i3, j3)
void MatAdd(int a[][20], int b[][20], int c[][20], int i3, int j3, int n) {
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			c[i+i3][j+j3] = a[i][j] + b[i][j];
		}
	}
}

void input(int a[][20], int n) {
	cout<<"Enter elements: \n";
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
	cout<<"Matrix: \n";
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout<<a[i][j]<<' ';
		}
		cout<<endl;
	}
}
