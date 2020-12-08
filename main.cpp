#include <stdio.h>
#include <stdlib.h> //These 3 includes are for generating random numbers
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>


using namespace std;

void heapifyDown(double* theheap, int index, int size)
{
	if (index >= size / 2 + 1)
	{
		//Do nothing
	}
	else
	{
		int Smallest_Child_Index = index;
		if (theheap[2 * (index)+1] < theheap[index] && 2 * (index)+1 < size)
		{
			Smallest_Child_Index = 2 * (index)+1;
		}
		if (theheap[2 * (index)+2] < theheap[Smallest_Child_Index] && 2 * (index)+2 < size)
		{
			Smallest_Child_Index = 2 * (index)+2;
		}
		if (Smallest_Child_Index != index)
		{
			int temp = theheap[index];
			theheap[index] = theheap[Smallest_Child_Index];
			theheap[Smallest_Child_Index] = temp;
			heapifyDown(theheap, Smallest_Child_Index, size);
		}
	}
}
int readHeap(double* theheap)
{
	string pp;
	getline(cin, pp);
	vector<string> ppassignment;
	bool Used = false;
	int pp2 = 0;
	for (int i = 0; i < pp.size(); i++)
	{
		if (pp[i] == '-')
		{
			break;
		}
		if (pp[i] != ' ')
		{
			if (Used == true)
			{
				ppassignment.at(pp2) += pp[i];
			}
			else
			{
				Used = true;
				string A = "";
				A.push_back(pp[i]);
				ppassignment.push_back(A);
			}
		}
		else
		{
			Used = false;
			pp2++;
		}
	}
	for (int i = 0; i < ppassignment.size(); i++)
	{
		*(theheap + i) = stoi(ppassignment.at(i));
	}
	return (ppassignment.size());

	//return the size of the heap
}

void heapRemove(double* theheap, int& size)
{
	//your code here
	theheap[0] = theheap[size - 1];
	size--;
	if (size > 0)
	{
		heapifyDown(theheap, 0, size);
	}
}

void heapPrint(double* theheap, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << theheap[i] << " ";
	}
	//use cout to print the array representing the heap
}


class Node
{
public:
	string name;
	double id;
	Node* left = NULL; //stores student data
	Node* right = NULL;
	Node(string N, double x) : name(N), id(x), left(nullptr), right(nullptr) {}

	// Node();
};
int getHeight(Node* root)
{
	if (root == nullptr)
		return 0;

	else
	{
		int l = getHeight(root->left);
		int r = getHeight(root->right); //finds path of max length

		if (l > r)
			return (l + 1);

		else
			return (r + 1);
	}
}

int getAVL(Node* root)
{
	Node* left = root->left;
	Node* right = root->right;
	int l, r;
	l = getHeight(left);
	r = getHeight(right);

	int t = (l - r); //subtracts left height from right to get diff

	return t;
}
Node* _rr(Node* parent)
{
	Node* n = parent->right;
	parent->right = n->left;
	n->left = parent;
	return n;
}
Node* _ll(Node* parent)
{
	Node* n = parent->left;
	parent->left = n->right; //rotations
	n->right = parent;
	return n;
}
Node* _lr(Node* parent)
{
	Node* n2 = parent->left;
	parent->left = _rr(n2);

	return _ll(parent);
}
Node* _rl(Node* parent)
{
	Node* n2 = parent->right;
	parent->right = _ll(n2);

	return _rr(parent);
}

Node* balanceTree(Node* p)
{
	int t = getAVL(p);
	if (t > 1)
	{
		if (getAVL(p->left) > 0)
			p = _ll(p); //left side unbalanced
		else
			p = _lr(p);
	}
	else if (t < -1)
	{
		if (getAVL(p->right) > 0)
			p = _rl(p); //right side unbalanced
		else
			p = _rr(p);
	}
	return p;
}
Node* insertID(string name, double id, Node* n)
{

	if (n == NULL)
	{ //base case; once there is a spot available for student it's inserted

		Node* n2 = new Node(name, id);
		n2->left = nullptr;
		n2->right = nullptr;
		// cout << id << endl;
		return n2;
	}

	else if (id <= n->id)
	{
		n->left = insertID(name, id, n->left);
		n = balanceTree(n); //after each iteration checks if tree needs to be balanced
	}
	else if (id > n->id)
	{
		n->right = insertID(name, id, n->right);
		n = balanceTree(n);
	}
	else
	{
		cout << "unsuccessful" << id << " " << n->id << endl;
	}
	return n;
}

void In_Order(Node* root, double& avg) //left, root, right. Order of the "In order" traversal
{
	if (root != nullptr) //if the root isn't null
	{
		In_Order(root->left, avg);//left node
		avg += root->id; //root node
		In_Order(root->right, avg); //right node
	}
}

bool checkString(string s)
{ //for validity

	for (int i = 0; i < s.size(); i++)
	{

		if (isalpha(s[i]) || isspace(s[i]))
		{
		}
		else
			return false;
	}
	return true;
}

class WaterBottle //Class that holds waterbottle info
{
public:
	double volume;
	double concentration;
	double price;
	WaterBottle(double _volume, double _concentration, double _price)
	{
		volume = _volume;
		concentration = _concentration;
		price = _price;
	}
	WaterBottle()
	{
		volume, concentration, price = 0;
	}
};

