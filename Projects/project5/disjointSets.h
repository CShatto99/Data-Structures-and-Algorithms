#include <iostream>
#include <iomanip>
#include <stack>
#include <math.h>

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
	void unionSets(int parent, int child) {
		// perform the find operation on the parent and child equivalence classes
		parent = find(parent);
		child = find(child);

		// if the parent and child equivalence classes are not equal 
		if (parent != child) {
			// set the parent of the child equivalence class to "parent" and push the child to the union stack
			equivClasses[child] = parent;
			unions.push(child);
		}	
	}
	
	// reverts the most recent union operation
	void split() {
		// if the untion stack is not empty
		if (!unions.empty()) {
			// set the parent of the most recent child that was unioned to -1 (no parent) and pop the union off the stack
			equivClasses[unions.top()] = -1;
			unions.pop();
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
	stack<int> unions;
};
