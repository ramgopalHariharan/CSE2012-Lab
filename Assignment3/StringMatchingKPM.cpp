#include<iostream>
#include<chrono>
#include<ctime>

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
int StringMatchKMP(char t[], char p[], int n, int m) {
	int f[m];
	FailureFunction(f, p, m);
	int i=0;
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
				j = f[j-1]
		//move the while window 1 character if first character of p doesnt match
			else 
				i++;
	}
	//retrun -1 if no match found
	return -1;
}

int main() {
	char T[500], P[20];
	int n=0, m=0;
	//input strings
	cout<<"Enter T: ";
	scanf("%[^\n]500s", T);
	cout<<"Enter P: "; scanf("\n");
	scanf("%[^\n]20s", P);
	//Calculate String lengths
	for(;T[n]!='\0';n++); for(;P[m]!='\0';m++);
	S.reset();
	int index = StringMatchNaiive(T, P, n, m);
	if(index != -1) cout<<"Pattern Found at index: "<<index<<endl;
	else cout<<"Pattern not Found!\n";
	cout<<"Elapsed Time: "<<S.getTime() / 1000<<" ms\n";
	return 0;
}


