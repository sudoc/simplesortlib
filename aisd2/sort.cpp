#include "sort.h"
//#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <stdio.h>
#include <chrono>
#include <fstream>
#include <iterator>


sort::sort()
{
	//srand(time(NULL));
}

sort::~sort()
{
}

std::mt19937 getRandomEngine()
{
	static std::random_device randDev;
	std::mt19937 twister(randDev());
	return twister;
}

int sort::getRand(const int& A, const int& B) 
{
	static std::uniform_int_distribution<int> dist;

	dist.param(std::uniform_int_distribution<int>::param_type(A, B));
	return dist(getRandomEngine());
}

void sort::insertionSort(double* tab, int l, int r)
{
	if (r-l <= 1)
		return;

	double key;
	int j;

	//sprawdzaj od 2 bo 1 jest juz posortowany
	for (int i = l+1; i <= r; ++i)
	{
		key = tab[i];
#ifdef DEBUG
		std::cerr << "Set key = tab[" << i << "]" << std::endl;
#endif
		//porownuj klucz z reszta po kolei
		for (j = i - 1; j >= 0 && tab[j] > key && ++comp; j--)
		{
			tab[j + 1] = tab[j];
			
#ifdef DEBUG
			std::cerr << "Set tab[" << j + 1 << "] = tab[" << j << "]" << std::endl;
#endif
			++swap;
		}
		tab[j + 1] = key;
#ifdef DEBUG
		std::cerr << "Set tab[" << j+1 << "] = key = "<< key << std::endl;
#endif
		++swap;
	}
}

void sort::insertionSortReverse(double* tab, int l, int r)
{
	if (r - l <= 1)
		return;

	double key;
	int j;

	//sprawdzaj od 2 bo 1 jest juz posortowany
	for (int i = l + 1; i <= r; ++i)
	{
		key = tab[i];
#ifdef DEBUG
		std::cerr << "Set key = tab[" << i << "]" << std::endl;
#endif
		//porownuj klucz z reszta po kolei
		for (j = i - 1; j >= 0 && tab[j] < key && ++comp; j--)
		{
			tab[j + 1] = tab[j];
#ifdef DEBUG
			std::cerr << "Set tab[" << j + 1 << "] = tab[" << j << "]" << std::endl;
#endif
			++swap;
		}
		tab[j + 1] = key;
#ifdef DEBUG
		std::cerr << "Set tab[" << j + 1 << "] = key = " << key << std::endl;
#endif
		++swap;
	}
}

void sort::merge(double* tab, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int i, j, k;
	double* tmp1 = new double[n1+1];
	double* tmp2 = new double[n2+1];
	for (i = 0; i < n1; ++i)
		tmp1[i] = tab[p + i];
	for (j = 0; j < n2; ++j)
		tmp2[j] = tab[q + j + 1];

	i = 0;
	j = 0;
	k = p;
	while (i < n1 && j < n2) 
	{
		if (tmp2[j] < tmp1[i] && ++comp) 
		{
#ifdef DEBUG
			std::cerr << "Set tab[" << k << "] = " << tmp2[j] << std::endl;
#endif
			tab[k++] = tmp2[j++]; ++swap;
		}
		else 
		{
#ifdef DEBUG
			std::cerr << "Set tab[" << k << "] = " << tmp1[i] << std::endl;
#endif
			tab[k++] = tmp1[i++]; ++swap;
		}
	}
	while (i < n1) 
	{
#ifdef DEBUG
		std::cerr << "Set tab[" << k << "] = " << tmp1[i] << std::endl;
#endif
		tab[k++] = tmp1[i++]; ++swap;
	}
	while (j < n2) 
	{
#ifdef DEBUG
		std::cerr << "Set tab[" << k << "] = " << tmp2[j] << std::endl;
#endif
		tab[k++] = tmp2[j++]; ++swap;
	}

	delete[] tmp1;
	delete[] tmp2;

}

void sort::mergeSort(double* tab, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) >> 1;
#ifdef DEBUG
		std::cerr << "Divide tab[" << p << ":" << r << "] to tab[" << p << \
			":" << q << "]" << std::endl;
#endif
		mergeSort(tab, p, q);
#ifdef DEBUG
		std::cerr << "Divide tab[" << p << ":" << r << "] to tab[" << q + 1 \
			<< ":" << r << "]" << std::endl;
#endif
		mergeSort(tab, q + 1, r);
#ifdef DEBUG
		std::cerr << "Merge tab[" << p << ":" << q << "] and tab[" << q + 1 \
			<< ":" << r << "] to tab[" << p << ":" << r << "]" << std::endl;
#endif
		merge(tab, p, q, r);
	}
}

void sort::mergeReverse(double* tab, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int i, j, k;
	double* tmp1 = new double[n1 + 1];
	double* tmp2 = new double[n2 + 1];
	for (i = 0; i < n1; ++i)
		tmp1[i] = tab[p + i];
	for (j = 0; j < n2; ++j)
		tmp2[j] = tab[q + j + 1];

	i = 0;
	j = 0;
	k = p;
	while (i < n1 && j < n2)
	{
		if (tmp2[j] > tmp1[i] && ++comp)
		{
#ifdef DEBUG
			std::cerr << "Set tab[" << k << "] = " << tmp2[j] << std::endl;
#endif
			tab[k++] = tmp2[j++]; ++swap;
		}
		else
		{
#ifdef DEBUG
			std::cerr << "Set tab[" << k << "] = " << tmp1[i] << std::endl;
#endif
			tab[k++] = tmp1[i++]; ++swap;
		}
	}
	while (i < n1)
	{
#ifdef DEBUG
		std::cerr << "Set tab[" << k << "] = " << tmp1[i] << std::endl;
#endif
		tab[k++] = tmp1[i++]; ++swap;
	}
	while (j < n2)
	{
#ifdef DEBUG
		std::cerr << "Set tab[" << k << "] = " << tmp2[j] << std::endl;
#endif
		tab[k++] = tmp2[j++]; ++swap;
	}

	delete[] tmp1;
	delete[] tmp2;

}

void sort::mergeSortReverse(double* tab, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) >> 1;
#ifdef DEBUG
		std::cerr << "Divide tab[" << p << ":" << r << "] to tab[" << p << \
			":" << q << "]" << std::endl;
#endif
		mergeSortReverse(tab, p, q);
#ifdef DEBUG
		std::cerr << "Divide tab[" << p << ":" << r << "] to tab[" << q + 1 \
			<< ":" << r << "]" << std::endl;
#endif
		mergeSortReverse(tab, q + 1, r);
#ifdef DEBUG
		std::cerr << "Merge tab[" << p << ":" << q << "] and tab[" << q + 1 \
			<< ":" << r << "] to tab[" << p << ":" << r << "]" << std::endl;
#endif
		mergeReverse(tab, p, q, r);
	}
}

