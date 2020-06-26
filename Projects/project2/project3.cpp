/*
	Name: Cameron Shatto
	Course Section: CSCE 3110.021
	Date: 6/21/2020
	Description: This program implements a fully functional splay tree on top of a binary search tree.
*/

#include <iostream>
#include <string>
#include "bstSplay.h"

using namespace std;

template <typename T>
void simulateTree(string dataType);

int main() {
	// "dataType" will hold the data type of the splay tree
	string dataType;

	// get the splay tree data type
	cout << "What splay tree data type (int, float, char)? ";
	cin >> dataType;

	// if the data type is not one of the supported data types, terminate the program
	if (dataType != "int" && dataType != "float" && dataType != "char") {
		cout << "Unknown data type (" << dataType << "). Terminating..." << endl;
		exit(-1);
	}

	// if the data type is an int, start the tree simulation with an int splay tree
	else if (dataType[0] == 'i') simulateTree<int>("integer");
	
	// if the data type is a float, start the tree simulation with a float splay tree
	else if (dataType[0] == 'f') simulateTree<float>("floating-point number");
	
	// if the data type is a char, start the tree simulation with a char splay tree
	else simulateTree<char>("character");
}

template <typename T>
void simulateTree(string dataType) {
	// "bst" is the splay tree, "value" is the current value to insert or remove, and "option" is the current user menu option
	BinarySearchTree<T> bst;
	T value;
	char option;

	// while the program is not terminated
	while (1) {
		// display user menu
		cout << "+------------------------------------------+\n";
		cout << "Enter option choice 1 - 4:\n";
		cout << "(1) insert " << dataType << " into tree\n";
		cout << "(2) remove " << dataType << " from tree\n";
		cout << "(3) print tree traversals\n";
		cout << "(4) exit program\n";
		cout << "+------------------------------------------+\n";
		cin >> option;

		// display the user menu while the user input is invalid
		while (option < '1' || option > '4') {
			cout << "Invalid choice. Try again.\n";
			cout << "+------------------------------------------+\n";
			cout << "Enter option choice 1 - 4:\n";
			cout << "(1) insert " << dataType << " into tree\n";
			cout << "(2) remove " << dataType << " from tree\n";
			cout << "(3) print tree traversals\n";
			cout << "(4) exit program\n";
			cout << "+------------------------------------------+\n";
			cin >> option;
		}

		// if the user option is '1', add "value" to the splay tree
		if (option == '1') {
			cout << "Enter " << dataType << " key to insert: ";
			cin >> value;
			bst.insert(value);
		}
		// if the user opton is '2', remove "value" from the splay tree if it exists
		else if (option == '2') {
			cout << "Enter " << dataType << " key to remove: ";
			cin >> value;
			if (bst.contains(value)) {
				bst.remove(value);
				cout << "Remove (" << value << ") complete\n";
			}

		}
		// if the user option is '3', print the splay tree in inorder, preorder, and postorder orders
		else if (option == '3')
			bst.printTree(cout);

		// if the user option is '4', terminate the program
		else if (option == '4') {
			cout << "Terminating...\n";
			exit(0);
		}
	}
}
