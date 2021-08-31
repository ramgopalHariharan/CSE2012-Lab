#include<iostream>

using namespace std;

void Input(char* a, char* b, int& n1, int& n2) {
	cout<<"Enter a: "; scanf("%10s", a);
	cout<<"Enter b: "; scanf("%10s", b);
	for(n1=0;*a != '\0';n1++, a++);
	for(n2=0;*b != '\0';n2++, b++);
}

void shiftRight(char a[], int& n) {
	for(int i=n-1;i>=0;i--) {
		a[i+1] = a[i];
	}
	a[0] = '0';
	a[n+1] = '\0';
	n++;
}

//Pads the shorter binary String with Extra Leading Zeroes and returns the final length
//as Karatsubas algorithm is to be applied on numbers with an equal number of digits
int CorrectDigits(char a[], char b[], int& n1, int& n2) {
	if(n1==n2) return n1;
	while(n1>n2) {
		shiftRight(b, n2);
	}
	while(n2>n1) {
		shiftRight(a, n1);
	}
	return n1;
}

int Karatsuba(int x, int y) {
	
	//Base Case if either of the numbers has only 1 bit, 
	//normal multiplication is done
	if(x<2 || y<2) {
		return x*y;
	}
	//Calculate teh number of bits in each number using Left Shift operator
	int n1=1, n2=1;
	for(int i=x;i>1;i>>=1, n1++);
	for(int i=y;i>1;i>>=1, n2++);
	//Set n to be the length of the longer number
	int n = (n1>n2)? n1:n2;
	//Split the bit strings approximatelyy in half,
	//so that recursive calls can be made on nubers of n/2 digits
	int m = n/2;
	//a = first half of first number
	//b = second half of first number
	//c = first half of second number
	//d = second half of second number
	int a = x>>(m), b = x & ((1<<(m)) - 1), c = y>>(m), d = y & ((1<<(m)) - 1);
	//Recursive Call 1 to calculate a*c 
	int z2 = Karatsuba(a, c);
	//Recursive Call 2 to calculate b*d
	int z0 = Karatsuba(b, d);
	//Recursive Call 3 to calculate 
	//ab + cd = (a+b)*(c+d) - a*b - c*d 
	int z1 = Karatsuba(a+b, c+d) - z2 - z0;
	//Since base is 2 [Binary], 
	//Answer = z2 * 2^(n) + z1 * 2^(n/2) + z3
	//accomplished here using left shift operator
	z2 <<= 2*m;
	z1 <<= m;
	int ans = z2 + z1 + z0;
	//Return answer
	return ans;
	
}

//Convert Binary String to decimal Number
int BinToDec(char a[], int n) {
	int x = 0;
	for(int i=0;i<n;i++) {
		//If digit is 0, add 0 to x else add 1 to x
		x += (0 | (a[i] - 48)) ;
		//left shift x by 1 to add the next digit
		x <<=1;
	}
	//Remove the extra left shift
	x >>= 1;
	return x;
}

//Converts Integer to it's Binary String
char* DecToBin(int x) {
	char a[21];
	int n = 1;
	for(int i = x;i>1;i >>= 1, n++);
	for(int i = x, j = n-1;j>=0;i>>=1, j--) {
		a[j] = char((1 & i) + 48);
	}
	a[n] = '\0';
	return a;
}

int main() {
	char a[10];
	char b[10];
	int n1, n2, n;
	//Input Numbers as Binary Strings
	Input(a, b, n1, n2);
	//Make Sure that the strings are of Equal Length
	//and contain only zeroes and ones
	n = CorrectDigits(a, b, n1, n2);
	//Convert the binary strings to decimal numbers
	//(Arithmetic will still be done on the binary representations using shift operators)
	int x = BinToDec(a, n);
	int y = BinToDec(b, n);
	//Multiply using Karatsubas Algorithm and Convert the result back to a Binary String
	char* ans = DecToBin(Karatsuba(x, y));
	cout<<"Answer: "<<ans<<endl;
	return 0;
}