void sort::mergeSortWithInsertionSort(double* tab, int p, int r)
{
	int j = r - p;

	if (j <= 0)
		return;
	else if (j < 11)
	{
#ifdef DEBUG
		std::cerr << "tab really small run insertion sort on tab[" << p << \
			":" << r << "]"<< std::endl;
#endif
		insertionSort(tab, p, r);
	}
	else
	{
		int q = (p + r) >> 1;
#ifdef DEBUG
		std::cerr << "Divide tab[" << p << ":" << r << "] to tab[" << p << \
			":" << q << "]" << std::endl;
#endif
		mergeSort(tab, p, q);
#ifdef DEBUG
		std::cerr << "Divide tab[" << p << ":" << r << "] to tab[" << q + 1 \
			<< ":" << r << "]" << std::endl;
#endif
		mergeSort(tab, q + 1, r);
#ifdef DEBUG
		std::cerr << "Merge tab[" << p << ":" << q << "] and tab[" << q + 1 \
			<< ":" << r << "] to tab[" << p << ":" << r << "]" << std::endl;
#endif
		merge(tab, p, q, r);
	}
}

void sort::swap_(double* tab, int i, int j)
{
	double tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}

int chooseDividePoint(int l, int r)
{
	//element w polowie
	return l + (r - l) / 2;
}

int sort::quickSortDivide(double* tab, int l, int r)
{
	int pivot = chooseDividePoint(l, r);
	double pivotValue = tab[pivot];
#ifdef DEBUG
	std::cerr << "Swap pivot tab[" << pivot << "] with tab[" \
		<< r << "]" << std::endl;
#endif
	//pivot na koniec
	sort::swap_(tab, pivot, r); ++swap;
	//zacznij od poczatku
	int position = l;
	//przejdz po wszystkich elementach
	for (int i = l; i < r ; i++)
	{
		//jezeli pivot jest wiekszy od danego elem.
		if (tab[i] < pivotValue && ++comp)
		{
#ifdef DEBUG
			std::cerr << "Swap tab[" << i << "] with tab[" \
				<< position << "]" << std::endl;
#endif
			//przenies elem. na lewa strone
			sort::swap_(tab, i, position); ++swap;
			//przesun pozycje
			++position;
		}
	}
#ifdef DEBUG
	std::cerr << "Swap pivot tab[" << position << "] with tab[" \
		<< r << "]" << std::endl;
#endif
	//przywroc pivot na swoje miejsce
	sort::swap_(tab, position, r); ++swap;
	return position;
}

void sort::quickSort(double* tab, int l, int r)
{
	//jezeli jest jakis element
	if (l < r)
	{
		//podziel problem na pol i zapamietaj punkt
		int i = quickSortDivide(tab, l, r);
#ifdef DEBUG
		std::cerr << "Divide tab[" << l << ":" << r << "] to tab[" << l << \
			":" << i - 1 << "]" << std::endl;
#endif
		//sortuj lewa czesc
		quickSort(tab, l, i - 1);
#ifdef DEBUG
		std::cerr << "Divide tab[" << l << ":" << r << "] to tab[" \
			<< i + 1 << ":" << r << "]" << std::endl;
#endif
		//sortuj prawa czesc
		quickSort(tab, i + 1, r);
	}
}

int sort::quickSortDivideReverse(double* tab, int l, int r)
{
	int pivot = chooseDividePoint(l, r);
	double pivotValue = tab[pivot];
#ifdef DEBUG
	std::cerr << "Swap pivot tab[" << pivot << "] with tab[" \
		<< r << "]" << std::endl;
#endif
	//pivot na koniec
	sort::swap_(tab, pivot, r); ++swap;
	//zacznij od poczatku
	int position = l;
	//przejdz po wszystkich elementach
	for (int i = l; i < r; i++)
	{
		//jezeli pivot jest mniejszy od danego elem.
		if (tab[i] > pivotValue && ++comp)
		{
#ifdef DEBUG
			std::cerr << "Swap tab[" << i << "] with tab[" \
				<< position << "]" << std::endl;
#endif
			//przenies elem. na lewa strone
			sort::swap_(tab, i, position); ++swap;
			//przesun pozycje
			++position;
		}
	}
#ifdef DEBUG
	std::cerr << "Swap pivot tab[" << position << "] with tab[" \
		<< r << "]" << std::endl;
#endif
	//przywroc pivot na swoje miejsce
	sort::swap_(tab, position, r); ++swap;
	return position;
}

void sort::quickSortReverse(double* tab, int l, int r)
{
	//jezeli jest jakis element
	if (l < r)
	{
		//podziel problem na pol i zapamietaj punkt
		int i = quickSortDivideReverse(tab, l, r);
#ifdef DEBUG
		std::cerr << "Divide tab[" << l << ":" << r << "] to tab[" << l << \
			":" << i - 1 << "]" << std::endl;
#endif
		//sortuj lewa czesc
		quickSortReverse(tab, l, i - 1);
#ifdef DEBUG
		std::cerr << "Divide tab[" << l << ":" << r << "] to tab[" \
			<< i + 1 << ":" << r << "]" << std::endl;
#endif
		//sortuj prawa czesc
		quickSortReverse(tab, i + 1, r);
	}
}

void sort::quickSortWithInsertionSort(double* tab, int l, int r)
{
	int j = r - l;
	//jezeli jest jakis element
	if (j <= 0)
		return;
	else if (j < 12)
	{
#ifdef DEBUG
		std::cerr << "tab really small run insertion sort on tab[" << l << \
			":" << r << "]" << std::endl;
#endif
		insertionSort(tab, l, r);
	}
	else
	{
		//podziel problem na pol i zapamietaj punkt
		int i = quickSortDivide(tab, l, r);
#ifdef DEBUG
		std::cerr << "Divide tab[" << l << ":" << r << "] to tab[" << l << \
			":" << i - 1 << "]" << std::endl;
#endif
		//sortuj lewa czesc
		quickSortWithInsertionSort(tab, l, i - 1);
#ifdef DEBUG
		std::cerr << "Divide tab[" << l << ":" << r << "] to tab[" \
			<< i + 1 << ":" << r << "]" << std::endl;
#endif
		//sortuj prawa czesc
		quickSortWithInsertionSort(tab, i + 1, r);
	}
}

int sort::chooseDividePointMedian(double *tab, int l, int r)
{
	if (r == l)
		return l;

	//element w polowie
	int k = l + (r - l) / 2;

	//mediana elementu srodkowego, ostatniego i pierwszego
	if (tab[l] <= tab[r])
	{
		if (tab[k] <= tab[l] && comp++)
			return l;
		else if (tab[k] <= tab[r] && comp++)
			return k;
		else
			return r;
	}
	else
	{
		if (tab[k] <= tab[r] && comp++)
			return r;
		else if (tab[k] <= tab[l] && comp++)
			return k;
		else
			return l;
	}
}

