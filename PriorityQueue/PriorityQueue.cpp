// PriorityQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>


int main()
{
	std::vector<int> v(10);
	v[5] = 2;

	for (int x : v)
		std::cout << x << " ";
	std::cout << std::endl;
	return 0;
}

