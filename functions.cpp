#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include "Header.h"


using namespace std;

void DataProject::menu() {
	tree* null;
	int  choice = 0;

	while (choice != 3) {
		cout	<< "Welcome to Text Encoder-Decoder \n"
				<< "Please select a choice:\n"
				<< "1)Encode the txt\n"
				<< "2)Decode the txt\n"
				<< "3)EXIT\n";
		cin >> choice;
	
		switch (choice) {
		case(1) : input(); toQueue(1); buildTree(1,null);	output();		break;
		case(2) : decode();													break;
		case(3) : 															return;
		}
	}
	return;
}



void DataProject::input() {
	
	cout << "Enter The File Name:(Without .txt)";
	cin >> fileName;
	fileEncoded = fileName + "Zip.txt";
	fileName += ".txt";

	
	ifstream myfile(fileName);
	if (!myfile) {
		cerr << "Can't Open The File";
	}

	char c;
	while (myfile.read(&c, sizeof(char))) {
		holymeatball[int(c)]++;
		charvector.push_back(c);
	}

	//Dummy EOF
	holymeatball[999]++;

	myfile.close();
	
	return;
}


void DataProject::toQueue(int i)
{
	ofstream outfile;
	if (i == 1) { 
		 outfile.open(fileEncoded, ios::out); 
		
		//Kaç harf var
		 outfile << holymeatball.size() << "\n"; 
	}

	
	for (auto it = holymeatball.cbegin(); it != holymeatball.cend(); ++it){	
		
		//Harf ve sıklıkları 
		if (i == 1) { outfile << ((it->first)) << " " << it->second << "\n"; }
		
		insert(it->first, it->second);
	}
	outfile.close();
	return;
}

void DataProject::insert(int char1,int data1)
{
	tree *onetree = new tree(char1, data1);
	myqueue.push(onetree);
	return;
}


void DataProject::buildTree(int i,tree* &decodeTree) {

	while (myqueue.size() > 1) {
		tree* tree1 = new tree();
		tree* tree2 = new tree();
		tree *lastTreeBender = new tree();

		tree1->letter = myqueue.top()->letter;
		tree1->totalFrequency = myqueue.top()->totalFrequency;
		tree1->left = myqueue.top()->left;
		tree1->right = myqueue.top()->right;

		myqueue.pop();

		tree2->letter = myqueue.top()->letter;
		tree2->totalFrequency = myqueue.top()->totalFrequency;
		tree2->left = myqueue.top()->left;
		tree2->right = myqueue.top()->right;

		myqueue.pop();

		lastTreeBender->totalFrequency = tree1->totalFrequency + tree2->totalFrequency;
		lastTreeBender->left = tree1;
		lastTreeBender->right = tree2;

		myqueue.push(lastTreeBender);
	}
	

	if (i) {
		tree *holyTree = myqueue.top();
		string code;
		traverseTree(holyTree, code);

	}
	else{ 
		decodeTree = myqueue.top();
	}
	
	return;

}

void DataProject::traverseTree(tree*  current, string code) {
	
	if (current->left == nullptr && current->right == nullptr)
	{
		mymap.insert(pair<int, string>(current->letter, code));
	}
	if (current->left != NULL) {
		traverseTree(current->left, code + '0');
	}
	if (current->right != NULL) {
		traverseTree(current->right, code + '1');
	}
	return;
}

void DataProject::output()
{
	ofstream outfile(fileEncoded, ios::out | ios::app| ios::binary);

	//Binary String
	vector<char> buffer;
	
	for (int i = 0; i < charvector.size(); i++) {
		for (char & d : mymap.at(charvector[i])) {
			buffer.push_back(d);
		}
	}
	
	// Append EOF to end
	for (char & c : mymap[999])
		buffer.push_back(c);

	
	unsigned int byte32 = 0;
	string word;

	for (int i = 0; i < buffer.size(); i++) {
		word += buffer[i];

		if (word.length() == 32) {
			byte32 = stoul(word, nullptr, 2);
			outfile.write(reinterpret_cast<const char *>(&byte32), sizeof(byte32));
			word.clear();
		}
	}
	if (word.length() != 32 && word.length() > 0) { 
		while (word.length() != 32 )  { 
			word += '0';
		}

	byte32 = stoul(word, nullptr, 2); 	
	outfile.write(reinterpret_cast<const char * >(&byte32), sizeof(byte32));
	}
	
	outfile.close();
	return;
}

void DataProject::decode()
{
	holymeatball.clear();
	while (!myqueue.empty()) {
		myqueue.pop();
	}
	mymap.clear();
	fileEncoded.clear();

	cout << "Enter The (Encoded)File Name:(Without .txt)";
	cin >> fileEncoded;
	fileDecoded = fileEncoded + "Decoded.txt";
	fileEncoded += ".txt";

	ifstream myfile(fileEncoded,ios::binary);
	if (!myfile) {
		cerr << "Can't Open The File";
	}

	int size;
	myfile >> size;
	
	int character;
	int frequency;
	for (int i = 0; i < size; i++) {	
		myfile >> character;
		myfile >> frequency;
		holymeatball.insert(pair<int, int>(character, frequency));
	}

	toQueue(0);
	tree* decodeTree;
	buildTree(0,decodeTree);



	string line;
	getline(myfile, line);	// start of encoded part
	line.clear();



	ofstream outfile(fileDecoded, ios::out|ios::binary);


	unsigned int byte32 = 0;
	string bitstring;
	while (myfile.read(reinterpret_cast< char * > (&byte32) , sizeof(byte32) ) ) {
		for (int i = 31; i >= 0; --i) {
			bitstring += ((byte32&(1 << i)) ? '1' : '0');
		}
		byte32 = 0;
	}
		
	
	
	tree * current = decodeTree;
	

	for (int i = 0; i < bitstring.size(); ++i) {
		if (bitstring[i] == '0') {
			current = current->left;
		}
		else if( bitstring[i] == '1')
			current = current->right;
	
		if (current->letter == 999) {
			outfile.close();
			myfile.close();
			return;
		}
		if (current->letter != -999) {
			char c = (current->letter);
			if (current->letter == 999) {
				outfile << int (current->letter);
				outfile.close();
				myfile.close();
				return;
			}	
			outfile.write(&c, sizeof(char));
			current = decodeTree;
		}
	}
	return;
}