int sort::quickSortDivideMedian(double* tab, int l, int r)
{
	int pivot = chooseDividePointMedian(tab, l, r);
	double pivotValue = tab[pivot];
#ifdef DEBUG
	std::cerr << "Swap pivot tab[" << pivot << "] with tab[" \
		<< r << "]" << std::endl;
#endif
	//pivot na koniec
	sort::swap_(tab, pivot, r); ++swap;
	//zacznij od poczatku
	int position = l;
	//przejdz po wszystkich elementach
	for (int i = l; i < r; i++)
	{
		//jezeli pivot jest wiekszy od danego elem.
		if (tab[i] < pivotValue && ++comp)
		{
#ifdef DEBUG
			std::cerr << "Swap tab[" << i << "] with tab[" \
				<< position << "]" << std::endl;
#endif
			//przenies elem. na lewa strone
			sort::swap_(tab, i, position); ++swap;
			//przesun pozycje
			++position;
		}
	}
#ifdef DEBUG
	std::cerr << "Swap pivot tab[" << position << "] with tab[" \
		<< r << "]" << std::endl;
#endif
	//przywroc pivot na swoje miejsce
	sort::swap_(tab, position, r); ++swap;
	return position;
}

void sort::quickSortWithInsertionSortAndMedian(double* tab, int l, int r)
{
	int j = r - l;
	//jezeli jest jakis element
	if (j <= 0)
		return;
	else if (j < 16)
	{
#ifdef DEBUG
		std::cerr << "tab really small run insertion sort on tab[" << l << \
			":" << r << "]" << std::endl;
#endif
		insertionSort(tab, l, r);
	}
	else
	{
		//podziel problem na pol i zapamietaj punkt
		int i = quickSortDivideMedian(tab, l, r);
#ifdef DEBUG
		std::cerr << "Divide tab[" << l << ":" << r << "] to tab[" << l << \
			":" << i - 1 << "]" << std::endl;
#endif
		//sortuj lewa czesc
		quickSortWithInsertionSortAndMedian(tab, l, i - 1);
#ifdef DEBUG
		std::cerr << "Divide tab[" << l << ":" << r << "] to tab[" \
			<< i + 1 << ":" << r << "]" << std::endl;
#endif
		//sortuj prawa czesc
		quickSortWithInsertionSortAndMedian(tab, i + 1, r);
	}
}

int sort::dualPivotQuickSortDivide(double* tab, int l, int r, int* lpivot)
{
	//jezeli pivot lewy jest wiekszy od prawego to je zamien
	if (tab[l] > tab[r] && ++comp)
	{
#ifdef DEBUG
		std::cerr << "Swap pivots tab[" << l << "] with tab[" \
			<< r << "]" << std::endl;
#endif
		sort::swap_(tab, l, r); ++swap;
	}
	int j = l + 1; //od drugiego poniewaz pierwszy jest lpivot
	int g = r - 1; //bez ostatniego poniewaz ostatni to rpivot
	int k = l + 1; //podobnie
	double lpivotValue = tab[l];
	double rpivotValue = tab[r];
	while (k <= g) 
	{
		//jezeli el jest mniejszy od lewego pivota
		if (tab[k] < lpivotValue && ++comp) 
		{
#ifdef DEBUG
			std::cerr << "Swap tab[" << k << "] with tab[" \
				<< j << "]" << std::endl;
#endif
			//to zamien i przesun wskaznik w prawo 
			sort::swap_(tab, k, j); ++swap;
			j++;
		}
		//jezeli el jest wiekszy rowny prawemu pivotowi
		else if (tab[k] >= rpivotValue && ++comp) 
		{
			while (tab[g] > rpivotValue && k < g && ++comp)
				g--;
#ifdef DEBUG
			std::cerr << "Swap pivot tab[" << k << "] with tab[" \
				<< g << "]" << std::endl;
#endif
			sort::swap_(tab, k, g); ++swap;
			g--;
			if (tab[k] < lpivotValue && ++comp) 
			{
#ifdef DEBUG
				std::cerr << "Swap pivot tab[" << k << "] with tab[" \
					<< j << "]" << std::endl;
#endif
				sort::swap_(tab, k, j); ++swap;
				j++;
			}
		}
		k++;
	}
	j--;
	g++;
#ifdef DEBUG
	std::cerr << "Swap lpivot tab[" << l << "] with tab[" \
		<< j << "]" << std::endl;
	std::cerr << "Swap rpivot tab[" << r << "] with tab[" \
		<< g << "]" << std::endl;
#endif
	//ustaw pivoty na swoje miesjca
	sort::swap_(tab, l, j); ++swap;
	sort::swap_(tab, r, g); ++swap;

	//zwroc lewy i prawy pivot
	*lpivot = j;
	return g;
}

void sort::dualPivotQuickSort(double* tab, int l, int r)
{
	if (l < r) 
	{
		int lpivot, rpivot;
		rpivot = dualPivotQuickSortDivide(tab, l, r, &lpivot);
#ifdef DEBUG
		std::cerr << "Divide tab[" << l << ":" << r << "] to tab[" \
			<< l << ":" << lpivot - 1 << "]" << std::endl;
#endif
		dualPivotQuickSort(tab, l, lpivot - 1);
#ifdef DEBUG
		std::cerr << "Divide tab[" << l << ":" << r << "] to tab[" \
			<< lpivot + 1 << ":" << rpivot - 1 << "]" << std::endl;
#endif
		dualPivotQuickSort(tab, lpivot + 1, rpivot - 1);
#ifdef DEBUG
		std::cerr << "Divide tab[" << l << ":" << r << "] to tab[" \
			<< rpivot + 1 << ":" << r << "]" << std::endl;
#endif
		dualPivotQuickSort(tab, rpivot + 1, r);
	}
}

void sort::selectionSort(double* tab, int l, int r)
{
	int n = r - l;
	if (n <= 0)
		return;

	// key is an index of minimal value 
	int key;

	for (int i = l; i < n; i++)
	{
		// Find the minimum element in unsorted array 
#ifdef DEBUG
		std::cerr << "Set key = tab[" << i << "]" << std::endl;
#endif
		key = i;

		for (int j = i + 1; j <= n; j++)
			if (tab[j] < tab[key] && comp++)
			{
#ifdef DEBUG
				std::cerr << "Set key = tab[" << j << "]" << std::endl;
#endif
				key = j;
			}

		// swap minimum element with the first unsorted one
#ifdef DEBUG
		std::cerr << "Swap tab[" << i << "] with tab[" \
			<< key << "]" << std::endl;
#endif
		sort::swap_(tab, key, i); swap++;

	}
}

