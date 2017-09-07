// RBTree.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "RBTree.h"
#include "RBTreeVisuzlizer.h"
#include <map>
#include <random>

using namespace std;

int main()
{
	algs::RBTree<int, int> rb_tree;
	
	for (int x = 100; x > 0; x--)
	{
		rb_tree.insert(x, x);		
	}

	algs::RBTreeVisualizer<int, int, less<int>> visualizer(rb_tree);
	string filename = "rbTree.dot";
	visualizer.saveDot(filename);

	cout << "RB Tree Height " << rb_tree.height() << endl;
		
	for (int x = 100; x > 50; x--)
	{
		rb_tree.remove(x);		
	}

	cout << "RB Tree Height " << rb_tree.height() << endl;
	
	return 0;
}

