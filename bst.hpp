/**
 * Yusuf Pisan pisan@uw.edu
 * 15 Jan 2018
 *
 * Creates a BST to store values
 * Uses Node which holds the Data
 * Uses templates to store any type of Data
 * Uses inorder, preorder, and postorder to traverse a tree
 * Prints the tree in multiple ways
 * Rebalance is used to create a balanced tree
 * Can modify tree using add/remove functions
 * Can check the height of tree, elements that the tree
 * contains, and if the tree is empty
 * binarysearchtreee.cpp file is included at the bottom of the .h file
 * binarysearchtreee.cpp is part of the template, cannot be compiled separately
 *
 * Edited by Sambhavi Pandey
 * Last modified on October 20, 2019
 */

#ifndef BST_HPP
#define BST_HPP

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

template<class T>
class BST {
	// display BST tree in a human-readable format
	friend ostream &operator<<(ostream &Out, const BST &Bst) {
		Bst.printSideways(Out, Bst.Root);
		Out << endl;
		Bst.printVertical(Out, Bst.Root);
		return Out;
	}

private:
	// Node for BST
	struct Node {
		T Data;
		struct Node *Left;
		struct Node *Right;
	};

	// refer to data type "struct Node" as Node
	using Node = struct Node;

	// root of the tree
	Node *Root{ nullptr };

	// height of a Node, nullptr is 0, Root is 1, static, no access to 'this'
	static int getHeight(const Node *N) {
		if (N == nullptr)
		{
			return 0;
		}
		return 1;
	}

	/**
	 * print tree sideways with root on left
				  6
			  2
				  5
		  0
				  4
			  1
				  3
	 */
	static ostream &printSideways(ostream &Out, const Node *Curr, int Level = 0) {
		const static char SP = ' ';
		const static int ReadabilitySpaces = 4;
		if (!Curr)
			return Out;
		printSideways(Out, Curr->Right, ++Level);
		Out << setfill(SP) << setw(Level * ReadabilitySpaces) << SP;
		Out << Curr->Data << endl;
		printSideways(Out, Curr->Left, Level);
		return Out;
	}

	static ostream &centeredPrint(ostream &Out, int Space,
		const string &Str, char FillChar = ' ') {
		auto StrL = static_cast<int>(Str.length());
		int Extra = (Space - StrL) / 2;
		if (Extra > 0) {
			Out << setfill(FillChar) << setw(Extra + StrL) << Str;
			Out << setfill(FillChar) << setw(Space - Extra - StrL) << FillChar;
		}
		else {
			Out << setfill(FillChar) << setw(Space) << Str;
		}
		return Out;
	}

	/**
	 * print tree with the root at top
	 *
		_____0______
	 __1___      __2___
	3     4     5     6
	 *
	**/
	static ostream &printTreeLevel(ostream &Out, queue<const Node *> &Q,
		int Width, int Depth, int MaxDepth) {
		const static char SP = ' ';
		const static char UND = '_';
		int Nodes = 0;
		int MaxN = pow(2, Depth - 1);
		int SpaceForEachItem = Width * pow(2, MaxDepth - 1) / MaxN; // NOLINT
		string
			Bigspace = string(static_cast<uint64_t>(SpaceForEachItem / 4), SP);
		while (Nodes++ < MaxN) {
			const Node *Tp = Q.front();
			Node *TpL = nullptr;
			Node *TpR = nullptr;
			Q.pop();
			string Label = "N";
			if (Tp) {
				stringstream Ss;
				Ss << Tp->Data;
				Label = Ss.str();
				TpL = Tp->Left;
				TpR = Tp->Right;
			}
			char Filler = Depth == MaxDepth ? SP : UND;
			if (Depth == MaxDepth) {
				centeredPrint(Out, SpaceForEachItem, Label, Filler);
			}
			else {
				Out << Bigspace;
				centeredPrint(Out, SpaceForEachItem / 2, Label, Filler);
				Out << Bigspace;
				Q.push(TpL);
				Q.push(TpR);
			}
		}
		Out << endl;
		return Out;
	}

	// helper function for displaying tree sideways, works recursively
	static ostream &printVertical(ostream &Out, Node *Curr) {
		const static int WIDTH = 6;  // must be even
		if (!Curr)
			return Out << "[__]";
		// figure out the maximum depth which determines how wide the tree is
		int MaxDepth = getHeight(Curr);
		queue<const Node *> Q;
		Q.push(Curr);
		for (int Depth = 1; Depth <= MaxDepth; ++Depth) {
			printTreeLevel(Out, Q, WIDTH, Depth, MaxDepth);
		}
		return Out;
	}