void sort::selectionSortReverse(double* tab, int l, int r)
{
	int n = r - l;
	if (n <= 0)
		return;

	// key is an index of maximal value 
	int key;

	for (int i = l; i < n; i++)//n; i >= l + 1; i--)
	{
		// find the maximum element in unsorted array 
#ifdef DEBUG
		std::cerr << "Set key = tab[" << i << "]" << std::endl;
#endif
		key = i;

		for (int j = i + 1; j <= n; j++)
			if (tab[j] > tab[key] && comp++)
			{
#ifdef DEBUG
				std::cerr << "Set key = tab[" << j << "]" << std::endl;
#endif
				key = j;
			}

		// swap maximum element with the first unsorted one
#ifdef DEBUG
			std::cerr << "Swap tab[" << i - 1 << "] with tab[" \
				<< key << "]" << std::endl;
#endif
			sort::swap_(tab, i, key); swap++;
	}
}

void sort::heapify(double* tab, int heap_size, int i)
{
	// largest is index of current root element 
#ifdef DEBUG
	std::cerr << "Set key = tab[" << i << "]" << std::endl;
#endif
	int largest = i;
	int l = 2 * i +	1;
	int r = 2 * i + 2;

	// if left child is larger then root element
	if (l < heap_size && tab[l] > tab[largest] && comp++)
	{
#ifdef DEBUG
		std::cerr << "Set key = tab[" << l << "]" << std::endl;
#endif
		largest = l;
	}

	// if right child is larger then root element
	if (r < heap_size && tab[r] > tab[largest] && comp++)
	{
#ifdef DEBUG
		std::cerr << "Set key = tab[" << r << "]" << std::endl;
#endif
		largest = r;
	}

	// if largest is not a root element
	if (largest != i)
	{
#ifdef DEBUG
		std::cerr << "Swap tab[" << i << "] with tab[" \
			<< largest << "]" << std::endl;
#endif
		sort::swap_(tab, i, largest); swap++;

		// correct heap (sub-tree)
		sort::heapify(tab, heap_size, largest);
	}
}

void sort::heapSort(double* tab, int l, int r)
{
	int n = r + 1 - l;

	// build heap
	for (int i = n / 2 - 1; i >= l; i--)
		sort::heapify(tab, n, i);

	// take each element from heap
	for (int i = n - 1; i >= l; i--)
	{
		// move current root element to the end
#ifdef DEBUG
		std::cerr << "Swap tab[" << i << "] with tab[" \
			<< 0 << "]" << std::endl;
#endif
		sort::swap_(tab, 0, i); swap++;

		// heapify tab with reduced tab size
		sort::heapify(tab, i, 0);
	}
}

void sort::heapifyReverse(double* tab, int heap_size, int i)
{
	// smallest is index of current root element 
#ifdef DEBUG
	std::cerr << "Set key = tab[" << i << "]" << std::endl;
#endif
	int smallest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	// if left child is smaller then root element
	if (l < heap_size && tab[l] < tab[smallest] && comp++)
	{
#ifdef DEBUG
		std::cerr << "Set key = tab[" << l << "]" << std::endl;
#endif
		smallest = l;
	}

	// if right child is smaller then root element
	if (r < heap_size && tab[r] < tab[smallest] && comp++)
	{
#ifdef DEBUG
		std::cerr << "Set key = tab[" << r << "]" << std::endl;
#endif
		smallest = r;
	}

	// if smallest is not a root element
	if (smallest != i)
	{
#ifdef DEBUG
		std::cerr << "Swap tab[" << i << "] with tab[" \
			<< smallest << "]" << std::endl;
#endif
		sort::swap_(tab, i, smallest); swap++;

		// correct heap (sub-tree)
		sort::heapifyReverse(tab, heap_size, smallest);
	}
}

void sort::heapSortReverse(double* tab, int l, int r)
{
	int n = r + 1 - l;

	// build heap
	for (int i = n / 2 - 1; i >= l; i--)
		sort::heapifyReverse(tab, n, i);

	// take each element from heap
	for (int i = n - 1; i >= l; i--)
	{
		// move current root element to the end
#ifdef DEBUG
		std::cerr << "Swap tab[" << i << "] with tab[" \
			<< 0 << "]" << std::endl;
#endif
		sort::swap_(tab, 0, i); swap++;

		// heapify tab with reduced tab size
		sort::heapifyReverse(tab, i, 0);
	}
}

int sort::chooseRandomDividePoint(int l, int r)
{
	//element losowy z przedzialu
	//return (int)floor(rand() % (r - l + 1)) + l;
	return sort::getRand(l, r);
}

int sort::randomizedSelectDivide(double* tab, int l, int r)
{
	int pivot = chooseRandomDividePoint(l, r);
	double pivotValue = tab[pivot];
#ifdef DEBUG
	std::cerr << "Swap random pivot tab[" << pivot << "] with tab[" \
		<< r << "]" << std::endl;
#endif
	//pivot na koniec
	sort::swap_(tab, pivot, r); ++swap;
	//zacznij od poczatku
	int position = l;
	//przejdz po wszystkich elementach
	for (int i = l; i < r; i++)
	{
		//jezeli pivot jest wiekszy od danego elem.
		if (tab[i] < pivotValue && ++comp)
		{
#ifdef DEBUG
			std::cerr << "Swap tab[" << i << "] with tab[" \
				<< position << "]" << std::endl;
#endif
			//przenies elem. na lewa strone
			sort::swap_(tab, i, position); ++swap;
			//przesun pozycje
			++position;
		}
	}
#ifdef DEBUG
	std::cerr << "Swap pivot tab[" << position << "] with tab[" \
		<< r << "]" << std::endl;
#endif
	//przywroc pivot na swoje miejsce
	sort::swap_(tab, position, r); ++swap;
	return position;
}

int sort::randomizedSelect(double* tab, int l, int r, int k)
{
	//jezeli w zakresie jest tylko jeden element
	if (l >= r)
		return l;
	//idiotoodpornosc (k poza zakresem)
	if (r - k < l)
		return NULL;

	if (l < r)
	{
		//podziel problem na czesci losowo
		int mid = randomizedSelectDivide(tab, l, r);
		//poprawka na zakres
		int i = mid - l + 1;
#ifdef DEBUG
		std::cerr << "New candidate: " << i << " ";
#endif
		//jezeli element zostal znaleziony
		if (i == k)
		{
#ifdef DEBUG
			std::cerr << "is okey return" << std::endl;
#endif
			return mid;
		}
			//jezeli element jest w lewej czesci
		else if (k < i)
		{
#ifdef DEBUG
			std::cerr << "is in left" << std::endl << "Divide tab[" \
				<< l << ":" << r << "] to tab[" << l << ":" << \
				mid - 1 << "]" << std::endl;
#endif
			return randomizedSelect(tab, l, mid - 1, k);
		}
		else //jezeli w prawej
		{
#ifdef DEBUG
			std::cerr << "is in right" << std::endl << "Divide tab[" \
				<< l << ":" << r << "] to tab[" << mid + 1 << ":" << \
				r << "]" << std::endl;
#endif
			return randomizedSelect(tab, mid + 1, r, k - i);
		}
	}
	return NULL;
}

