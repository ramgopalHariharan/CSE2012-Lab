#include<iostream>

using namespace std;

//Each Item has a Number, a weight and a value
struct Item {
	int number;
	int weight;
	int value;
};

ostream& operator << (ostream& out, Item i) {
	out<<"\nItem Number: "<<i.number<<"; Weight: "<<i.weight<<"; Value: "<<i.value;
	return out;
}

void display(char* name, Item a[], int n) {
	cout<<"Array of: "<<name<<endl;
	for (int i=0;i<n;i++) cout<<a[i]<<' ';
	cout<<endl;
}

//Sorting is done using Insertion sort based on the item weights
void sort(Item items[], int n) {
	for(int i=1;i<n;i++) {
		int j = i-1;
		Item x = items[i];
		while(j>=0 && items[j].weight > x.weight) {
			items[j+1] = items[j];
			j--;
		}
		items[j+1] = x;
	}
}

int main() {
	Item items[100];
	int maxWeight;
	int noOfItems;
	cout<<"Enter Number of Items:";
	cin>>noOfItems;
	
	//Enter weights and values of items
	cout<<"Enter Weights: ";
	for(int i=0;i<noOfItems;i++) {
		items[i].number = i;
		cin>>items[i].weight;
	}
	cout<<"Enter Values: ";
	for(int i=0;i<noOfItems;i++) cin>>items[i].value;
	
	//Enter the maximum weight W allowed to be carried
	cout<<"Enter Maximum Allowed Weight: ";
	cin>>maxWeight;
	
	//Sort the items based on weight in Ascending Order
	sort(items, noOfItems);
	
	//Create a table to store the maximum value attainable with different items and maximum Weights
	int values[noOfItems][maxWeight+1];
	
	//Initialize first column as 0 and first row as the weight of the first item
	for (int i=0;i<noOfItems;i++) {
		values[i][0] = 0;
	}
	for(int i=0;i<maxWeight+1;i++) {
		if(i>=items[0].weight) {
			values[0][i] = items[0].value;
		} else values[0][i] = 0;
	}
	
	//Fill in the rest og the values recursively
	for(int i=1;i<noOfItems;i++) {
		for(int j=0;j<maxWeight+1;j++) {
			values[i][j] = 0;
			if(items[i].weight>j) {
				values[i][j] = values[i-1][j];
				continue;
			}
			if(items[i].value + values[i-1][j-items[i].weight] > values[i-1][j]) {
				values[i][j] = items[i].value + values[i-1][j-items[i].weight];
			}
			else values[i][j] = values[i-1][j];
		}
	}
	
	display("Items", items, noOfItems);
	
	//Maximum Value Obtainable is at the bottom right corner of the values array
	cout<<"Maximum Value = "<<values[noOfItems-1][maxWeight]<<endl;
	
	//Recursively search through the value table to find he items which have been dicarded
	
	for(int i=noOfItems-1, j=maxWeight;i>=0 &&j>=0;) {
		//Discarded items are the rows in which the maximum value does not change 
		//from the previous row's value
		if(values[i-1][j] == values[i][j] || values[i][j]==0) {
			cout<<"Item "<<items[i].number<<" discarded\n";
			i--;
		}
		//If teh maximum value changes, that item has been taken and 
		//it's weight must be subtracted from the carried weight 
		else {
			j-=items[i].weight;
			i--;
		}
	}
}
