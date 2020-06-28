/*
	Name: Cameron Shatto
	Course Section: CSCE 3110.021
	Date: 6/23/2020
	Description: This program simulates the mathematical concept of disjoint sets via a user menu that supports the find, union, and split operations.
*/

#include "disjointSets.h"
#include <string>

using namespace std;

int main() {
	// "n" is the number of initially disjoint sets, "set1" and "set2" will be used in the find and untion operations, "ds" is the disjoint sets object, and "option" is the user menu option
	int n = 8, set1, set2;
	DisjointSets ds(n);
	string option;

	while (1) {
		// display the current disjoint sets
		ds.displaySets();

		// display the user menu while the user enters an incorrect option
		do {
			cout << "Enter option choice 1 - 4:\n";
			cout << "(1) Find Operation\n";
			cout << "(2) Union-By-Size Operation\n";
			cout << "(3) Split Operation\n";
			cout << "(4) Exit Program\n";
			cin >> option;
		} while (option[0] < '1' || option[0] > '4');

		// perform the find operation
		if (option[0] == '1') {
			// get a valid set number from the user
			do {
				cout << "Enter 1 set #: ";
				cin >> set1;
				cin.clear();
			} while (set1 < 0 || set1 >= n);

			// display set and the set's parent
			int parent = ds.find(set1);
			if (parent < 0) cout << "Parent of " << set1 << " is " << set1 << endl;
			else cout << "Parent of " << set1 << " is " << parent << endl;
		}
		// perform the union operation
		else if (option[0] == '2') {
			// get the two valid set numbers from the user
			do {
				cout << "Enter 2 set #s: ";
				cin >> set1 >> set2;
				cin.clear();
			} while (set1 < 0 || set2 < 0 || set1 >= n || set2 >= n);

			// union the two sets
			ds.unionSets(set1, set2);
		}
		// perform the split operation
		else if (option[0] == '3') {
			ds.split();
		}
		// terminate the program
		else {
			exit(0);
		}
	}
}
