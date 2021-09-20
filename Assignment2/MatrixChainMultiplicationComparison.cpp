#include<iostream>
#include<time.h>
#include<cstdlib>
#define N 5

using namespace std;

int multCount = 0;

void MatMul(int[][40], int[][40], int[][40], int, int, int);

void generateMatrix(int a[][40], int m, int n) {
	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++) {
			a[i][j] = rand()%2;
		}
	}
}

void display(char* name, int a[][40], int m, int n) {
	printf("\nMatrix %s: \n\n", name);
	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++) {
			cout<<a[i][j]<<' ';
		}
		cout<<endl;
	}
}

int main() {
	int M0[40][40], M1[40][40], M2[40][40], M3[40][40], M4[40][40], Result[40][40];
	//make Matrices with given dimensions
	generateMatrix(M0, 40, 25);
	generateMatrix(M1, 25, 40);
	generateMatrix(M2, 40, 30);
	generateMatrix(M3, 30, 5);
	generateMatrix(M4, 5, 30);
	//Display the matrices
	display("M0", M0, 40, 25);
	display("M1", M1, 25, 40);
	display("M2", M2, 40, 30);
	display("M3", M3, 30, 5);
	display("M4", M4, 5, 30);
	//Multiplying Brute Force Method
//	cout<<"Brute Force Method: \n";
//	MatMul(M0, M1, Result, 40, 25, 40);
//	MatMul(Result, M2, Result, 40, 40, 30);
//	MatMul(Result, M3, Result, 40, 30, 5);
//	MatMul(Result, M4, Result, 40, 5, 30);
//	
//	display("Result", Result, 40, 30);
//	cout<<"Multiplications: "<<multCount<<endl;
//	multCount = 0;
	
	//multiply using the parentises ((M0*(M1*(M2*M3)))*M4)
//	cout<<"\nUsing Generated parentheses ((M0*(M1*(M2*M3)))*M4) : \n";
//	MatMul(M2, M3, Result, 40, 30, 5);
//	MatMul(M1, Result, Result, 25, 40, 5);
//	MatMul(M0, Result, Result, 40, 25, 5);
//	MatMul(Result, M4, Result, 40, 5, 30);
//	
//	display("Result", Result, 40, 30);
//	cout<<"Multiplications: "<<multCount<<endl;
	return 0;
}

//Multiply Matrices a and b and plce in c
//a and b are d1xd2 and d2xd3 matrices respectively
void MatMul(int a[][40], int b[][40], int c[][40], int d1, int d2, int d3) {
	int d[40][40];
	for(int i=0;i<d1;i++) {
		for(int j=0;j<d3;j++) {
			d[i][j] = 0;
			for(int k=0;k<d2;k++) {
				multCount++;
				d[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	for(int i=0;i<d1;i++) {
		for(int j=0;j<d3;j++) {
			c[i][j] = d[i][j];
		}
	}
}
