#include<iostream>
#include<cstdlib>
#include<time.h>
#include<vector>
#define N 4
#define INF 9999

using namespace std;

struct Unit {
	int cost;
	int prevNode;
	bool end;
	Unit() { }
	Unit(int prev, int c, bool e = false) {
		cost = c;
		prevNode = prev;
		end = e;
	}
};

void GenerateDist(int dist[][N]) {
	srand(time(0));
	for(int i=0;i<N;i++) {
		for(int j=0 ;j<N;j++) {
			if(i==j) dist[i][j] = 0;
			else dist[i][j] = rand()%20 + 20;
		}
	}
}

void DisplayDist(int dist[][N]) {
	cout<<"Distance Graph : \n";
	for(int i=-1;i<N;i++) {
		for(int j=-1 ;j<N;j++) {
			if(i+j==-2) cout<<"   ";
			else if(i==-1) printf("%2-d ", j);
			else if(j==-1) printf("%2-d ", i);
			else printf("%2-d ", dist[i][j]);
		}
		cout<<endl;
	}
}

Unit* TSP(int dist[][N], int pos, int visited, Unit* DP[][1<<N], int prevNode) {
	if(visited == ((1<<N)-1)) {	
		Unit* u = new Unit(pos, dist[pos][0], true);
		return u;
	}
	if(DP[pos][visited]->cost != INT_MAX) {
		return DP[pos][visited];
	}
	
	for(int i=0;i<N;i++) {
		if(i == pos || visited & (1<<i)) {
			continue;
		}
		Unit* nextPos = TSP(dist, i, visited|(1<<i), DP, pos);
		int distance = dist[pos][i] + nextPos->cost;
		if(distance<DP[pos][visited]->cost) {
			if(nextPos->end) {
				int min = INT_MAX;
				int prev = -1;
				for(int k=0, j=(1<<N) - 1 - (1<<i);k<N;k++) {
					if(DP[k][j]->cost<min) {
						min = DP[k][j]->cost;
						prev = k;
					}
				}
				DP[i][(1<<N)-1]->prevNode = prev;
				DP[0][(1<<N)-1]->prevNode = i;
			}
			DP[pos][visited]->cost = distance;
			DP[pos][visited]->prevNode = prevNode;
		}
	}
	return DP[pos][visited];
}

void TracePath(Unit* DP[][1<<N], int i, int j) {
	cout<<i;
	if(j==1) return;
	cout<<"-->";
	if(i==0) {
		TracePath(DP, DP[i][j]->prevNode, j);
		return;
	}
	else {
		TracePath(DP, DP[i][j]->prevNode, j-(1<<i));
	}
}

int main() {
	int dist[N][N] = {  {0, 10, 15, 20}, 
						{5, 0, 9, 10}, 
						{6, 13, 0, 12}, 
						{8, 8, 9, 0}
					 };
	Unit* DP[N][(1<<N)];
//	GenerateDist(dist);
	DisplayDist(dist);
	for(int i=0;i<N;i++) {
		for(int j=0;j<(1<<N);j++) {
			DP[i][j] = new Unit(-1, INT_MAX);
			if(j==(1<<N)-1) DP[i][j]->cost = dist[i][0];
		}
	}
	int bestCost = TSP(dist, 0, 1, DP, -1)->cost;
	cout<<"\nBest Cost = "<<bestCost<<endl;
	cout<<"\nPath: ";
	TracePath(DP, 0, (1<<N)-1);
	return 0;
}
