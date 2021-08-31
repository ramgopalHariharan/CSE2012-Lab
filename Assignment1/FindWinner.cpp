#include<iostream>

using namespace std;

int main() {
	int scores[100], n;
	cout<<"Enter No of players: ";
	cin>>n;
	cout<<"Enter Scores: ";
	int max = 0, min = 0, secondMax = 0, secondMin = 0;
	for(int i=0;i<n;i++) cin>>scores[i];
	for(int i=0;i<n;i++) {
		if(scores[i] >= scores[max]) {
			max = i;
		}
		else if(scores[i]>scores[secondMax]) {
			secondMax = i;
		}
		if(scores[i]<=scores[min]) {
			min = i;
		}
		else if(scores[i]<scores[secondMin]) {
			secondMin = i;
		}
	}
	for(int i=0;i<n;i++) cout<<scores[i]<<' ';
	printf("\nWinner: Player %d\nWorst: Player %d\nSecond Winner: Player %d\nSecond Worst: Player %d\n"
			, max+1, min+1, secondMax+1, secondMin+1);
	
}