  //Additional private functions 
  /*
   * This is a helper function that is used to add
   * a node to the BST
   * @param: Takes in a Node pointer, takes in
   * const T reference
   * @return: bool corresponding to if if was added
   * or not
   */
	bool addHelper(Node *N, const T &Item) {
		//If the Item is less than the data
		if (Item < N->Data) {
			//Goes left 
			if (N->Left == nullptr) {
				N->Left = makeNode(Item);
				return true;
			}
				return addHelper(N->Left, Item);
		}
		//If the Item is greater than or equal to the data
			//Goes right 
			if (N->Right == nullptr) {
				N->Right = makeNode(Item);
				return true;
			}
				return addHelper(N->Right, Item);
	}

	/*
	 * This is a helper function that is used to count
	 * the number of nodes in the BST.
	 * @param: Takes in a Node pointer
	 * @return: integer corresponding to number of nodes
	 */
	int countHelper(Node *N)const {
		if (N == nullptr) {
			return 0;
		}
		return 1 + countHelper(N->Left) + countHelper(N->Right);
	}

	/*
	* This is a helper function that is used to check if
	* two BST's are equal.
	* @param: Takes in two node pointers
	* @return: Boolean corresponding to if the BST's are
	* equal or not
	*/
	bool checkEquality(Node *N1, Node *N2)const {
		//If both are null
		if (N1 == nullptr && N2 == nullptr) {
			return true;
		}
		//If one is null and the other is not 
		if ((N1 == nullptr && N2 != nullptr) || (N1 != nullptr && N2 == nullptr)) {
			return false;
		}
		//If they are not equal to each other 
		if (N1->Data != N2->Data) {
			return false;
		}
		return checkEquality(N1->Left, N2->Left) && checkEquality(N1->Right, N2->Right);
	}

	/*
	 * Function deletes nodes that are not the root
	 * @param: Takes in a const T reference
	 * @return: Nothing
	 */
	void deleteNode(const T &Item) const {
		//Declaring Node pointers
		Node* N = Root;
		Node* Parent = nullptr;
		//While true
		while (true) {
			if (N->Data == Item) {
				break;
			}
			//Otherwise if Item is less than value
			else if (Item < N->Data) {
				Parent = N;
				N = N->Left;
			}
			//If Item is greater than value 
			else {
				Parent = N;
				N = N->Right;
			}
		}
		//If there are no children
		if (N->Left == nullptr && N->Right == nullptr) {
			if (Parent->Left == N) {
				Parent->Left = nullptr;
				delete N;
				return;
			}
				Parent->Right = nullptr;
				delete N;
				return;
		}
		//If the tree has a right node
		if (N->Left == nullptr) {
			if (Parent->Left == N) {
				Parent->Left = N->Right;
				delete N;
				return;
			}
				Parent->Right = N->Right;
				delete N;
				return;

		}
		//If the tree has a left node 
	    if (N->Right == nullptr) {
			if (Parent->Left == N) {
				Parent->Left = N->Left;
				delete N;
				return;
			}
				Parent->Right = N->Left;
				delete N;
				return;
		}
		//If it has two children 
			T Max = removeMax(N);
			N->Data = Max;
			return;
	}

	/*
	 * Function deletes nodes that are the root
	 * nodes
	 * @param: Nothing
	 * @return: Nothing
	 */
	void deleteNodeRoot() {
		if (Root->Left == nullptr && Root->Right == nullptr) {
			delete Root;
			Root = nullptr;
			return;
		}
		//If the Root has a right node 
		if (Root->Left == nullptr) {
			Node* N = Root;
			Root = Root->Right;
			delete N;
			return;
		}
		//If the Root has left node
	    if (Root->Right == nullptr) {  
			Node* N = Root;
			Root = Root->Left;
			delete N;
			return;
		}
		//Root has two nodes
			T Max = removeMax(Root);
			Root->Data = Max;
			return;
	}

	/*
	 * This is a helper function that is used to conduct
	 * an inorder traversal.
	 * @param: Takes in a const T reference and Node pointer
	 * @return: Does not return anything
	 */
	void inOrderHelper(void Visit(const T &Item), Node* N) const {
		//If the pointer is pointing to some value
		if (N != nullptr) {
			//Go left
			inOrderHelper(Visit, N->Left);
			//Go root 
			T Item = N->Data;
			Visit(Item);
			//Go right 
			inOrderHelper(Visit, N->Right);
		}
	}

	/*
	 * This is a helper function that is used to conduct
	 * a preorder traversal.
	 * @param: Takes in a const T reference and Node pointer
	 * @return: Does not return anything
	 */
	void preOrderHelper(void Visit(const T &Item), Node *N)const {
		//If the pointer is pointing to some value
		if (N != nullptr){
			//Go root
			T Item = N->Data;
			Visit(Item);
			//Go left
			preOrderHelper(Visit, N->Left);
			//Go right 
			preOrderHelper(Visit, N->Right);
		}
	}