int sort::medianOfFive(double* tab, int l, int r)
{
	if (l == r)
		return l;
	sort::insertionSort(tab, l, r - 1);
	return (r - l) / 2 + l;
}

int sort::chooseMedianDividePoint(double* tab, int l, int r)
{
	//mediana median
	//jezeli jest mniej niz 5 elementow 
	//wykonaj insertion sort i zwroc mediane
	if (r - l < 5)
	{
#ifdef DEBUG
		std::cerr << "choosing median divde point: elements ammount < 5 "\
			<< "insertion sort them and return median" << std::endl;
#endif
		return medianOfFive(tab, l, r);
	}

	int last;
#ifdef DEBUG
	std::cerr << "choosing median divde point: elements ammount > 5 "\
		<< "count medians of 5-el sub-groups" << std::endl;
#endif
	//policz mediany wszystkich piecioelementowych podgrup
	//i przenies je na poczatek przedzialu
	for (int i = l; i < r; i = i + 4)
	{
		//zapamietaj pozycje ostatniej podgrupy
		last = i + 4;
		//jezeli wykracza poza zakres
		if (last > r)
			last = r; //cofnij
		//policz mediane podgrupy
		int median5 = medianOfFive(tab, i, last);
#ifdef DEBUG
		std::cerr << "Swap tab[" << median5 << "] with tab[" \
			<< l + (int)floor((i - l) / 5) << "]" << std::endl;
#endif
		//przenies ja na poczatek przedzialu
		sort::swap_(tab, median5, l + (int)floor((i - l) / 5)); ++swap;
	}
	//policz mediane wszystkich median z podgrup 
	return select(tab, l, l + (int)ceil((r - l) / 5) - 1, l + (r - l) / 10);
}

int sort::selectDivide(double* tab, int l, int r, int pivot)
{
	//int pivot = chooseMedianDividePoint(l, r);
	double pivotValue = tab[pivot];
#ifdef DEBUG
	std::cerr << "Swap pivot tab[" << pivot << "] with tab[" \
		<< r << "]" << std::endl;
#endif
	//pivot na koniec
	sort::swap_(tab, pivot, r); ++swap;
	//zacznij od poczatku
	int position = l;
	//przejdz po wszystkich elementach
	for (int i = l; i < r; i++)
	{
		//jezeli pivot jest wiekszy od danego elem.
		if (tab[i] < pivotValue && ++comp)
		{
#ifdef DEBUG
			std::cerr << "Swap tab[" << i << "] with tab[" \
				<< position << "]" << std::endl;
#endif
			//przenies elem. na lewa strone
			sort::swap_(tab, i, position); ++swap;
			//przesun pozycje
			++position;
		}
	}
#ifdef DEBUG
	std::cerr << "Swap pivot tab[" << position << "] with tab[" \
		<< r << "]" << std::endl;
#endif
	//przywroc pivot na swoje miejsce
	sort::swap_(tab, position, r); ++swap;
	return position;
}

int sort::select(double* tab, int l, int r, int k)
{
	if (l == r)
		return l;
	//wybieramy pivota za pomoca mediany median
	int pivot = chooseMedianDividePoint(tab, l, r);
#ifdef DEBUG
	std::cerr << "New median of medians pivot: " << pivot << std::endl;
#endif
	//dzielimy tablice wzgledem znalezionego pivota
	pivot = selectDivide(tab, l, r, pivot);

#ifdef DEBUG
	std::cerr << "New candidate: " << pivot << " ";
#endif
	//pivot jest rozwiazaniem
	if (k == pivot)
	{
#ifdef DEBUG
		std::cerr << "is okey return" << std::endl;
#endif
		return k;
	}
	//pivot jest wiekszy od poszukiwanej statystki poz.
	else if (k < pivot)
	{
#ifdef DEBUG
		std::cerr << "is in left" << std::endl << "Divide tab[" \
			<< l << ":" << r << "] to tab[" << l << ":" << \
			pivot - 1 << "]" << std::endl;
#endif
		return select(tab, l, pivot - 1, k);
	}
	//pivot jest mniejszy ..
	else
	{
#ifdef DEBUG
		std::cerr << "is in right" << std::endl << "Divide tab[" \
			<< l << ":" << r << "] to tab[" << pivot + 1 << ":" << \
			r << "]" << std::endl;
#endif
		return select(tab, pivot + 1, r, k);
	}
}

int sort::binarySearch(double* tab, int l, int r, double v)
{
	if (l > r)
		return NULL;

	int mid = (l + r) / 2;

	if (v == tab[mid])
		return mid;
	if (v < tab[mid])
		return binarySearch(tab, l, mid - 1, v);
	else
		return binarySearch(tab, mid + 1, r, v);
}

/*
	Stworz tablice parametry:
	m - tryby:
		1 - ciagi losowe
		2 - ciagi posortowane
		3 - ciagi posortowane malejaco
		4 - permutacja ciagu od 1 do n
		dowolna wartosc - ciagi zer
	n - wielkosc tablicy
	zwracana wartosc:
	tab - tablica danych
*/
double* sort::createTab(int m, int n)
{
	if (n <= 0)
		return NULL;

	double* tab = new double[n];
	
	//ciagi losowe
	if (m == 1)
	{
		for (int i = 0; i < n; ++i)
		{
			tab[i] = sort::getRand(0, 10000);
		}
	}
	//ciagi posortowane
	else if (m == 2)
	{
		for (int i = 0; i < n; ++i)
		{
			tab[i] = getRand(0,10000);
		}
		quickSort(tab, 0, n);
	}
	//ciagi posortowane malejaco
	else if (m == 3)
	{
		for (int i = 0; i < n; ++i)
		{
			tab[i] = getRand(0,10000);
		}
		quickSort(tab, 0, n);
		int j = n;
		for (int i = 0; i < n >> 1; ++i)
		{
			swap_(tab, i, j);
			--j;
		}
	}
	//permutacja ciagu od 1 do n
	if (m == 4)
	{
		for (int i = 0; i < n; ++i)
		{
			tab[i] = i + 1;
		}
		std::shuffle(&tab[0], &tab[n-1], getRandomEngine());

	}
	//tryb niezdefiniowany ciagi zer
	else
	{
		for (int i = 0; i < n; ++i)
		{
			tab[i] = 0;
		}
	}

	return tab;
}

