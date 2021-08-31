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
	cout<<"Enter Weights: ";
	
	//Enter weights of items
	for(int i=0;i<noOfItems;i++) {
		items[i].number = i;
		cin>>items[i].weight;
	}
	//Enter teh maximum weight W allowed to be carried
	cout<<"Enter Maximum Allowed Weight: ";
	cin>>maxWeight;
	//Since All Items have Equal Value, Set it as 1
	for(int i=0;i<noOfItems;i++) items[i].value = 1;
	
	display("Items", items, noOfItems);
	
	//Sort the items in Ascending order of Weight
	sort(items, noOfItems);
	int weightCarried = 0, i=0, k=0;
	//Loop through the sorted list of items
	while(weightCarried + items[i].weight <= maxWeight) {
		//If the current item does not push the carried weight over the limit, add it to carried items
		weightCarried += items[i].weight;
		i++;
		//Continue until carried weight is more than the allowed weight
	}
	cout<<"Weight Carried = "<<weightCarried<<endl;
	//Display Discarded items, items in the list whose weght was not added to total carried weight
	cout<<"Items Discarded : \n";
	for(;i<noOfItems;i++) {
		cout<<"Item "<<items[i].number<<endl;
	}
}
