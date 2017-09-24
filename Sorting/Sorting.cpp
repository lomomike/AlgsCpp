// Sorting.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>

using namespace std;

void shellSort(vector<int>& v)
{
	size_t n = v.size();

	size_t h = 1;
	while (h < n / 3)
		h = 3 * h + 1;

	while (h >= 1)
	{

		for (size_t i = h; i < n; ++i)
		{
			auto temp = v[i];

			size_t j = i;
			for (; j >= h; j -= h)
			{
				if (temp < v[j - h])
					v[j] = v[j - h];
				else break;
			}

			v[j] = temp;
		}

		h = h / 3;
	}

}

template<typename RandomAccessIterator, typename Compare>
void templateShellSort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	using difType = typename std::iterator_traits<RandomAccessIterator>::difference_type;

	difType size = last - first;
	difType h = 1;
	while (h < size / 3)
		h = 3 * h + 1;

	while (h >= 1)
	{
		for (RandomAccessIterator i = first + h; i != last; ++i)
		{
			auto temp = *i;

			auto j = i;
			for (; (j - first) >= h && comp(*j, *(j - h)); j -= h)
			{
				std::swap(*j, *(j - h));
			}

			//*j = temp;
		}

		h = h / 3;
	}
}

template< typename RandomAccessIterator, typename Compare >
void shell_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	for (typename std::iterator_traits< RandomAccessIterator >::difference_type d = (last - first) / 2; d != 0; d /= 2)
		for (RandomAccessIterator i = first + d; i != last; ++i)
			for (RandomAccessIterator j = i; j - first >= d && comp(*j, *(j - d)); j -= d)
				std::swap(*j, *(j - d));
}

bool isSorted(const vector<int>& v)
{
	size_t lastIndex = v.size() - 1;

	for (auto i = 0; i < lastIndex; i++)
	{
		if (v.at(i) > v.at(i + 1))
			return false;
	}

	return true;
}


int main()
{
	vector<int> vector = { 32, 95, 16, 82, 24, 66, 35, 19, 75, 54, 40, 43, 93, 68 };

	cout << "Input array: ";
	for (auto v : vector)
	{
		cout << v << " ";
	}
	cout << endl;
	cout << "Sorted: " << boolalpha << isSorted(vector) << endl;

	//shellSort(vector);
	templateShellSort(vector.begin(), vector.end(), std::less<int>());
	for (auto v : vector)
	{
		cout << v << " ";
	}
	cout << endl;
	cout << "Sorted: " << boolalpha << isSorted(vector) << endl;

	return 0;
}

