// BSTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "BST.h"

using namespace std;

char shiftA(int x)
{
	return static_cast<char>('A' + x - 1);
}

int main()
{
	BST<int, char> tree;
	tree.insert(5, shiftA(5));
	tree.insert(2, shiftA(2));
	tree.insert(3, shiftA(3));
	tree.insert(1, shiftA(1));
	tree.insert(7, shiftA(7));
	tree.insert(8, shiftA(8));
	tree.insert(6, shiftA(6));

	tree.print();
	cout << endl;

	auto value = tree.find(7);
	cout << *value << endl;

	auto min = tree.min();
	cout << "Min " << min.first << " " << min.second << endl;

	auto max = tree.max();
	cout << "Max " << max.first << " " << max.second << endl;

	auto successor = tree.successor(5);
	cout << "Succ 5 " << *successor << endl;

	successor = tree.successor(3);
	cout << "Succ 3 " << *successor << endl;

	auto pred = tree.predecessor(5);
	cout << "Pred 5 " << *pred << endl;

	pred = tree.predecessor(1);
	cout << "Pred 1 " << (pred == nullptr ? "null" : to_string(*pred)) << endl;

	tree.remove(5);
	tree.print();

	return 0;
}

