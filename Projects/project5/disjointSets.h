#pragma once
#include <iostream>
#include <iomanip>
#include <stack>

using namespace std;

class DisjointSets {
public:
	DisjointSets(int nums) {
		n = nums;
		equivClasses = new int[n];
		// set all of the initial equivalence classes to -1
		for (int i = 0; i < n; i++)
			equivClasses[i] = -1;
	}

	~DisjointSets() {
		// deallocate the equivalence classes array
		delete[] equivClasses;
	}

	// perform the find operation on "parent"
	int find(int parent) {
		// if the current equivalence class has no parent (= -1), return the parent
		if (equivClasses[parent] < 0)
			return parent;
		// otherwise, make a recursive call with the parent equivalence class
		else
			return find(equivClasses[parent]);
	}

	// unions "parent" and "child"
	void unionSets(int set1, int set2) {
		// perform the find operation on the parent and child equivalence classes
		set1 = find(set1);
		set2 = find(set2);

		// if the parent and child equivalence classes are not equal 
		if (set1 != set2) {
			// if the set1 tree is bigger than the set2 tree
			if (equivClasses[set1] > equivClasses[set2]) {
				// push the set1's size/rep and set1 on the stack
				unions.push(pair<int, int>(equivClasses[set1], set1));

				// add the size of the set1 tree to the size of the set2 tree and make set1 a subtree of set2
				equivClasses[set2] += equivClasses[set1];
				equivClasses[set1] = set2;
			}
			//if the set2 tree is bigger than the set1 tree or the trees are equal size
			else {
				// push the set2's size/rep and set2 on the stack
				unions.push(pair<int, int>(equivClasses[set2], set2));

				// add the size of the set2 tree to the size of the set1 tree and make set2 a subtree of set1
				equivClasses[set1] += equivClasses[set2];
				equivClasses[set2] = set1;	
			}
		}	
	}
	
	// reverts the most recent union operation
	void split() {
		// if the union stack is not empty
		if (!unions.empty()) {
			// get the previous union information and pop it off the stack
			pair<int, int> p = unions.top();
			unions.pop();

			// get the parent of the most recent child that was unioned
			int par = find(p.second);

			// adjust the size of the tree after undoing the union and update the parent of the most recent child in the union to its previous parent
			equivClasses[par] -= p.first;
			equivClasses[p.second] = p.first;
		}
	}

	// displays the current values of the disjoint sets
	void displaySets() {
		// display top table border
		cout << "+";
		for (int i = 0; i < n*ceil(log(n)); i++) cout << "-";
		cout << "+\n|";

		// display data
		for (int i = 0; i < n; i++) cout << setw(ceil(log(n))) << i;
		cout << "|\n|";;
		for (int i = 0; i < n; i++) cout << setw(ceil(log(n))) << equivClasses[i];

		// display bottom table border
		cout << "|\n+";
		for (int i = 0; i < n*ceil(log(n)); i++) cout << "-";
		cout << "+\n|";
	}

private:
	// "n" is the number of disjoint sets, "equivClasses" holds the equivalence class values, and "unions" holds the history of union operations
	int n;
	int *equivClasses;
	// pair.first = prev size of p.second. p.second is the set
	stack<pair<int, int>> unions;
};
