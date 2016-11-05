#pragma once

#include <vector>
#include <map>
#include <queue>

using namespace std;


//Tree class
class tree {
private:
	tree(int letter = -999, int totalFrequency = -999) : left(nullptr), right(nullptr) {
		this->letter = letter;
		this->totalFrequency = totalFrequency;
	}

	int letter;
	int totalFrequency;
	tree *left;
	tree *right;

	friend class node_cmp;
	friend class DataProject;
};
//Comparator for priority queue
class node_cmp
{
public:
	bool operator() (const tree* a, const tree*b)const
	{
		return a->totalFrequency > b->totalFrequency;
	}
};


class DataProject {
private:
	//File Name
	string fileName;

	//Encoded File Name
	string fileEncoded;

	//Decoded File Name
	string fileDecoded;

	//First int:	ASCII code of that character
	//Second int:	Frequency
	map<int, int> holymeatball;

	//Contain characters of Alice.txt
	vector<char> charvector;

	//int : Decimal for ASCII characters
	//string : Code for ASCII character
	map<int, string> mymap;

	//Priority queue for my tree 
	priority_queue<tree*, deque<tree*>, node_cmp> myqueue;
public:
	//Menu
	void menu();

	//Encoding Part

	//Load data from .txt
	void input();

	//Building Queue
	//i = 1 Encode
	//i = 0 Decode
	void toQueue(int i);

	//Insert only one element to priority queue
	void insert(int char1, int data1);

	//Create the tree
	//i = 1 Encode
	//i = 0 Decode
	void buildTree(int i, tree*& decodeTree);

	//Traverse the final tree and make codes
	void traverseTree(tree*  holyTree, string code);

	//Make an encoded output
	void output();

	//Decoding Part

	//Decode txt
	void decode();



	friend class tree;

};

