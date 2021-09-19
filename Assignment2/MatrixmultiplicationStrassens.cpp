#include<iostream>
#include<cstdlib>

using namespace std;

int multCount = 0;

void input(int[][20], int);
void display(int[][20], int);
void generateMatrix(int[][20], int);
void MatMulStrassens(int[][20], int[][20], int[][20], int, int, int, int, int);
void MatAdd(int[][20], int[][20], int[][20], int, int, int, int,int, int, int);
void MatSub(int[][20], int[][20], int[][20], int, int, int, int,int, int, int);

int main() {
	cout<<"Strassens Algorithm: \n\n";
	int a[20][20], b[20][20], c[20][20];
	int n=4;
	generateMatrix(a, n);
	generateMatrix(b, n);
//	cout<<"Enter Size of matrices: "; cin>>n;
//	input(a, n);
//	input(b, n);
	MatMulStrassens(a, b, c, 0, 0, 0, 0, n);
	
	cout<<"A "; display(a, n);
	cout<<"B "; display(b, n);
	cout<<"C "; display(c, n);
	
	cout<<"Multiplication Count = "<<multCount<<endl;
	return 0;
}

//Multiplies parts of two matrices a and b with left top corners at a[i1, j1] and b[i2, j2]
// and places the result in c 
void MatMulStrassens(int a[][20], int b[][20], int c[][20], int i1, int j1, int i2, int j2, int n) {
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
		int p[20][20], q[20][20], r[20][20], s[20][20], t[20][20], u[20][20], v[20][20];
		
		//p = (a11 + a22)(b11 + b22)
		MatAdd(a, a, d1, 0, 0, n/2, n/2, 0, 0, n/2);
		MatAdd(b, b, d2, 0, 0, n/2, n/2, 0, 0, n/2);
		MatMulStrassens(d1, d2, p, 0, 0, 0, 0, n/2);
		
		//q = (a21 + a22)b11
		MatAdd(a, a, d1, n/2, 0, n/2, n/2, 0, 0, n/2);
		MatMulStrassens(d1, b, q, 0, 0, 0, 0, n/2);
		
		//r = a11(b12 - b22)
		MatSub(b, b, d2, 0, n/2, n/2, n/2, 0, 0, n/2);
		MatMulStrassens(a, d2, r, 0, 0, 0, 0, n/2);
		
		//s = a22(b21-b11)
		MatSub(b, b, d2, n/2, 0, 0, 0, 0, 0, n/2);
		MatMulStrassens(a, d2, s, n/2, n/2, 0, 0, n/2);
		
		//t = (a11 + a12)b22
		MatAdd(a, a, d1, 0, 0, 0, n/2, 0, 0, n/2);
		MatMulStrassens(d1, b, t, 0, 0, n/2, n/2, n/2);
		
		//u = (a21 - a11)(b11 + b12)
		MatSub(a, a, d1, n/2, 0, 0, 0, 0, 0, n/2);
		MatAdd(b, b, d2, 0, 0, 0, n/2, 0, 0, n/2);
		MatMulStrassens(d1, d2, u, 0, 0, 0, 0, n/2);
		
		//v = (a12 - a22)(b21 + b22)
		MatSub(a, a, d1, 0, n/2, n/2, n/2, 0, 0, n/2);
		MatAdd(b, b, d2, n/2, 0, n/2, n/2, 0, 0, n/2);
		MatMulStrassens(d1, d2, v, 0, 0, 0, 0, n/2);
		
		//c11 = p + s - t + v
		MatAdd(p, s, d1, 0, 0, 0, 0, 0, 0, n/2);
		MatSub(d1, t, d2, 0, 0, 0, 0, 0, 0, n/2);
		MatAdd(d2, v, c, 0, 0, 0, 0, 0, 0, n/2);
		
		//c12 = r + t
		MatAdd(r, t, c, 0, 0, 0, 0, 0, n/2, n/2);
		
		//c21 = q + s
		MatAdd(q, s, c, 0, 0, 0, 0, n/2, 0, n/2);
		
		//c22 = p + r - q + u
		MatAdd(p, r, d1, 0, 0, 0, 0, 0, 0, n/2);
		MatSub(d1, q, d2, 0, 0, 0, 0, 0, 0, n/2);
		MatAdd(d2, u, c, 0, 0, 0, 0, n/2, n/2, n/2);
	}	
}

//Adds parts of two matrices a and b with left top corners at a[i1, j1] and b[i2, j2]
//and places the result in c part with top left corner c[i3, j3]
void MatAdd(int a[][20], int b[][20], int c[][20], int i1, int j1, int i2, int j2,int i3, int j3, int n) {
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			c[i+i3][j+j3] = a[i+i1][j+j1] + b[i+i2][j+j2];
		}
	}
}

//Subtracts parts of two matrices a and b with left top corners at a[i1, j1] and b[i2, j2]
//and places the result in c part with top left corner c[i3, j3]
void MatSub(int a[][20], int b[][20], int c[][20], int i1, int j1, int i2, int j2,int i3, int j3, int n) {
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			c[i+i3][j+j3] = a[i+i1][j+j1] - b[i+i2][j+j2];
		}
	}
}

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
	cout<<"Matrix Elements: \n";
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout<<a[i][j]<<' ';
		}
		cout<<endl;
	}
}
