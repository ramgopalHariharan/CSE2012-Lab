#include<iostream>

using namespace std;

struct Item {
	int number, weight, value;
	float taken;
	Item(){}
	Item(int number_, int weight_, int value_) {
		weight = weight_;
		value = value_;
		taken = 0.0;
		number = number_;
	}
	Item(Item &i) {
		weight = i.weight;
		value = i.value;
		taken = i.taken;
		number = i.number;
	}
}; 

bool operator > (Item a, Item b) {
	return a.weight > b.weight;
}

bool operator < (Item a, Item b) {
	return a.weight < b.weight;
}

void input(Item items[], int& n, int& W) {
	cout<<"Enter Number of items: "; cin>>n;
	cout<<"Enter Weights: ";
	for(int i=0;i<n;i++) {
		items[i].number = i;
		cin>>items[i].weight;
	}
	cout<<"Enter Values: ";
	for(int i=0;i<n;i++) {
		cin>>items[i].value;
	}
	cout<<"Enter Maximum Weight: ";
	cin>>W;
}

void display(Item items[], int n) {
	cout<<"Items:\n";
	for(int i=0;i<n;i++) {
		cout<<"Item: "<<items[i].number<<" Weight: "<<items[i].weight<<" Value: "<<items[i].value;
		cout<<"\nFraction Taken: "<<items[i].taken<<endl;
	}
}

sortItemsByWeight(Item items[], int n) {
	for(int i=1;i<n;i++) {
		Item x = items[i];
		int j = i-1;
		while(j>=0 && items[j] > x) {
			items[j+1] = items[j];
			j--;
		}
		items[j+1] = x;
	}
}

float KnapsackGreedy2(Item items[], int n, int W) {
	sortItemsByWeight(items, n);
	float MaxValue = 0;
	for(int i=0;i<n && W>0 ;i++) {
		if(W > items[i].weight) {
			W -= items[i].weight;
			MaxValue += items[i].value;
			items[i].taken = 1;
		}
		else {
			float taken = (float)W / (float)items[i].weight;
			MaxValue += items[i].value * taken;
			items[i].taken = taken;
			W = 0;
		}
	}
	return MaxValue;
} 

int main() {
	Item items[10];
	int n, W;
	input(items, n, W);
	cout<<"\nGreedy Algorithm using Weights\n\n";
	float MaxValue = KnapsackGreedy2(items, n, W);
	cout<<"Maximum Value Possible = "<<MaxValue<<endl;
	display(items, n);
	return 0;
}
