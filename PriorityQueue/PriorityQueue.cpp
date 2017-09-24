// PriorityQueue.cpp : Defines the entry point for the console application.
//

#include <queue>
#include <iostream>
#include "BinaryHeapQueue.h"

using namespace std;

template<typename T>
void print_queue(T& q) {
	while (!q.empty()) {
		std::cout << q.top() << " ";
		q.pop();
	}
	std::cout << '\n';
}

int main()
{
	algs::BinaryHeapQueue<int> hq;
	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
	{
		hq.push(n);
	}
	print_queue(hq);
		
	algs::BinaryHeapQueue<int, std::greater<int>> queueGreater;
	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
	{
		queueGreater.push(n);
	}
	print_queue(queueGreater);

	auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
	algs::BinaryHeapQueue<int, decltype(cmp)> q3(cmp);
	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
	{
		q3.push(n);
	}
	print_queue(q3);
	
	return 0;
}

