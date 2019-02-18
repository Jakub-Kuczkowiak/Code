 // C++ program to demonstrate working of 
// palindromic tree 
#include <iostream>
#include <string>
//#include "bits/stdc++.h" 
using namespace std;

#define MAXN 10000

struct Node
{
	// store start and end indexes of current 
	// Node inclusively 
	int start, end;

	// stores length of substring 
	int length;

	// stores insertion Node for all characters a-z 
	int insertEdg[256];

	// flag for lazy propagation of palindomres number
	int flag;

	// stores the Maximum Palindromic Suffix Node for 
	// the current Node 
	int suffixEdg;
};

// two special dummy Nodes as explained above 
Node root1, root2;

// stores Node information for constant time access 
Node tree[MAXN];

// Keeps track the current Node while insertion 
int currNode;
string s;
int ptr;

void init() {
	// initializing the tree 
	root1.length = -1;
	root1.suffixEdg = 1;
	root2.length = 0;
	root2.suffixEdg = 1;

	tree[1] = root1;
	tree[2] = root2;
	ptr = 2;
	currNode = 1;
}

void insert(int idx)
{
	//STEP 1// 

		/* search for Node X such that s[idx] X S[idx]
		is maximum palindrome ending at position idx
		iterate down the suffix link of currNode to
		find X */
	int tmp = currNode;
	while (true)
	{
		int curLength = tree[tmp].length;
		if (idx - curLength >= 1 and s[idx] == s[idx - curLength - 1])
			break;
		tmp = tree[tmp].suffixEdg;
	}

	/* Now we have found X ....
	* X = string at Node tmp
	* Check : if s[idx] X s[idx] already exists or not*/
	if (tree[tmp].insertEdg[s[idx]] != 0)
	{
		// s[idx] X s[idx] already exists in the tree 
		currNode = tree[tmp].insertEdg[s[idx]];

		tree[currNode].flag++;
		return;
	}

	// creating new Node 
	ptr++;

	// making new Node as child of X with 
	// weight as s[idx] 
	tree[tmp].insertEdg[s[idx]] = ptr;

	// calculating length of new Node 
	tree[ptr].length = tree[tmp].length + 2;

	// updating end point for new Node 
	tree[ptr].end = idx;

	// updating the start for new Node 
	tree[ptr].start = idx - tree[ptr].length + 1;


	//STEP 2// 

		/* Setting the suffix edge for the newly created
		Node tree[ptr]. Finding some String Y such that
		s[idx] + Y + s[idx] is longest possible
		palindromic suffix for newly created Node.*/

	tmp = tree[tmp].suffixEdg;

	// making new Node as current Node 
	currNode = ptr;
	if (tree[currNode].length == 1)
	{
		// if new palindrome's length is 1 
		// making its suffix link to be null string 
		tree[currNode].suffixEdg = 2;

		// lazy flag
		tree[2].flag++;
		return;
	}

	while (true)
	{
		int curLength = tree[tmp].length;
		if (idx - curLength >= 1 and s[idx] == s[idx - curLength - 1])
			break;
		tmp = tree[tmp].suffixEdg;
	}

	// Now we have found string Y 
	// linking current Nodes suffix link with s[idx]+Y+s[idx] 
	tree[currNode].suffixEdg = tree[tmp].insertEdg[s[idx]];
	tree[tree[currNode].suffixEdg].flag++;
}

int main()
{
	// given string 
	cin >> s;
	//s = "abcbab"; 
	int l = s.length();

	init(); // initializing tree

	for (int i = 0; i < l; i++)
		insert(i);

	int totalCount = 0;
	for (int i = ptr; i >= 3; i--) {
		tree[tree[i].suffixEdg].flag += tree[i].flag;
		totalCount += tree[i].flag;
	}

	// printing all of its distinct palindromic 
	// substring 
	cout << "All " << ptr - 2 << " distinct palindromic substring for " << s << " : \n";
	for (int i = 3; i <= ptr; i++)
	{
		cout << i - 2 << ") ";
		for (int j = tree[i].start; j <= tree[i].end; j++)
			cout << s[j];

		cout << ", " << tree[i].flag + 1;
		cout << endl;
	}

	// longest palindrome
	int m = 0;
	for (int i = 3; i <= ptr; i++) {
		if (tree[i].length > m) {
			m = tree[i].length;
		}
	}

	cout << "Longest palindrome: ";
	for (int i = 3; i <= ptr; i++) {
		if (tree[i].length == m) {
			for (int j = tree[i].start; j <= tree[i].end; j++)
				cout << s[j];
			cout << endl;
			break;
		}
	}
	// longest palindrome

	//system("PAUSE");

	return 0;
}
