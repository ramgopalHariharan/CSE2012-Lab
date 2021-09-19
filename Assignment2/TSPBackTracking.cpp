#include<iostream>
#include<cstdlib>
#define INF 9999999.0
#define N 14

using namespace std;

int n = N;
int finalCount = 0;

struct Site {
	char* name;
	int number;
};

void Swap(int& s1, int& s2) {
	int t = s1; s1 = s2; s2 = t;
}

float G [N][N];
Site sites[N];
int trip[N];

void InitializeSites() {
	for(int i=0;i<N;i++) {
		sites[i].number = i;
	}
	sites[0].name = "Pulikuthikal";sites[7].name = "Palagai Kalvettu";
	sites[1].name = "Aruvi";sites[8].name = "Moonukavalai Thottam";
	sites[2].name = "Gd Naidu Museum";sites[9].name = "Soolakkal";
	sites[3].name = "Rajagiri Fort";sites[10].name = "Kamathenu Kalvettu";
	sites[4].name = "Sathikkal";sites[11].name = "Grand Anicut";
	sites[5].name = "Gass Forest Museum";sites[12].name = "Sumaithangikkal";
	sites[6].name = "Konthagai";sites[13].name = "Historical Place";
}

void InitializeGraph() {
	for(int i=0;i<n;i++) {
		for(int j = 0;j<n;j++) {
			if(i==j) G[i][j] = 0;
			else if(i>j) G[i][j] = rand() % 500 + 100;
		}	
	}
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			if(i<j) G[i][j] = G[j][i];
		}
	}
}

void displayFinalTrip(int A[N], int l) {
	cout<<"START->";
	for(int i=0;i<l;i++) {
		cout<<sites[A[i]].name<<"->";
	}
	if(l==N)
		cout<<sites[A[0]].name<<"->";
	cout<<"END"<<endl;
}

void displayTrip(int A[N], int l) {
	cout<<"START->";
	for(int i=0;i<l;i++) {
		cout<<A[i]<<"->";
	}
	if(l==N)
		cout<<A[0]<<"->";
	cout<<"END"<<endl;
}

void displayGraph() {
	cout<<"Distance Graph : \n";
	for(int i=0;i<N+1;i++) {
		for(int j=0;j<N+1;j++) {
			if(i==0) printf("%-6d ", j);
			else if(j==0) printf("%-6d ", i);
			else printf("%-6.0f ", G[i-1][j-1]);
		}
		cout<<endl;
	}
	cout<<endl;
}

float TSP(int A[N], int l, float LSF, float& minCost) {
	if (l==N-1) {
		finalCount++;
		float prev = minCost;
		minCost = min(minCost, LSF + G[A[N-1]][A[0]]);
		if(minCost<prev) {
			for(int i=0;i<N;i++) {
				trip[i] = A[i];
			}
//			displayTrip(A, l+1);
//			cout<<minCost<<endl;
		}
	}
	else {
		for(int i=l+1;i<N;i++) {
			Swap(A[l+1], A[i]); 
			float newLength = LSF + G[A[l]][A[l+1]];
			if(newLength >= minCost) {
				//do Nothing
			}
			else {
				minCost = min(minCost, TSP(A, l+1, newLength, minCost));
			}
			Swap(A[l+1], A[i]);
		}
	}
	return minCost;
}

int main() {
	int A[N];
	for(int i=0;i<N;i++) A[i] = i;
	InitializeSites();
	InitializeGraph();
	displayGraph();
	float minCost = 32767.0;
	cout<<"Min Cost = "<<TSP(A, 0, 0.0, minCost)<<endl;
	displayTrip(trip, N);
	displayFinalTrip(trip, N);
	cout<<"No of Permutations checked: "<<finalCount<<endl;
	return 0;
}


