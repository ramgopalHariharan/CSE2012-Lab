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