	/*
	 * This is a helper function that is used to conduct
	 * a postorder traversal.
	 * @param: Takes in a const T reference and Node pointer
	 * @return: Does not return anything
	 */
	void postOrderHelper(void Visit(const T &Item), Node *N)const {
		//If the pointer is pointing to some value
		if (N != nullptr){
			//Go left
			postOrderHelper(Visit, N->Left);
			//Go right 
			postOrderHelper(Visit, N->Right);
			//Go root 
			T Item = N->Data;
			Visit(Item);
		}
	}

	/*
	 * This is a helper function that is used to help copy
	 * the BST.
	 * @param: Takes in a Node pointer
	 * @return: Node pointer corresponding to the copied BST
	 */
	Node *copyHelper(const Node* N){
		if (N){
			add(N->Data);
			copyHelper(N->Left);
			copyHelper(N->Right);
		}
	}

	/*
	 * This is a helper function that is used to help clear 
	 * the tree
	 * @param: Takes in a Node pointer
	 * @return: Nothing 
	 */
	void clearHelper(Node* N) {
		if (N != nullptr) {
			clearHelper(N->Left);
			clearHelper(N->Right);
			delete N;
		}
	}


	/*
	 * Function removes max (so largest node)
	 * @param: Takes in Node pointer
	 * @return: T (node)
	 */
	static T removeMax(Node* N) {
		Node* R = N;
		Node* Node = N->Right;
		T Temp;

		if (Node->Left == nullptr) {
			R->Right = Node->Right;
			Temp = Node->Data;
			delete Node;
			return Temp;
		}
		while (Node->Left != nullptr) {
			R = Node;
			Node = Node->Left;
		}
		R->Left = Node->Right;
		Temp = Node->Data;
		delete Node;
		return Temp;
	}

	/*
	 * Function takes tree and converts to array 
	 * @param: Takes in Node pointer, array of type T, 
	 * and a int reference
	 * @return: Nothing
	 */
	void treeToArray(Node* N, T Array[], int& Item) const {
		if (N == nullptr)
			return;

		treeToArray(N->Left, Array, Item);
		Array[Item++] = N->Data;
		treeToArray(N->Right, Array, Item);
	}

	/*
	 * Function makes a tree with minimum height 
	 * @param: Takes in a array of type t, takes in an int
	 * @return: Nothing
	 */
	void readTree(T Array[], int N) {
		//Declaring variable 
		int Num = N - 1;
		//Going through array 
		for (int I = 1; I < Num; I++) {
			if (Array[I - 1] > Array[I])
				return;
		}
		
		clear();
		//Declaring 
		int Begin = 0;
		int End = Num;
		Root = readTreeHelper(Array, Begin, End);
	}

	/*
	 * Function helps read tree.
	 * @param: Takes in an array of type T and two int
	 * @return: Node pointer
	 */
	Node* readTreeHelper(T Array[], int Begin, int End) {
		if (Begin > End)
			return nullptr;

		int Middle = (Begin + End) / 2;
		Node* N = makeNode(Array[Middle]);
		N->Left = (readTreeHelper(Array, Begin, Middle - 1));
		N->Right = (readTreeHelper(Array, Middle + 1, End));

		return N;
	}

	/*
	 * This function makes a new BST node
	 * @param: Takes in a const T reference
	 * @return: Node pointer corresponding to the new BST node
	 */
	Node *makeNode(const T &Item) const {
		//Creates new node 
		auto *NewNode = new Node;
		//Pointer points to data
		NewNode->Data = Item;
		NewNode->Left = nullptr;
		NewNode->Right = nullptr;
		return NewNode;
	}

public:
	/*
	 * This is a constructor, empty tree which sets
	 * the root to nullptr
	 * @param: None
	 * @return: None
	 */
	BST() {
		Root = nullptr;
	}

	/*
	 * This is a constructor, tree with root. Sets root to
	 * makeNode(RootItem).
	 * @param: Takes in a const T reference
	 * @return: Nothing
	 */
	explicit BST(const T &RootItem) {
		Root = makeNode(RootItem);
	}

	/*
	 * This is a constructor that given an array of
	 * length n, creates a tree to have all items i that
	 * array with the minimum height (rebalance)
	 * @param: Takes in T array, integer
	 * @return: Nothing
	 */
	 // NOLINTNEXTLINE
	BST(const T Arr[], int N) {
		Root = makeNode(Arr[0]);

		for (int I = 1; I < N; I++) {
			add(Arr[I]);
		}
		rebalance();
	}

	/*
	 * This is a copy constructor, it calls
	 * copy helper.
	 * @param: Takes in a const BST<T> reference
	 * @return: Nothing
	 */
	BST(const BST<T> &Bst) {
		copyHelper(Bst.Root);
	}

