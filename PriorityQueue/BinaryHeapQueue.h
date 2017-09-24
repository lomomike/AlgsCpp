#pragma once
#include <functional>

namespace algs {
	using namespace std;

	template <
		typename TKey,
		typename TComp = less<TKey>
	>
		class BinaryHeapQueue
	{
	public:
		explicit BinaryHeapQueue()
			: comparer(),
			count(0),
			capacity(1)
		{
			heap = new TKey[capacity];
		}

		explicit BinaryHeapQueue(const TComp& comp) 
			: comparer(comp),
			count(0),
			capacity(1)
		{
			heap = new TKey[capacity];
		}

		~BinaryHeapQueue()
		{
			delete[]heap;
			count = 0;
			capacity = 0;
		}

		size_t size() const
		{
			return count;
		}

		bool empty() const
		{
			return size() == 0;
		}

		void push(const TKey& key);

		TKey& top();

		void pop();

		void print()
		{
			for(int i = 0; i < count; ++i)
			{
				cout << heap[i] << " ";
			} 
			cout << endl;
		}

	private:
		static size_t parent(size_t k)
		{
			return (k - 1) / 2;
		}

		static size_t left(size_t k)
		{
			return 2 * k + 1;
		}

		static size_t right(size_t k)
		{
			return 2 * k + 2;
		}

		void fixDown(size_t index);

		void fixUp(size_t index);

		void resize(size_t size)
		{
			auto newHeap = new TKey[size];

			for (size_t i = 0; i < count; ++i)
			{
				newHeap[i] = heap[i];
			}

			delete[]heap;
			heap = newHeap;
		}

	private:
		TComp comparer;
		size_t count;
		size_t capacity;
		TKey* heap;

	};

	template <typename TKey, typename TComp>
	void BinaryHeapQueue<TKey, TComp>::push(const TKey& key)
	{
		heap[count] = key;
		fixUp(count);
		count++;

		if (count == capacity)
		{
			auto newCapacity = capacity * 2;
			resize(newCapacity);
			capacity = newCapacity;
		}
	}

	template <typename TKey, typename TComp>
	TKey& BinaryHeapQueue<TKey, TComp>::top()
	{
		if (count < 1)
			throw std::exception();

		return heap[0];
	}

	template <typename TKey, typename TComp>
	void BinaryHeapQueue<TKey, TComp>::pop()
	{
		if (count < 1)
			throw std::exception();

		swap(heap[0], heap[count - 1]);
		count--;
		fixDown(0);

		if (count == capacity / 4)
		{
			resize(capacity / 2);
			capacity /= 2;
		}
	}

	template <typename TKey, typename TComp>
	void BinaryHeapQueue<TKey, TComp>::fixDown(size_t index)
	{
		auto l = left(index);
		auto r = right(index);

		size_t largest = index;
		if (l < count && comparer(heap[index], heap[l]))
		{
			largest = l;
		}

		if (r < count && comparer(heap[largest], heap[r]))
		{
			largest = r;
		}

		if (largest != index)
		{
			swap(heap[largest], heap[index]);

			fixDown(largest);
		}
	}

	template <typename TKey, typename TComp>
	void BinaryHeapQueue<TKey, TComp>::fixUp(size_t index)
	{
		TKey parentIndex = parent(index);
		while (index > 0 && comparer(heap[parentIndex], heap[index]))
		{
			std::swap(heap[parentIndex], heap[index]);
			index = parentIndex;
			parentIndex = parent(index);
		}
	}
}
