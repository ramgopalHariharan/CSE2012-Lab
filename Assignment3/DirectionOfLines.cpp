#include<iostream>
#include<chrono>
#include<ctime>

using namespace std;

struct Point {
	float x, y;
};

Point input(char* name) {
	Point p;
	cout<<"Enter Coordinates for point "<<name<<": \n";
	cout<<"x: "; cin>>p.x;
	cout<<"y: "; cin>>p.y;
	return p;
}

char* Direction(Point p0, Point p1, Point p2) {
	float d = (p1.x - p0.x)*(p2.y-p0.y) - (p2.x - p0.x)*(p1.y-p0.y);
	cout<<"d =  "<<d<<endl;
	if(d>0) {
		return "Counter-Clockwise";
	} else if(d<0) {
		return "Clockwise";
	} else {
		return "Same Direction";
	}
}

int main() {
	Point p0, p1, p2;
	p0 = input("P0");
	p1 = input("P1");
	p2 = input("P2");
	cout<<"Direction : "<<Direction(p0, p1, p2);
	return 0;
}


