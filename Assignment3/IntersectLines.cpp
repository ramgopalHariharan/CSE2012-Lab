#include<iostream>
#include<cstdlib>
#include<time.h>

using namespace std;

struct Point {
	float x, y;
	int id, line;
};

//Line structure with an id, a start point p, and an end point q
struct Line {
	Point p, q;
	int id;
};

//Uses Cross Product And retruns the value of (x1-x0)(y2-y0)-(x2-x0)(y1-y0)
float Direction(Point p0, Point p1, Point p2) {
	float d = (p1.x - p0.x)*(p2.y-p0.y) - (p2.x - p0.x)*(p1.y-p0.y);
	return d;
}

//Checks if pk lies on the segment formed by pi and pj
bool OnSegment(Point pi, Point pj, Point pk) {
	if(min(pi.x, pj.x)<=pk.x && pk.x<=max(pi.x, pj.x) 
		&& min(pi.y, pj.y)<=pk.y && pk.y<=max(pi.y, pj.y)) 
		return true;
	else 
		return false;
}

//returns true if l1 and l2 intersect using the cross products of different
//conmbinations of endpoints
bool Intersect(Line l1, Line l2) {
	float d1 = Direction(l2.p, l2.q, l1.p);
	float d2 = Direction(l2.p, l2.q, l1.q);
	float d3 = Direction(l1.p, l1.q, l2.p);
	float d4 = Direction(l1.p, l1.q, l2.q);
	if((d1*d2<0) && (d3*d4<0)) return true;
	else if(d1==0 && OnSegment(l2.p, l2.q, l1.p)) return true;
	else if(d2==0 && OnSegment(l2.p, l2.q, l1.q)) return true;
	else if(d1==0 && OnSegment(l1.p, l1.q, l2.p)) return true;
	else if(d1==0 && OnSegment(l1.p, l1.q, l2.q)) return true;
	else return false;
}

//Random points to act as coordinates for ten villages
void input(Point p[], int n) {
	srand(time(0));
	for(int i=0;i<n;i++) {
		p[i].id = i;
		p[i].line = i/2;
		p[i].x = rand() % 20 + 1;
		p[i].y = rand() % 20 + 1;
	}
	for(int i=0;i<n;i++) 
		printf("Point %d: (%.0f,%.0f)\n", i, p[i].x, p[i].y);
}

//List Class to hold the points in sorted order
class List {
public:	
	Point a[20];
	int size;
	List() {size = 0;}
	void insert(Point p) {a[size++] = p;}
	//Sorts points using selection sort in the order of their x coordinates
	//as we are sweeping the lines from left to right
	void sort() {
		cout<<"Sorting\n";
		for(int i=0;i<size-1;i++) {
			int x = i;
			for(int j=i+1;j<size;j++) 
				if(a[j].x<a[x].x) 
					x = j;
			Point temp = a[i];
			a[i] = a[x];
			a[x] = temp;
		}
	}
	//Displays the sorted list of event points
	void display() {
		cout<<endl<<"Displaying\n";
		for(int i=0;i<size;i++) 
			printf("Point %d: (%.0f,%.0f)\n", a[i].id, a[i].x, a[i].y);
	}
};

//Holds the current sweep line status at the current event point as an ordered list
//(doubly linked list) ordered by the y coordinate of teh points in the lines
class Order {
	struct Node {
		Node* next;
		Node* prev;
		int id;
		float y;
		Node(int i = -1, float y = 0) {
			id = i;
			next = prev = NULL;
		}
	};
	Node* root;
public:
	Order() {
		root = NULL;
	}
	void Insert(Line l, Point p) {
		Node* t = root;
		Node* x = new Node(l.id, p.y);
		if(t==NULL) {
			root = x;
			return;
		}
		while(t!=NULL) {
			if(p.y>t->y) {
				if(t->next==NULL) {
					t->next = x;
					x->prev = t;
					return;
				}
				t=t->next;
			} else {
				x->next = t;
				x->prev = t->prev;
				t->prev = x;
				return;
			}
		}	
	}
	void Delete(int id) {
		Node* t =  root;
		while(t!=NULL) {
			if(t->id == id) {
				if(t->prev!=NULL) 
					t->prev->next = t->next;
				if(t->next!=NULL) 
					t->next->prev = t->prev;
				delete t;
			}
			t=t->next;
		}
	}
	//Returns id of line immediately above the given line id
	//returns -1 if no line found
	int Above(int id) {
		Node* t = root;
		while(t!=NULL) {
			if(t->id == id) {
				if(t->next==NULL) 
					return -1;	
				return t->next->id;
			}
			t=t->next;
		}
		return -1;
	}
	//Same as Above() but returns line immediately below given line id
	int Below(int id) {
		Node* t = root;
		while(t!=NULL) {
			if(t->id == id) {
				if(t->prev == NULL) 
					return -1;
				return t->prev->id;
			}
			t=t->next;
		}
		return -1;
	}
};

//Returns true if any of the segments intersect
bool anySegIntersect(Line lines[], List L) {
	Order T;
	for(int i=0;i<L.size;i++) {
		int current = L.a[i].line;
		//if the curretn point is a starting point of a line
		if(L.a[i].id%2==0) {	
			//insert the line into the order
			T.Insert(lines[current], L.a[i]);
			int above = T.Above(current); 
			int	below = T.Below(current);
			//If a line exits above this line and it intersects it
			if(above != -1) 
				if(Intersect(lines[above], lines[current])) 
					return true;
			//	or a line below this line exists and intersects it
			else if(below != -1) 
				if (Intersect(lines[below], lines[current])) 
					return true;
		}
		//if the current point is an endpoint
		else if (L.a[i].id%2==1) {
			int above = T.Above(current);
			int	below = T.Below(current);
			//If there are lines above and below the current line 
			//and they intersect each other
			if(above != -1 && below != -1 )
				if(Intersect(lines[above], lines[below])) 
					return true;	
			T.Delete(current);
		}
	}
	return false;
}

int main() {
	Point points[20];
	Line lines[10];
	List L;
	int n = 20;
	input(points, n);
	for(int i=0;i<n/2;i++) {
		lines[i].id = i;
		lines[i].p = points[2*i];
		lines[i].q = points[2*i + 1];
	}
	for(int i=0;i<n;i++) 
		L.insert(points[i]);
	L.sort();
	L.display();
	if(anySegIntersect(lines, L)) {
		cout<<"There are intersecting Lines\n";
	} else {
		cout<<"There are no intersecting lines\n";
	}
	return 0;
}

