// RBTree.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "RBTree.h"
#include "RBTreeVisuzlizer.h"
#include <map>
#include <random>
#include "RandomizedBST.h"
#include "RandomizedBSTVisualizer.h"

using namespace std;

int main()
{
	srand(NULL);

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

	for (int k = 0; k < 2; k++)
	{
		algs::RandomizedBST<int, int> rnd_tree;
		algs::RandomizedBSTVisualizer<int, int, less<int>> rnd_visualizer(rnd_tree);

		for (int x = 100; x > 0; x--)
		{
			rnd_tree.insert(x, x);
		}

		rnd_visualizer.saveDot(string("rndTree") + to_string(k) + ".dot");
		cout << "Randomized Tree Height " << rnd_tree.height() << endl;

		for (int x = 100; x > 50; x--)
		{
			rnd_tree.remove(x);
		}

		rnd_visualizer.saveDot(string("rndTree_delete") + to_string(k) + ".dot");
		cout << "Randomized Tree Height " << rnd_tree.height() << endl;
	}
	
	return 0;
}