	/*
	 * This is a destructor
	 * @param: None
	 * @return: None
	 */
	virtual ~BST() {
		clear();
	}

	/*
	 * Function that checks if the BST is
	 * empty.
	 * @param: None
	 * @return: Boolean, true if no nodes. False
	 * if there are nodes in BST
	 */
	bool isEmpty() const {
		if (Root == nullptr)
		{
			return true;
		}
		return false;
	}

	/*
	 * Functions that determines height of tree
	 * @param: None
	 * @return: Integer corresponding to height
	 * of tree
	 */
	int getHeight() const {
		return heightCount(Root);
	}

	/*
	 * Helper function to determine height of tree.
	 * @param: Node pointer
	 * @return: Integer corresponding to height
	 * of tree
	 */
	int heightCount(Node *Height) const {
		if (Height == nullptr){
			return 0;
		}
			int LeftHeight = heightCount(Height->Left);
			int RightHeight = heightCount(Height->Right);
			if (LeftHeight > RightHeight){
				return (LeftHeight + 1);
			}
				return (RightHeight + 1);
	}

	/*
	 * Function that determines the number of nodes
	 * in the BST, calls helper function.
	 * @param: None
	 * @return: Int corresponding to number of nodes in BST
	 */
	int numberOfNodes() const {
		return countHelper(Root);
	}

	/*
	 * Function that adds a new item. Calls helper function.
	 * @param: Takes in a const T reference
	 * @return: Boolean corresponding to if the add was
	 * successful or not
	 */
	bool add(const T &Item) {
		if (Root == nullptr) {
			Root = makeNode(Item);
			return true;
		}
		return addHelper(Root, Item);
	}

	/*
	 * Function that removes item. Calls helper
	 * function.
	 * @param: Takes in a const T reference
	 * @return: Boolean corresponding to if the
	 * remove was succesful or not.
	 */
	bool remove(const T &Item) {
		if (!contains(Item))
			return false;
		if (Root->Data == Item) {
			deleteNodeRoot();
			return true;
		}
			deleteNode(Item);
			return true;
	}

	/*
	 * Function that determines if the item is in BST.
	 * Calls helper function.
	 * @param: Takes in a const T reference
	 * @return: Boolean corresponding to if the item is
	 * in BST.
	 */
	bool contains(const T &Item) const {
		if (Root == nullptr)
			return false;

		Node* N = Root;
		while (N != nullptr) {
			if (N->Data == Item)
				return true;
			if (N->Data > Item)
				N = N->Left;
			else
				N = N->Right;
		}
		return false;
	}

	/*
	 * Function that does inorder traversal. Calls helper function.
	 * @param: Takes in a const T reference
	 * @return: Nothing
	 */
	void inOrderTraverse(void Visit(const T &Item)) const {
		inOrderHelper(Visit, Root);
	}

	/*
	 * Function that does preorder traversal. Calls helper function.
	 * @param: Takes in a const T reference
	 * @return: Nothing
	 */
	void preOrderTraverse(void Visit(const T &Item)) const {
		preOrderHelper(Visit, Root);
	}

	/*
	 * Function that does postorder traversal. Calls helper function.
	 * @param: Takes in a const T reference
	 * @return: Nothing
	 */
	void postOrderTraverse(void Visit(const T &Item)) const {
		postOrderHelper(Visit, Root);
	}

	/*
	 * Function that creates dynamic array, copies 
	 * items to the array, reads the array to re-create tree
	 * from scratch so resulting tree is balanced 
	 * @param: Nothing
	 * @return: Nothing
	 */
	void rebalance() {
		//Creating array
		auto* Array = new T[numberOfNodes()];

		//Declaring variable 
		int Count = 0;
		
		//Calling helper functions 
		treeToArray(Root, Array, Count);
		readTree(Array, numberOfNodes());

		//Deleting 
		delete[] Array;
	}

	/*
	 * clears tree 
	 * @param: Nothing
	 * @return: Nothing
	 */
	void clear() {
		clearHelper(Root);
		Root = nullptr;
	}

	/*
	 * Function that checks if the trees are equal.
	 * The trees are equal if they have the same
	 * structure and the same item values at all nodes.
	 * @param: Takes in a const T reference
	 * @return: Boolean corresponding to if the trees
	 * are equal or not.
	 */
	bool operator==(const BST<T> &Other) const {
		//Calls helper function 
		return checkEquality(Root, Other.Root);
	}

	/*
	 * Function that checks if the trees are not equal.
	 * Calls helper function.
	 * @param: Takes in a const T reference
	 * @return: Boolean corresponding to if the trees
	 * are not equal or not.
	 */
	bool operator!=(const BST<T> &Other) const {
		//Calls helper function 
		return !checkEquality(Root, Other.Root);
	}
};
#endif  // BST_HPP