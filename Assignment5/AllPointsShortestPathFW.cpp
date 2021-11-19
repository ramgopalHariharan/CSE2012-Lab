#include<iostream>
#define INF 1<<30

using namespace std;

void input(int graph[][10], int& n) {
	int choice;
	cout<<"User input ? (Enter 0 for automatic generation) : ";
	cin>>choice;
	if(choice == 0) {
		//Automatic input for testing
		n = 5;
		for(int i=0;i<n;i++) 
			for(int j=0;j<n;j++)
				graph[i][j] = INF;
		for(int i=0, j=0;i<n;i++, j++) 
			graph[i][j] = 0;
		graph[0][1] = 1; graph[0][3] = 1;
		graph[0][4] = 5; graph[1][0] = 9;
		graph[1][2] = 3; graph[1][3] = 2;
		graph[2][3] = 4; graph[3][2] = 2;
		graph[3][4] = 3; graph[4][0] = 3;
		return;
	}
//	User can enter the number of vertices and the connections
	cout<<"Enter number of Vertices: "; cin>>n;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			if(i==j) {
				graph[i][j] = 0;
				continue;
			}
			printf("Enter Distance between vertex %d and vertex %d (Enter -1 for no connection): ", i, j);
			cin>>graph[i][j];
			if(graph[i][j] == -1) graph[i][j] = INF;
		}
	}
}

void display(int array[][10], int n) {
	for(int i=0;i<n+1;i++) {
		for(int j=0;j<n+1;j++) {
			if(i==0 && j==0) cout<<"    ";
			else if (i==0) printf("%3d ", j-1);
			else if (j==0) printf("%3d ", i-1);
			else {
				if(array[i-1][j-1]==INF) printf("INF ");
				else printf("%3d ", array[i-1][j-1]);
			}
		}
		cout<<endl;
	}
	cout<<endl;
}

//table is the dynamic programming array that is updated every loop
void AllPairShortestPathFW(int graph[][10], int n, int D[][10]) {
	//Setting the d[0] to the same value as the graph matrix
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			D[i][j] = graph[i][j];
		}
	}
	cout<<"Tables: \n";
	//Adding the next vertex to teh set of vertices s = {0, 1, .. k}
	for(int k=0;k<n;k++) {
		cout<<"D "<<k<<" :\n";
		display(D, n);
		//Chhosing a start vertex
		for(int i=0;i<n;i++) {
			//Choosing an end vertex for the above start vertex
			for(int j=0;j<n;j++) {
				//If vertex k is on the path from i to j, choose the shorter distance
				if (D[i][j] > (D[i][k] + D[k][j]) && D[i][k]!=INF && D[k][j]!=INF)
                    D[i][j] = D[i][k] + D[k][j];
			}
		}
	}
}

int main() {
	int graph[10][10], n;
	int D[10][10];
	input(graph, n);
	cout<<"Graph: \n";
	display(graph, n);
	AllPairShortestPathFW(graph, n, D);
	cout<<"Shortest Distances: \n";
	display(D, n);
	return 0;
}