// map <
void generate(vector<WaterBottle>& Bottles, double seedPrice, double seedVolume, double seedConcentration)
{

	srand(time(NULL));
	for (int a = 0; a < 20000; a++)
	{
		WaterBottle WB;
		WB.volume = seedVolume * ((rand() % 100 + 9));
		WB.concentration = seedConcentration * ((rand() % 100 + 9));
		WB.price = seedPrice * ((rand() % 2 + 1.2));
		Bottles.push_back(WB);
	}
}

Node* createAVL(string name, vector<WaterBottle> bottles, Node* root, double arr[])
{

	for (int i = 0; i < bottles.size(); i++)
	{
		arr[i] = bottles[i].price;
		double val = bottles[i].volume / bottles[i].concentration;
		root = insertID(name, val, root);
	}
	heapifyDown(arr, 0, bottles.size());
	return root;
}


int main()
{
	std::map<string, vector<WaterBottle>> BottleData;

	vector<WaterBottle> FijiBottles;
	vector<WaterBottle> DasaniBottles;
	vector<WaterBottle> SmartwaterBottles;
	vector<WaterBottle> ZephyrhillsBottles;
	vector<WaterBottle> AquafinaBottles;
	Node* root1 = NULL;
	Node* root2 = NULL;
	Node* root3 = NULL;
	Node* root4 = NULL;
	Node* root5 = NULL;
	double heap1[20000];
	double heap2[20000];
	double heap3[20000];
	double heap4[20000];
	double heap5[20000];
	double avg1 = 0;
	double avg2 = 0;
	double avg3 = 0;
	double avg4 = 0;
	double avg5 = 0;

	// Fiji: price- $2.18 volume- 50.7 oz dissolved solids: 222 mg/L
	generate(FijiBottles, 2.18, 50.7, 222);

	// Dasani: price - $1.12 volume - 33.81413 oz dissolved: 14 mg/L
	generate(DasaniBottles, 1.12, 33.81, 14);

	// Smartwater: price - $1.58 volume - 33.81413 oz total dissolved: 36 mg/L
	generate(SmartwaterBottles, 1.58, 33.81, 36);

	// Zephyrhills: price - 1.14 volume - 101.4 total dissolved: 120 mg/L
	generate(ZephyrhillsBottles, 1.14, 101.4, 120);

	// Aquafina: price - 1.00 volume - 33.81413 oz total dissolved: 60 mg/L
	generate(AquafinaBottles, 1.00, 33.81, 60);

	// put bottle vectors into map
	BottleData["Fiji"] = FijiBottles;
	BottleData["Dasani"] = DasaniBottles;
	BottleData["Smartwater"] = SmartwaterBottles;
	BottleData["Zephyrhills"] = ZephyrhillsBottles;
	BottleData["Aquafina"] = AquafinaBottles;

	//creates 5 trees
	root1 = createAVL("Fiji", FijiBottles, root1, heap1);
	root2 = createAVL("Dasani", DasaniBottles, root2, heap2);
	root3 = createAVL("SmartWater", SmartwaterBottles, root3, heap3);
	root4 = createAVL("Zephyrhills", ZephyrhillsBottles, root4, heap4);
	root5 = createAVL("Aquafina", AquafinaBottles, root5, heap5);
	//calculates average mineral concentration per vol
	In_Order(root1, avg1);
	avg1 /= 20000;
	In_Order(root2, avg2);
	avg2 /= 20000;
	In_Order(root3, avg3);
	avg3 /= 20000;
	In_Order(root4, avg4);
	avg4 /= 20000;
	In_Order(root5, avg5);
	avg5 /= 20000;

	//organizes heaps
	heapifyDown(heap1, 0, 20000);
	heapifyDown(heap2, 0, 20000);
	heapifyDown(heap3, 0, 20000);
	heapifyDown(heap4, 0, 20000);
	heapifyDown(heap5, 0, 20000);

	map<string, vector<pair<double, double>>> finalData;
	finalData["Fiji"].push_back(make_pair(heap1[0], avg1));
	finalData["Dasani"].push_back(make_pair(heap2[0], avg2));
	finalData["SmartWater"].push_back(make_pair(heap3[0], avg3));
	finalData["Zephyrhills"].push_back(make_pair(heap4[0], avg4));
	finalData["Aquafina"].push_back(make_pair(heap5[0], avg5));

	//finds optimum price per minerals per vol ratio
	map<string, vector<pair<double, double>>>::iterator it;
	double min = finalData["Fiji"].at(0).first / finalData["Fiji"].at(0).second;
	string smin = "Fiji";
	for (it = finalData.begin(); it != finalData.end(); it++) {
		if (min > finalData[it->first].at(0).first / finalData[it->first].at(0).second) {
			min = finalData[it->first].at(0).first / finalData[it->first].at(0).second;
			smin = it->first;
		}
	}
	//prints values as well as the optimal water brand
	cout << "Fiji " << endl << "Lowest price: " << heap1[0] << "  " << "average mineral per vol concentration: " << avg1 << endl << endl;
	cout << "Dasani " << endl << "Lowest price: " << heap2[0] << "  " << "average mineral per vol concentration: " << avg2 << endl << endl;
	cout << "SmartWater " << endl << "Lowest price: " << heap3[0] << "  " << "average mineral per vol concentration: " << avg3 << endl << endl;
	cout << "Zephyrhills " << endl << "Lowest price: " << heap4[0] << "  " << "average mineral per vol concentration: " << avg4 << endl << endl;
	cout << "Aquafina " << endl << "Lowest price: " << heap5[0] << "  " << "average mineral per vol concentration: " << avg5 << endl << endl;
	cout << smin << " has the best price / minerals per vol ratio: " << min << endl << endl;


	return 0;
}
