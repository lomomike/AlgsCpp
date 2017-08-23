#pragma once
#include <functional>

template <
	typename TKey,
	typename TComp = std::less<TKey>
>
class BinaryHeapQueue
{
public:
	explicit BinaryHeapQueue()
		: count(0),
		capacity(4),
		heap(new TKey[capacity])
	{
	}

	~BinaryHeapQueue()
	{
		delete[]heap;
		count = 0;
		capacity = 0;
	}

private:
	static size_t parent(size_t k)
	{
		return k / 2;
	}

	static size_t left(size_t k)
	{
		return 2 * k + 1;
	}

	static size_t right(size_t k)
	{
		return 2 * (k + 1);
	}

	

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
	std::size_t count;
	std::size_t capacity;
	TKey* heap;
	
};
