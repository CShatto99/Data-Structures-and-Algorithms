#pragma once
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree() : root{ nullptr } {
	}

	/**
	* Copy constructor
	*/
	BinarySearchTree(const BinarySearchTree & rhs) : root{ nullptr } {
		root = clone(rhs.root);
	}

	/**
	* Move constructor
	*/
	BinarySearchTree(BinarySearchTree && rhs) : root{ rhs.root } {
		rhs.root = nullptr;
	}

	/**
	* Destructor for the tree
	*/
	~BinarySearchTree() {
		makeEmpty();
	}

	/**
	* Copy assignment
	*/
	BinarySearchTree & operator=(const BinarySearchTree & rhs) {
		BinarySearchTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	/**
	* Move assignment
	*/
	BinarySearchTree & operator=(BinarySearchTree && rhs) {
		std::swap(root, rhs.root);
		return *this;
	}


	/**
	* Find the smallest item in the tree.
	* Throw UnderflowException if empty.
	*/
	const Comparable & findMin() const {
		if (isEmpty())
			throw UnderflowException{};
		return findMin(root)->element;
	}

	/**
	* Find the largest item in the tree.
	* Throw UnderflowException if empty.
	*/
	const Comparable & findMax() const {
		if (isEmpty())
			throw UnderflowException{};
		return findMax(root)->element;
	}

	/**
	* Returns true if x is found in the tree.
	*/
	bool contains(const Comparable & x) {
		return contains(x, root, root);
	}

	/**
	* Test if the tree is logically empty.
	* Return true if empty, false otherwise.
	*/
	bool isEmpty() const {
		return root == nullptr;
	}

	/**
	* Print the tree contents in sorted order.
	*/
	void printTree(ostream & out = cout) const {
		if (isEmpty())
			out << "Empty tree" << endl;
		else
			printTree(root, out);
	}

	/**
	* Make the tree logically empty.
	*/
	void makeEmpty() {
		makeEmpty(root);
	}

	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(const Comparable & x) {
		insert(x, root, root);
	}

	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(Comparable && x) {
		insert(std::move(x), root, root);
	}

	/**
	* Remove x from the tree. Nothing is done if x is not found.
	*/
	void remove(const Comparable & x) {			
		remove(x, root);
	}

private:
	struct BinaryNode {
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;
		BinaryNode *parent;

		BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt)
			: element{ theElement }, left{ lt }, right{ rt }, parent{ pt } { }

		BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt)
			: element{ std::move(theElement) }, left{ lt }, right{ rt }, parent{ pt } { }
	};

	BinaryNode *root;


	/**
	* Internal method to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(const Comparable & x, BinaryNode * & t, BinaryNode * & pt) {
		if (t == nullptr) {
			t = new BinaryNode{ x, nullptr, nullptr, pt };
			splay(t);
			cout << "Insert (" << x << ") complete\n";
		}
		else if (x < t->element) {
			insert(x, t->left, t);
		}
		else if (t->element < x) {
			insert(x, t->right, t);
		}
		else
			;  // Duplicate; do nothing
	}

	/**
	* Internal method to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(Comparable && x, BinaryNode * & t, BinaryNode * & pt) {
		if (t == nullptr) {
			t = new BinaryNode{ std::move(x), nullptr, nullptr, pt };
			splay(t);
			cout << "Insert (" << x << ") complete\n";
		}
		else if (x < t->element) {
			insert(std::move(x), t->left, t);
		}
		else if (t->element < x) {
			insert(std::move(x), t->right, t);
		}
		else
			;  // Duplicate; do nothing
	}

	/**
	* Internal method to remove from a subtree.
	* x is the element to remove.
	* t is the node that roots the subtree.
	*/
	void remove(const Comparable & x, BinaryNode * & t) {
		if (!t->left && !t->right)
			t = nullptr;
		else {
			BinaryNode* oldRoot;
			oldRoot = t;
			if (!t->left)
				t = t->right;
			else {
				BinaryNode* newRoot = findMax(t->left);
				splay(newRoot);
				t->right = oldRoot->right;
			}
			delete(oldRoot);
		}		
	}

	/**
	* Internal method to find the smallest item in a subtree t.
	* Return node containing the smallest item.
	*/
	BinaryNode * findMin(BinaryNode *t) const {
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		return findMin(t->left);
	}

	/**
	* Internal method to find the largest item in a subtree t.
	* Return node containing the largest item.
	*/
	BinaryNode * findMax(BinaryNode *t) const {
		if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;
	}

	/**
	* Internal method to test if an item is in a subtree.
	* x is item to search for.
	* if x is found, t is splayed to the root.
	* if x is not found, the last accessed node is splayed to the root.
	*/
	bool contains(const Comparable & x, BinaryNode *t, BinaryNode *pt) {
		if (t == nullptr) {
			splay(pt);
			return false;
		}
		else if (x < t->element)
			return contains(x, t->left, t);
		else if (t->element < x)
			return contains(x, t->right, t);
		else {
			splay(t);
			return true;
		}
	}
	/****** NONRECURSIVE VERSION*************************
	bool contains( const Comparable & x, BinaryNode *t ) const {
	while( t != nullptr )
	if( x < t->element )
	t = t->left;
	else if( t->element < x )
	t = t->right;
	else
	return true;    // Match

	return false;   // No match
	}
	*****************************************************/

	/**
	* Internal method to make subtree empty.
	*/
	void makeEmpty(BinaryNode * & t) {
		if (t != nullptr) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			makeEmpty(t->parent);
			delete t;
		}
		t = nullptr;
	}

	/**
	* Internal method to print a subtree rooted at t in inorder, preorder, and postorder.
	*/
	void printTree(BinaryNode *t, ostream & out) const {
		out << "inorder   traversal : ";
		printInorder(t, out);
		out << endl;
		out << "preorder  traversal : ";
		printPreorder(t, out);
		out << endl;
		out << "postorder traversal : ";
		printPostorder(t, out);
		out << endl;
	}

	/**
	* Internal method to perform an inorder traversal on a subtree rooted at t.
	*/
	void printInorder(BinaryNode *t, ostream & out) const {
		if (t != nullptr) {
			printInorder(t->left, out);
			out << t->element << " ";
			printInorder(t->right, out);
		}
	}
	/**
	* Internal method to perform a preorder traversal on a subtree rooted at t.
	*/
	void printPreorder(BinaryNode *t, ostream & out) const {
		if (t != nullptr) {
			out << t->element << " ";
			printPreorder(t->left, out);
			printPreorder(t->right, out);
		}
	}
	/**
	* Internal method to perform a postorder traversal on a subtree rooted at t.
	*/
	void printPostorder(BinaryNode *t, ostream & out) const {
		if (t != nullptr) {
			printPostorder(t->left, out);
			printPostorder(t->right, out);
			out << t->element << " ";
		}
	}

	/**
	* Internal method to clone subtree.
	*/
	BinaryNode * clone(BinaryNode *t) const {
		if (t == nullptr)
			return nullptr;
		else
			return new BinaryNode{ t->element, clone(t->left), clone(t->right), clone(t->parent) };
	}

	/**
	* Internal method to perform a right rotation on some node t.
	*/
	void rightRotate(BinaryNode *t) {
		BinaryNode  *y = t->left;

		t->left = y->right;

		if (y->right != nullptr)
			y->right->parent = t;

		y->parent = t->parent;

		if (t->parent == nullptr) this->root = y;
		else if (t == t->parent->right) t->parent->right = y;
		else t->parent->left = y;

		y->right = t;
		t->parent = y;
	}

	/**
	* Internal method to perform a left rotation on some node t.
	*/
	void leftRotate(BinaryNode *t) {
		BinaryNode *y = t->right;

		t->right = y->left;

		if (y->left != nullptr)
			y->left->parent = t;

		y->parent = t->parent;

		if (t->parent == nullptr) this->root = y;
		else if (t == t->parent->left) t->parent->left = y;
		else t->parent->right = y;

		y->left = t;
		t->parent = y;
	}
	
	/**
	* Internal method perform a splay operation on some node t
	*/
	void splay(BinaryNode *t) {
		while (t->parent != nullptr) {
			if (t->parent->parent == nullptr) {
				// t requires a zag rotation
				if (t == t->parent->right) leftRotate(t->parent);
				// t requires a zig rotation
				else rightRotate(t->parent);
			}
			// t requires a zag-zag rotation
			else if (t == t->parent->right && t->parent == t->parent->parent->right) {
				leftRotate(t->parent->parent);
				leftRotate(t->parent);
			}
			// t requires a zig-zig rotation
			else if (t == t->parent->left && t->parent == t->parent->parent->left) {
				rightRotate(t->parent->parent);
				rightRotate(t->parent);
			}
			// t requires a zag-zig rotation
			else if (t == t->parent->left && t->parent == t->parent->parent->right) {
				rightRotate(t->parent);
				leftRotate(t->parent);
			}
			// t requires a zig-zag rotation
			else if (t == t->parent->right && t->parent == t->parent->parent->left) {
				
				leftRotate(t->parent);
				rightRotate(t->parent);
			}
		}
	}
	
};

#endif