/* m - algo
 * n - ilosc elementow
 * c - comp
 * s - swap
 * filename - file name
*/
int sort::writeToFile(int m, int n, int c, int s, char* filename)
{ 
	char* out = (char*)malloc(sizeof(char*) * 10);
	
	sprintf_s(out, 10 * sizeof(out), "%s%s%02d%s", filename, "_X", m, ".txt");
	std::ofstream f1;
	f1.open(out, std::ios_base::app);
	f1 << n << std::endl;
	f1.close();

	sprintf_s(out, 10 * sizeof(out), "%s%s%02d%s", filename, "_compY", m, ".txt");
	std::ofstream f2;
	f2.open(out, std::ios_base::app);
	f2 << c << std::endl;
	f2.close();

	sprintf_s(out, 10 * sizeof(out), "%s%s%02d%s", filename, "_swapY", m, ".txt");
	std::ofstream f3;
	f3.open(out, std::ios_base::app);
	f3 << s << std::endl;
	f3.close();

	free(out);
	return 0;
}

/* m - algo
* n - ilosc elementow
* c - comp
* s - swap
* t - time
* filename - file name
*/
int sort::writeToFile(int m, int n, int c, int s, int time, char* filename)
{
	char* out = (char*)malloc(sizeof(char*) * 10);

	sprintf_s(out, 10 * sizeof(out), "%s%s%02d%s", filename, "_X", m, ".txt");
	std::ofstream f4;
	f4.open(out, std::ios_base::app);
	f4 << n << std::endl;
	f4.close();

	sprintf_s(out, 10 * sizeof(out), "%s%s%02d%s", filename, "_compY", m, ".txt");
	std::ofstream f5;
	f5.open(out, std::ios_base::app);
	f5 << c << std::endl;
	f5.close();

	sprintf_s(out, 10 * sizeof(out), "%s%s%02d%s", filename, "_swapY", m, ".txt");
	std::ofstream f6;
	f6.open(out, std::ios_base::app);
	f6 << s << std::endl;
	f6.close();

	sprintf_s(out, 10 * sizeof(out), "%s%s%02d%s", filename, "_timeY", m, ".txt");
	std::ofstream f7;
	f7.open(out, std::ios_base::app);
	f7 << time << std::endl;
	f7.close();

	free(out);
	return 0;
}

int sort::clearFile(int m)
{
	char* out = (char*)malloc(sizeof(char*) * 10);
	
	sprintf_s(out, 10 * sizeof(out), "%s%02d%s", "comp", m, ".txt");
	std::ofstream f8;
	f8.open(out);
	f8 << "" << std::endl;
	f8.close();

	sprintf_s(out, 10 * sizeof(out), "%s%02d%s", "swap", m, ".txt");
	std::ofstream f9;
	f9.open(out);
	f9 << "" << std::endl;
	f9.close();

	free(out);
	return 0;
}

void sort::plotGnuplot(int m)
{
	if (m == 1)
	{
		system("gnuplot -p -e \"plot 'comp01.txt' with lines, \
			'comp02.txt' with lines, 'comp03.txt' with lines\"");
	}
	else if (m == 2)
	{
		system("gnuplot -p -e \"plot 'comp01.txt' with lines, \
			'comp02.txt' with lines, 'comp03.txt' with lines, \
			'comp04.txt' with lines, 'comp05.txt' with lines\"");
	}
	else if (m == 3)
	{
		system("gnuplot -p -e \"plot 'comp08.txt' with lines, \
			'comp09.txt' with lines\"");
	}
	else
	{
		return;
	}
}

void sort::printTab(double* tab, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("tab[%d] = %f\n", i, tab[i]);
	}
}

int sort::testSort(int m)
{
	if (m == 1)
	{
		comp = 0; swap = 0;
		for (int i = 1; i <= 3; ++i)
			sort::clearFile(i);
		char* empty = "";
		// dla wszystkich n
		for (int i = 100; i <= 100000; i += 100)
		{
			// wielokrotnie dla wszystkich n
			for (int j = 0; j < 3; ++j)
			{

				double* tab1 = createTab(1, i);
				//printTab(tab1, i);
				double* tab2 = new double[i];
				//std::copy(tab1, tab1 + i, tab2);
				memcpy(tab2, tab1, i * sizeof(double));
				double* tab3 = new double[i];
				//std::copy(tab1, tab1 + i, tab3);
				memcpy(tab3, tab1, i * sizeof(double));

				comp = 0; swap = 0;
				insertionSort(tab1, 0, i - 1);
				//printTab(tab2, i);
				sort::writeToFile(1, i, comp, swap, empty);
				delete[] tab1;

				comp = 0; swap = 0;
				mergeSort(tab2, 0, i-1);
				//printTab(tab3, i);
				sort::writeToFile(2, i, comp, swap, empty);
				delete[] tab2;

				comp = 0; swap = 0;
				quickSort(tab3, 0, i-1);
				//printTab(tab3, i);
				sort::writeToFile(3, i, comp, swap, empty);
				delete[] tab3;
			}
		}
		//free(empty);
	}
	sort::plotGnuplot(1);
	return 0;
}

int sort::checkSortingAlgorithm(double *tab, int l, int p, int order)
{
	for (int i = 0; i < p - l; i++)
	{
		if (tab[i] > tab[i + 1] && order == 1)
			return 1;
		else if (tab[i] < tab[i + 1] && order == 2)
			return 1;
	}
	return 0;
}

