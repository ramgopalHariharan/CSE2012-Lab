#include<iostream>
#include<vector>

using namespace std;

struct Node {
	int freq;
	char character;
	bool leaf;
	char code[500];
	int codeLength;
	Node* left;
	Node* right;
	Node* parent;
	//Initializes th node with a character and whether the node is a leaf or not
	//(Only characters can be leaves in the Huffn=mann Tree)
	Node(int freq_ = 0, char character_ = '\0', bool isLeaf = false) {
		freq = freq_;
		character = character_;
		isLeaf = isLeaf;
		codeLength = 0;
		next = left = right = parent = NULL;
	}
	//Increments the frequency of the character represented by the node
	void incr() {
		freq++;
	}
	//Adds a character to teh end of the code of the particular node
	//b is the character
	void addBit(char a[], char b) {
		int i = 0;
		//Loop to the end of the node
		while(a[i]) {
			code[i] = a[i];
			i++;
		}
		code[i] = b;
		code[i+1] = '\0';
	}	
};
//Priority Queue Class fro the Huffmann Tree
//Priority is the frequency of the Node
//Node with the minimum priority is in the front of the queue
class PriorityQueue {
	Node* front;
	Node* rear;
	int size;
public:
	PriorityQueue() {
		front = rear = NULL;
		size = 0;
	}
	//Inserts a Node into the priority Queue
	void insert(Node* x) {
		Node* t = x;
		if(t==NULL) return;
		if(isEmpty()) front = rear = t;
		else if(t->freq<=front->freq)  {
			t->next = front;
			front = t;
		}
		else {
			Node* x = front->next;
			Node* p = front;
			while(x!=NULL && x->freq<t->freq) {
				p = x;
				x = x->next;
			}
			if(p->next==NULL) p->next = t;
			else {
				t->next = p->next;
				p->next = t;
			}
		}
		size++;
	}
	//Returns the Node with the minimum priority and removes it from the Priority Queue
	Node* returnMin() {
		Node* t = NULL;
		if(isEmpty()) return t;
		t = front;
		front = front->next;
		size--;
		return t;
	}
	//Checks wheher the priority queue is empty
	bool isEmpty() {
		return (front==NULL);
	}
	//returns the size of the priority queue
	int Size() {
		return size;
	}
};
	
//Priority Queue For building Huffmann Tree
PriorityQueue PQ;
//Storing the Huffmann Tree as an array of Pointers
vector<Node*> treeNodes;
//Root of the huffmann Tree
Node* root = NULL;
//Number of Nodes in the tree
int nodeCount = 0;
//Length of the longest code
int maxCodeLength;

//Returns the node for a specified character
Node* getNode(char a) {
	for(int i=0;i<treeNodes.size();i++) {
		if(treeNodes[i]->character == a) return treeNodes[i];
	}
	Node* t = NULL;
	return t;
}
//Makes Huffmann Tree from tree nodes that have been inserted into the Priority Queue
void makeTree() {
	while(PQ.Size()!=1) {
		Node* l = PQ.returnMin();
		Node* r = PQ.returnMin();
		//Pop two nodes from the priority Queue and 
		//add their frequencies to get tehir parent node
		Node* p = new Node(l->freq+r->freq);
		//Set the nodes as children of the parent
		p->left = l;
		p->right = r;
		r->parent = l->parent = p;
		//insert the parent into the priority Queue
		PQ.insert(p);
		//Repeat until there is only one node in the priority Queue
		//this is the root of the tree, with the character nodes at the leaves
		//Non leaf nodes have the character \0
	}
}
//Set the code for each node in the tree, 
//0 if going dowm the left brach and 
//1 for the right branch
void setCode(Node* cur) {
	if(cur == root) {
		cur->codeLength = 0;
		if(cur->left!=NULL) {
			cur->left->code[0] = '0';
			cur->left->codeLength = 1+cur->codeLength;
			setCode(cur->left);
		} 
		if(cur->right!=NULL) {
			cur->right->code[0] = '1';
			cur->right->codeLength = 1+cur->codeLength;
			setCode(cur->right);
		};
	}
	else {
		if(cur->leaf) return;
		if(cur->left!=NULL) {
			cur->left->addBit(cur->code, '0');
			cur->left->codeLength = 1+cur->codeLength;
			setCode(cur->left);
		} 
		if(cur->right!=NULL) {
			cur->right->addBit(cur->code, '1');
			cur->right->codeLength = 1+cur->codeLength;
			setCode(cur->right);
		};
	}
}

//Calculate max code length recursively by traversing DFS Style 
//down whichever path is longest from root
int calcMaxCodeLength(Node* current) {
	if(current ==NULL) return -1;
	return 1+max(calcMaxCodeLength(current->left), calcMaxCodeLength(current->right));
}

//Checks if the given character has already been read aand stroed in the tree
bool stored(char a) {
	for(int i=0;i<treeNodes.size();i++) {
		if(treeNodes[i]->character == a) return true;
	}
	return false;
}

//Display the codes of all the characters in the file along with their frequncy
void displayDictionary() {
	printf("Character Frequency Code Word Bits Required\n");
	for(int i=0;i<treeNodes.size();i++) {
		printf("%-9-c %-9-d %-9-s %-13-d\n", 
				treeNodes[i]->character, treeNodes[i]->freq, treeNodes[i]->code, 
				treeNodes[i]->codeLength*treeNodes[i]->freq);
	}
}

//Builds a Huffmann Tree for a given text txt and traverses teh tree to calculate the codes
void HuffmannCompression(char txt[]) {
	int i=0;
	//Read through the characters of teh text an add them to the list of characters
	//if already added, increment their frequency
	while(txt[i]!='\0') {
		if(stored(txt[i])) {
			getNode(txt[i])->incr();
		}
		else {
			treeNodes.push_back(new Node(1, txt[i], true));
			nodeCount++;
		}
		i++;
	}
	//Insert all the character nodes into the priority Queue to initialize it
	for(int i=0;i<treeNodes.size();i++) {
		PQ.insert(treeNodes[i]);
	}
	//Buld HuffmannTree
	makeTree();
	//The node remianing in hte priority queue is the root fo the Huffmann Tree
	root = PQ.returnMin();
	//Calculate the codes of each of the Nodes, start from root
	setCode(root);
	//Calculate teh maximum code length for future reference
	calcMaxCodeLength(root);
}
int main() {
	char text[500]; int n, total = 0;
	cout<<"Enter the text to compress: ";
	scanf("%[^\n]500s", text);
	for(n=0;text[n]!='\0';n++);
	cout<<"Compressing and generating bit codes...\n";
	HuffmannCompression(text);
	displayDictionary();
	cout<<"Coded Text: \n";
	for(int i=0;i<n;i++) {
		cout<<getNode(text[i])->code;
	}
	cout<<"\nTotal bits required = ";
	for(int i=0;i<nodeCount;i++) {
		total += treeNodes[i]->freq * treeNodes[i]->codeLength;
	}
	cout<<total<<endl;
	cout<<endl<<root->freq<<endl;
	return 0;
}
