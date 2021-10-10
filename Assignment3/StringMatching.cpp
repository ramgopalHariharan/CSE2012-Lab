#include<iostream>
#include<chrono>
#include<ctime>
#include<cmath>

using namespace std::chrono;

//Stopwatch class for measuring execution time
class Stopwatch
{
private:
    steady_clock::time_point start;
    
public:
    Stopwatch(){
        reset();
    }
    
    ~Stopwatch(){}
    
    // Start the clock
    void reset(){ start = steady_clock::now(); }
    
    // Read time elapsed in nanoseconds
    double getTime(){
        return duration<double, std::nano>(steady_clock::now() - start).count();
    }
};

using namespace std;

Stopwatch S;

//Calculating Failure Function to be used in 
//the KMP String Matching Algorithm
void FailureFunction(int f[], char p[], int m) {
	f[0] = 0;
	int i=1, j=0;
	while(i<m) {
		if(p[i] == p[j]) {
			f[i++] = ++j;
		}
		else if(j>0) {
			j = f[j-1];
		}
		else {
			f[i++] = 0;
		}
	}
}

//Naiive String matching algorithm
int StringMatchNaiive(char t[], char p[], int n, int m) {
//	Moves the matching window from the start to the end of the string
	for(int i=0;i<n-m+1;i++) {
		int j = 0;
		//checks if the text in the window matches teh patern
		while(j<m &&  t[i+j] == p[j]) j++;
		//if pattern match is foound, rreutrn the starting index
		if(j==m) {
			return i;
		}
	}
	//if no match is found return -1
	return -1;
}

//KMP String matching algorithm
int StringMatchKMP(char t[], char p[], int n, int m) {
	int f[m];
	int i=0, j=0;
	FailureFunction(f, p, m);
	while(i<n) {
		if(t[i]==p[j]) 
		//Whole pattern matched
			if (j==m-1) 
				return i-j;
		//else move to next character in p
			else 
				i++, j++;		
		else 
			if(j>0) 
		//Shift to longetst prefix of P
				j = f[j-1];
		//move the while window 1 character if first character of p doesnt match
			else 
				i++;
	}
	//retrun -1 if no match found
	return -1;
}

int StringMatchRabinKarp(char T[], char P[], int n, int m, int q, int d=256) {
	long int h =(long int)pow(d, m-1) % q;
	long int p=0;
	long int t=0;
	//Calculates the first window value and the value for the pattern string
	for(int i=0;i<m;i++) {
		p = (d*p + P[i]) % q;
		t = (d*t + T[i]) % q;
	}
	for(int s=0;s<n-m;s++) {
		//if vale is same, 
		if(p==t) {
			int f=1;
			//Check if string is same to avoid spurious matches
			for(int j=0;j<m;j++) {
				if(P[j] != T[s+j])
					f=0;
			}
			if(f==1) return s;
		}
		//Else move the window by subtracting previous character and adding next character
		if(s<n-m) {
			t = (long int)(d*(t-T[s+1]*h) + T[s+m+1]) % q;
			if(t<0) t+=q;
		}
	}
	return -1;
}

// Calls all the three algorithms on a single text, pattern pair and stores the value in the table
void CompareAlgorithms(float table[3][3], int i, char T[], char P[], int n, int m) {
	S.reset();
	int index = StringMatchNaiive(T, P, n, m);
	table[i][0] = S.getTime()/1000;
	S.reset();
	index = StringMatchKMP(T, P, n, m);
	table[i][1] = S.getTime()/1000;
	S.reset();
	index = StringMatchRabinKarp(T, P, n, m, 3);
	table[i][2] = S.getTime()/1000;
	S.reset();
}

//Calls the Rabin karp algorithm using the passed prime p andstores teh execution time in the rktable
void CompareRabinKarp(float rktable[], int i, char T[], char P[], int n, int m, int p) {
	S.reset();
	int index = StringMatchRabinKarp(T, P, n, m, p);
	rktable[i] = (float)S.getTime()/1000;
}

int main() {
	//Texts and Patterns to search for are predefined
	char Texts[3][500] = {"Ramgopal Harihaharan", "Register Number 20BCE0249", "Design and Analysis of Algorithms"};
	char Patterns[3][20] = {"Hariharan", "Number", "Analysis of"};
	int primes[3] = {3, 11, 199}; //Primes for rabin karp comparison
	int lengths[3][2] = {20, 9, 25, 6, 33, 11};
	//Table to store execution times of the three algorithms
	float table[3][3], rktable[3] = {0.0, 0.0, 0.0};
	for(int i=0;i<3;i++) {
		CompareAlgorithms(table, i, Texts[i], Patterns[i], lengths[i][0], lengths[i][1]);
		S.reset();
		CompareRabinKarp(rktable, i, Texts[1], Patterns[1], lengths[1][0], lengths[1][1], primes[i]);
	}
	cout<<"Table of execution Times(ns): \n";
	printf("\t%-5s\t%-5s\t%6s\t%-6s\t%6s \n", "n", "m", "Naiive", "KMP", "Rabin Karp");
	for(int i=0;i<3;i++)
		printf("\t%-5d\t%-5d\t%4.2f\t%4.2f\t%4.2f\n", lengths[i][0], lengths[i][1], table[i][0], table[i][1], table[i][2]);
	cout<<"\n\nTable of execution Times for different Prime Numebers in Rabin Karp Alogrithm: \n";
	printf("\t%-5s\t%-5s\t%-5s\t%-6s \n", "n", "m", "Prime", "Time(ns)");
	for(int i=0;i<3;i++) {
		printf("\t%-5d\t%-5d\t%-5d\t%4.2f\n", lengths[1][0], lengths[1][1], primes[i], rktable[i]);
	}
	return 0;
}