int sort::testSortWithoutStats(int algo, int order)
{
	// get size of tab
	int n = 0;
	std::cin >> n;
	// create tab of desired size
	double* tab = new double[n+1];
	// populate tab with values from user
	for (int i = 0; i < n; i++)
	{
		std::cin >> tab[i];
	}
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	comp = 0; swap = 0;
	if (algo == 1)
	{
		if (order == 1)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::insertionSort(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
		else if (order == 2)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::insertionSortReverse(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
	}
	else if (algo == 2)
	{
		if (order == 1)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::mergeSort(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
		else if (order == 2)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::mergeSortReverse(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
	}
	else if (algo == 3)
	{
		if (order == 1)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::quickSort(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
		else if (order == 2)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::quickSortReverse(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
	}
	else if (algo == 4)
	{
		if (order == 1)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::selectionSort(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
		else if (order == 2)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::selectionSortReverse(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
	}
	else if (algo == 5)
	{
		if (order == 1)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::heapSort(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
		else if (order == 2)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::heapSortReverse(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
	}
	else if (algo == 6)
	{
		if (order == 1)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::quickSortWithInsertionSortAndMedian(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
		else if (order == 2)
		{
			start = std::chrono::high_resolution_clock::now();
			sort::heapSortReverse(tab, 0, n - 1);
			end = std::chrono::high_resolution_clock::now();
		}
	}
	if (sort::checkSortingAlgorithm(tab, 0, n-1, order) == 1)
	{
		std::cerr << "Errors occured, check input and output tab" << std::endl;
	}
	// print algo time on stderr
#ifdef DEBUG
	std::cerr << "DEBUG FLAG ENABLED TIME ONLY IN APROXIMATION" << std::endl;
#endif
	std::cerr << "Time: ";
	std::cerr << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cerr << "us" << std::endl;
	// print comp and swap on stderr
	std::cerr << "Comp: " << comp << " Swap: " \
		<< swap << std::endl;
	// print on stdout n
	std::cout << n << std::endl;
	// print on stdout tab values
	for (int i = 0; i < n; i++)
	{
		std::cout << tab[i] << " ";
	}
	std::cout << std::endl;

	delete[] tab;
	return 0;
}

int sort::testSortWithStats(char* filename, int k)
{
	comp = 0; swap = 0;
	//for (int i = 1; i <= 3; ++i)
		//sort::clearFile(i);

	for (int i = 100; i <= 10000; i += 100)
	{
		for (int j = 0; j < k; j++)
		{
			double* tab1 = new double[i];
			for (int x = 0; x < i; ++x)
			{
				tab1[x] = sort::getRand(0, 10000);
			}
			//double* tab1 = sort::createTab(1, i);
			//printTab(tab1, i);
			double* tab2 = new double[i];
			//std::copy(tab1, tab1 + i, tab2);
			memcpy(tab2, tab1, i * sizeof(double));
			double* tab3 = new double[i];
			//std::copy(tab1, tab1 + i, tab3);
			memcpy(tab3, tab1, i * sizeof(double));
			double* tab4 = new double[i];
			//std::copy(tab1, tab1 + i, tab4);
			memcpy(tab4, tab1, i * sizeof(double));
			double* tab5 = new double[i];
			//std::copy(tab1, tab1 + i, tab3);
			memcpy(tab5, tab1, i * sizeof(double));
			double* tab6 = new double[i];
			//std::copy(tab1, tab1 + i, tab4);
			memcpy(tab6, tab1, i * sizeof(double));
			double* tab7 = new double[i];
			//std::copy(tab1, tab1 + i, tab4);
			memcpy(tab7, tab1, i * sizeof(double));

			comp = 0; swap = 0;
			auto start = std::chrono::high_resolution_clock::now();
			sort::insertionSort(tab1, 0, i - 1);
			auto end = std::chrono::high_resolution_clock::now();
			//printTab(tab1, i);
			sort::writeToFile(1, i, comp, swap, (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), filename);
			delete[] tab1;

			comp = 0; swap = 0;
			start = std::chrono::high_resolution_clock::now();
			mergeSort(tab2, 0, i - 1);
			end = std::chrono::high_resolution_clock::now();
			//printTab(tab2, i);
			sort::writeToFile(2, i, comp, swap, (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), filename);
			delete[] tab2;

			comp = 0; swap = 0;
			start = std::chrono::high_resolution_clock::now();
			quickSort(tab3, 0, i - 1);
			end = std::chrono::high_resolution_clock::now();
			//printTab(tab3, i);
			sort::writeToFile(3, i, comp, swap, (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), filename);
			delete[] tab3;

			comp = 0; swap = 0;
			start = std::chrono::high_resolution_clock::now();
			dualPivotQuickSort(tab4, 0, i - 1);
			end = std::chrono::high_resolution_clock::now();
			//printTab(tab4, i);
			sort::writeToFile(4, i, comp, swap, (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), filename);
			delete[] tab4;

			comp = 0; swap = 0;
			start = std::chrono::high_resolution_clock::now();
			selectionSort(tab5, 0, i - 1);
			end = std::chrono::high_resolution_clock::now();
			//printTab(tab3, i);
			sort::writeToFile(11, i, comp, swap, (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), filename);
			delete[] tab5;

			comp = 0; swap = 0;
			start = std::chrono::high_resolution_clock::now();
			heapSort(tab6, 0, i - 1);
			end = std::chrono::high_resolution_clock::now();
			//printTab(tab4, i);
			sort::writeToFile(12, i, comp, swap, (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), filename);
			delete[] tab6;

			comp = 0; swap = 0;
			start = std::chrono::high_resolution_clock::now();
			quickSortWithInsertionSortAndMedian(tab7, 0, i - 1);
			end = std::chrono::high_resolution_clock::now();
			//printTab(tab4, i);
			sort::writeToFile(13, i, comp, swap, (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), filename);
			delete[] tab7;
		}
	}
	return 0;
}

int sort::testMergedSort(int m)
{
	if (m == 1)
	{
		comp = 0; swap = 0;
		//for(int i=1;i<=5;++i)
		//	sort::clearFile(i);
		char* empty = "";
		// dla wszystkich n
		for (int i = 2; i <= 100; i += 1)
		{
			// wielokrotnie dla wszystkich n
			for (int j = 0; j < 100; ++j)
			{
				double* tab1 = createTab(1, i);
				//printTab(tab1, i);
				double* tab2 = new double[i];
				//std::copy(tab1, tab1 + i, tab2);
				memcpy(tab2, tab1, i * sizeof(double));
				double* tab3 = new double[i];
				//std::copy(tab1, tab1 + i, tab3);
				memcpy(tab3, tab1, i * sizeof(double));
				double* tab4 = new double[i];
				//std::copy(tab1, tab1 + i, tab4);
				memcpy(tab4, tab1, i * sizeof(double));
				double* tab5 = new double[i];
				//std::copy(tab1, tab1 + i, tab5);
				memcpy(tab5, tab1, i * sizeof(double));

				comp = 0; swap = 0;
				comp++;
				++comp;

				insertionSort(tab1, 0, i - 1);
				//printTab(tab1, i);
				sort::writeToFile(1, i, comp, swap, empty);
				delete[] tab1;

				comp = 0; swap = 0;
				mergeSort(tab2, 0, i - 1);
				//printTab(tab2, i);
				sort::writeToFile(2, i, comp, swap, empty);
				delete[] tab2;

				comp = 0; swap = 0;
				quickSort(tab3, 0, i - 1);
				//printTab(tab3, i);
				sort::writeToFile(3, i, comp, swap, empty);
				delete[] tab3;

				comp = 0; swap = 0;
				quickSortWithInsertionSort(tab4, 0, i - 1);
				//printTab(tab4, i);
				sort::writeToFile(5, i, comp, swap, empty);
				delete[] tab4;

				comp = 0; swap = 0;
				mergeSortWithInsertionSort(tab5, 0, i - 1);
				//printTab(tab5, i);
				sort::writeToFile(6, i, comp, swap, empty);
				delete[] tab5;
			}
		}
		free(empty);
	}
	//sort::plotGnuplot(2);
	return 0;
}

int sort::testSearch(int m)
{
	if (m == 1)
	{
		comp = 0; swap = 0;
		for (int i = 8; i <= 9; ++i)
			sort::clearFile(i);
		char* empty = "";
		// dla wszystkich n
		for (int i = 5; i <= 100; i += 1)
		{
			// wielokrotnie dla wszystkich n
			for (int j = 0; j < 3; ++j)
			{

				double* tab1 = createTab(1, i);
				printTab(tab1, i);
				double* tab2 = new double[i];
				//std::copy(tab1, tab1 + i, tab2);
				memcpy(tab2, tab1, i * sizeof(double));

				comp = 0; swap = 0;
				printf("%d \n", randomizedSelect(tab1, 0, i - 1, 2));
				printTab(tab2, i);
				quickSort(tab2, 0, i - 1);
				printTab(tab2, i);
				sort::writeToFile(8, i, comp, swap, empty);
				delete[] tab1;

				comp = 0; swap = 0;
				printf("%d \n", select(tab2, 0, i - 1, 2));
				printTab(tab2, i);
				quickSort(tab2, 0, i - 1);
				printTab(tab2, i);
				sort::writeToFile(9, i, comp, swap, empty);
				delete[] tab2;
			}
		}
	}
	sort::plotGnuplot(3);
	return 0;
}

int sort::testSearchWithoutStats(int data_type)
{
	// get size of tab
	int n = 0;
	std::cin >> n;
	// get searching point
	int k_th = 0;
	std::cin >> k_th;
	// result point
	int result = 0;

	std::chrono::time_point<std::chrono::steady_clock> start, end;
	// create tab of desired size and data type
	// then run algorithms
	double* tab1 = createTab(data_type, n);
	double* tab2 = new double[n];
	memcpy(tab2, tab1, n * sizeof(double));

#ifdef DEBUG
	// print on stdout tab values
	for (int i = 0; i < n; i++)
	{
		std::cout << tab1[i] << " ";
	}
	std::cout << std::endl;
#endif

	// RANDOMIZED SELECT
	comp = 0; swap = 0;
	start = std::chrono::high_resolution_clock::now();
	result = sort::randomizedSelect(tab1, 0, n - 1, k_th);
	end = std::chrono::high_resolution_clock::now();

	// print algo time on stderr
#ifdef DEBUG
	std::cerr << "DEBUG FLAG ENABLED TIME ONLY IN APROXIMATION" << std::endl;
#endif
	std::cerr << "Time: ";
	std::cerr << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cerr << "us" << std::endl;
	// print comp and swap on stderr
	std::cerr << "Comp: " << comp << " Swap: " \
		<< swap << std::endl;
	// print on stdout n
	std::cout << n << std::endl;
	// print on stdout tab values
	// with marked k-th value
	for (int i = 0; i < result; i++)
	{
		std::cout << tab1[i] << " ";
	}
	std::cout << "[" << tab1[result] << "] ";
	for (int i = result + 1; i < n; i++)
	{
		std::cout << tab1[i] << " ";
	}
	std::cout << std::endl;

	delete[] tab1;

	// SELECT
	comp = 0; swap = 0;
	start = std::chrono::high_resolution_clock::now();
	result = sort::select(tab2, 0, n - 1, k_th-1);
	end = std::chrono::high_resolution_clock::now();

	// print algo time on stderr
#ifdef DEBUG
	std::cerr << "DEBUG FLAG ENABLED TIME ONLY IN APROXIMATION" << std::endl;
#endif
	std::cerr << "Time: ";
	std::cerr << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cerr << "us" << std::endl;
	// print comp and swap on stderr
	std::cerr << "Comp: " << comp << " Swap: " \
		<< swap << std::endl;
	// output would not be same
	// but we have to be strict with
	// spec so dont print in normal mode
#ifdef DEBUG
	// print on stdout tab values
	// with marked k-th value
	for (int i = 0; i < result; i++)
	{
		std::cout << tab2[i] << " ";
	}
	std::cout << "[" << tab2[result] << "] ";
	for (int i = result + 1; i < n; i++)
	{
		std::cout << tab2[i] << " ";
	}
	std::cout << std::endl;
#endif
	delete[] tab2;

	return 0;
}

int sort::testBinarySearchWithoutStats()
{
	// get size of tab
	int n = 0;
	std::cin >> n;
	// get searching value
	double v = 0;
	std::cin >> v;
	// result value
	int result = 0;

	// create tab of desired size
	double* tab = new double[n + 1];
	// populate tab with values from user
	for (int i = 0; i < n; i++)
	{
		std::cin >> tab[i];
	}

	std::chrono::time_point<std::chrono::steady_clock> start, end;
#ifdef DEBUG
	// print on stdout tab values
	for (int i = 0; i < n; i++)
	{
		std::cout << tab[i] << " ";
	}
	std::cout << std::endl;
#endif

	comp = 0; swap = 0;
	start = std::chrono::high_resolution_clock::now();
	result = sort::binarySearch(tab, 0, n - 1, v);
	end = std::chrono::high_resolution_clock::now();

	// print algo time on stderr
#ifdef DEBUG
	std::cerr << "DEBUG FLAG ENABLED TIME ONLY IN APROXIMATION" << std::endl;
#endif
	std::cerr << "Time: ";
	std::cerr << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cerr << "us" << std::endl;
	// print comp and swap on stderr
	std::cerr << "Comp: " << comp << " Swap: " \
		<< swap << std::endl;


	delete[] tab;

	if (result == NULL)
		return 0;
	else
		return 1;
}

int sort::testSearchWithStats(char* filename, int k)
{
	comp = 0; swap = 0;
	//for (int i = 1; i <= 3; ++i)
	//sort::clearFile(i);

	for (int i = 1000; i <= 100000; i += 1000)
	{
		for (int j = 0; j < k; j++)
		{
			double* tab1 = createTab(1, i);
			//printTab(tab1, i);
			double* tab2 = new double[i];
			memcpy(tab2, tab1, i * sizeof(double));
			double* tab3 = new double[i];
			memcpy(tab3, tab1, i * sizeof(double));

			comp = 0; swap = 0;
			auto start = std::chrono::high_resolution_clock::now();
			randomizedSelect(tab1, 0, i - 1, getRand(1, i - 1));
			auto end = std::chrono::high_resolution_clock::now();
			//printTab(tab1, i);
			sort::writeToFile(8, i, comp, swap, (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), filename);
			delete[] tab1;

			comp = 0; swap = 0;
			start = std::chrono::high_resolution_clock::now();
			select(tab2, 0, i - 1, getRand(1, i - 1));
			end = std::chrono::high_resolution_clock::now();
			//printTab(tab2, i);
			sort::writeToFile(9, i, comp, swap, (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), filename);
			delete[] tab2;

			comp = 0; swap = 0;
			start = std::chrono::high_resolution_clock::now();
			binarySearch(tab3, 0, i - 1, getRand(1, i - 1));
			end = std::chrono::high_resolution_clock::now();
			//printTab(tab3, i);
			sort::writeToFile(10, i, comp, swap, (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), filename);
			delete[] tab3;
		}
	}
	return 0;
}