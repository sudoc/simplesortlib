#include "sort.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>

sort::sort()
{
	srand(time(NULL));
}

sort::~sort()
{
}

void sort::insertionSort(double* tab, int l, int r)
{
	if (r-l <= 1)
		return;// tab;

	double key;
	int j;

	//sprawdzaj od 2 bo 1 jest juz posortowany
	for (int i = l+1; i <= r; ++i)
	{
		key = tab[i];
		//porownuj klucz z reszta po kolei
		for (j = i - 1; j >= 0 && tab[j] > key && ++comp; j--)
		{
			tab[j + 1] = tab[j];
			++swap;
		}
		tab[j + 1] = key;
		++swap;
	}

	//return tab;
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
	//tmp1[n1] = 0; //NULL
	//tmp2[n2] = 0; //NULL
	i = 0;
	j = 0;
	k = p;
	while (i < n1 && j < n2) 
	{
		if (tmp2[j] < tmp1[i] && ++comp) 
		{
			tab[k++] = tmp2[j++]; ++swap;
		}
		else 
		{
			tab[k++] = tmp1[i++]; ++swap;
		}
	}
	while (i < n1) 
	{
		tab[k++] = tmp1[i++]; ++swap;
	}
	while (j < n2) 
	{
		tab[k++] = tmp2[j++]; ++swap;
	}
	/*for (int k = p; k <= r; ++k)
	{
		if (tmp1[i] <= tmp2[j] && ++comp)
		{
			tab[k] = tmp1[i]; ++swap;
			//if(i!=n1)
				++i;
		}
		else
		{
			tab[k] = tmp2[j]; ++swap;
			//if (j != n2)
				++j;
		}
	}
	*/
	delete[] tmp1;
	delete[] tmp2;
	//return tab;
}

void sort::mergeSort(double* tab, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) >> 1;
		mergeSort(tab, p, q);
		mergeSort(tab, q + 1, r);
		merge(tab, p, q, r);
	}
}

void sort::mergeSortWithInsertionSort(double* tab, int p, int r)
{
	int j = r - p;

	if (j < 0)
		return;
	else if (j < 11 && j > 0)
	{
		insertionSort(tab, p, r);
	}
	else
	{
		int q = (p + r) >> 1;
		mergeSort(tab, p, q);
		mergeSort(tab, q + 1, r);
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
			//przenies elem. na lewa strone
			sort::swap_(tab, i, position); ++swap;
			//przesun pozycje
			++position;
		}
	}
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
		//sortuj lewa czesc
		quickSort(tab, l, i - 1);
		//sortuj prawa czesc
		quickSort(tab, i + 1, r);
	}
	//return tab;
}

void sort::quickSortWithInsertionSort(double* tab, int l, int r)
{
	int j = r - l;
	//jezeli jest jakis element
	if (j < 0)
		return;
	else if (j < 12 && j > 0)
	{
		insertionSort(tab, l, r);
	}
	else
	{
		//podziel problem na pol i zapamietaj punkt
		int i = quickSortDivide(tab, l, r);
		//sortuj lewa czesc
		quickSortWithInsertionSort(tab, l, i - 1);
		//sortuj prawa czesc
		quickSortWithInsertionSort(tab, i + 1, r);
	}
}

int chooseRandomDividePoint(int l, int r)
{
	//element losowy z przedzialu
	return floor(rand() % (r - l + 1)) + l;
}

int sort::randomizedSelectDivide(double* tab, int l, int r)
{
	int pivot = chooseRandomDividePoint(l, r);
	double pivotValue = tab[pivot];
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
			//przenies elem. na lewa strone
			sort::swap_(tab, i, position); ++swap;
			//przesun pozycje
			++position;
		}
	}
	//przywroc pivot na swoje miejsce
	sort::swap_(tab, position, r); ++swap;
	return position;
}

double sort::randomizedSelect(double* tab, int l, int r, int k)
{
	//jezeli w zakresie jest tylko jeden element
	if (l >= r)
		return tab[l];
	//idiotoodpornosc (k poza zakresem)
	if (r - k <= l)
		return NULL;

	if (l < r)
	{
		//podziel problem na czesci losowo
		int mid = randomizedSelectDivide(tab, l, r);
		//poprawka na zakres
		int i = mid - l + 1;
		//jezeli element zostal znaleziony
		if (i == k)
			return tab[mid];
		//jezeli element jest w lewej czesci
		else if (k < i)
			return randomizedSelect(tab, l, mid - 1, k);
		else //jezeli w prawej
			return randomizedSelect(tab, mid + 1, r, k - i);
	}
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
		return medianOfFive(tab, l, r);

	int last;
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
		//przenies ja na poczatek przedzialu
		swap_(tab, median5, l + floor((i - l) / 5)); ++swap;
	}
	//policz mediane wszystkich median z podgrup 
	return select(tab, l, l + ceil((r - l) / 5) - 1, l + (r - l) / 10);
}

int sort::selectDivide(double* tab, int l, int r, int pivot)
{
	//int pivot = chooseMedianDividePoint(l, r);
	double pivotValue = tab[pivot];
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
			//przenies elem. na lewa strone
			sort::swap_(tab, i, position); ++swap;
			//przesun pozycje
			++position;
		}
	}
	//przywroc pivot na swoje miejsce
	sort::swap_(tab, position, r); ++swap;
	return position;
}

double sort::select(double* tab, int l, int r, int k)
{
	if (l == r)
		return l;
	//wybieramy pivota za pomoca mediany median
	int pivot = chooseMedianDividePoint(tab, l, r);
	//dzielimy tablice wzgledem znalezionego pivota
	pivot = selectDivide(tab, l, r, pivot);

	//pivot jest rozwiazaniem
	if (k == pivot)
		return k;
	//pivot jest wiekszy od poszukiwanej statystki poz.
	else if (k < pivot)
		return select(tab, l, pivot - 1, k);
	//pivot jest mniejszy ..
	else
		return select(tab, pivot + 1, r, k);
}

/*
	Stworz tablice parametry:
	m - tryby:
		1 - ciagi losowe
		2 - ciagi posortowane
		3 - ciagi posortowane malejaco
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
			tab[i] = rand();
		}
	}
	//ciagi posortowane
	else if (m == 2)
	{
		for (int i = 0; i < n; ++i)
		{
			tab[i] = rand();
		}
		quickSort(tab, 0, n);
	}
	//ciagi posortowane malejaco
	else if (m == 3)
	{
		for (int i = 0; i < n; ++i)
		{
			tab[i] = rand();
		}
		quickSort(tab, 0, n);
		int j = n;
		for (int i = 0; i < n >> 1; ++i)
		{
			swap_(tab, i, j);
			--j;
		}
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

int sort::writeToFile(int m, int n, int c, int s)
{ 
	char* out = (char*)malloc(sizeof(char*) * 10);
	sprintf(out, "%s%02d%s", "comp", m, ".txt");

	FILE *f1 = fopen(out, "a");
	if (f1 == NULL)
	{
		printf("Error opening file!\n");
		return 1;
	}
	fprintf(f1, "%d %d\n", n, c);
	fclose(f1);

	sprintf(out, "%s%02d%s", "swap", m, ".txt");
	FILE *f2 = fopen(out, "a");
	if (f2 == NULL)
	{
		printf("Error opening file!\n");
		return 1;
	}
	fprintf(f2, "%d %d\n", n, s);
	fclose(f2);

	free(out);
	return 0;
}

int sort::clearFile(int m)
{
	char* out = (char*)malloc(sizeof(char*) * 10);
	sprintf(out, "%s%02d%s", "comp", m, ".txt");

	FILE *f1 = fopen(out, "w");
	if (f1 == NULL)
	{
		printf("Error opening file!\n");
		return 1;
	}
	fprintf(f1, "");
	fclose(f1);

	sprintf(out, "%s%02d%s", "swap", m, ".txt");
	FILE *f2 = fopen(out, "w");
	if (f2 == NULL)
	{
		printf("Error opening file!\n");
		return 1;
	}
	fprintf(f2, "");
	fclose(f2);

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

void printTab(double* tab, int n)
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

		// dla wszystkich n
		for (int i = 100; i <= 100000; i += 100)
		{
			// wielokrotnie dla wszystkich n
			for (int j = 0; j < 3; ++j)
			{

				double* tab1 = createTab(1, i);
				//printTab(tab1, i);
				double* tab2 = new double[i];
				std::copy(tab1, tab1 + i, tab2);
				double* tab3 = new double[i];
				std::copy(tab1, tab1 + i, tab3);

				comp = 0; swap = 0;
				insertionSort(tab1, 0, i - 1);
				//printTab(tab2, i);
				sort::writeToFile(1, i, comp, swap);
				delete[] tab1;

				comp = 0; swap = 0;
				mergeSort(tab2, 0, i-1);
				//printTab(tab3, i);
				sort::writeToFile(2, i, comp, swap);
				delete[] tab2;

				comp = 0; swap = 0;
				quickSort(tab3, 0, i-1);
				//printTab(tab3, i);
				sort::writeToFile(3, i, comp, swap);
				delete[] tab3;
			}
		}
	}
	sort::plotGnuplot(1);
	return 0;
}

int sort::testMergedSort(int m)
{
	if (m == 1)
	{
		comp = 0; swap = 0;
		for(int i=1;i<=5;++i)
			sort::clearFile(i);
		
		// dla wszystkich n
		for (int i = 2; i <= 100; i += 1)
		{
			// wielokrotnie dla wszystkich n
			for (int j = 0; j < 3; ++j)
			{

				double* tab1 = createTab(1, i);
				//printTab(tab1, i);
				double* tab2 = new double[i];
				std::copy(tab1, tab1 + i, tab2);
				double* tab3 = new double[i];
				std::copy(tab1, tab1 + i, tab3);
				double* tab4 = new double[i];
				std::copy(tab1, tab1 + i, tab4);
				double* tab5 = new double[i];
				std::copy(tab1, tab1 + i, tab5);

				comp = 0; swap = 0;
				insertionSort(tab1, 0, i - 1);
				//printTab(tab1, i);
				sort::writeToFile(1, i, comp, swap);
				delete[] tab1;

				comp = 0; swap = 0;
				mergeSort(tab2, 0, i - 1);
				//printTab(tab2, i);
				sort::writeToFile(2, i, comp, swap);
				delete[] tab2;

				comp = 0; swap = 0;
				quickSort(tab3, 0, i - 1);
				//printTab(tab3, i);
				sort::writeToFile(3, i, comp, swap);
				delete[] tab3;

				comp = 0; swap = 0;
				quickSortWithInsertionSort(tab4, 0, i - 1);
				//printTab(tab4, i);
				sort::writeToFile(4, i, comp, swap);
				delete[] tab4;

				comp = 0; swap = 0;
				mergeSortWithInsertionSort(tab5, 0, i - 1);
				//printTab(tab5, i);
				sort::writeToFile(5, i, comp, swap);
				delete[] tab5;
			}
		}
	}
	sort::plotGnuplot(2);
	return 0;
}

int sort::testSearch(int m)
{
	if (m == 1)
	{
		comp = 0; swap = 0;
		for (int i = 8; i <= 9; ++i)
			sort::clearFile(i);

		// dla wszystkich n
		for (int i = 5; i <= 100; i += 1)
		{
			// wielokrotnie dla wszystkich n
			for (int j = 0; j < 3; ++j)
			{

				double* tab1 = createTab(1, i);
				printTab(tab1, i);
				double* tab2 = new double[i];
				std::copy(tab1, tab1 + i, tab2);

				comp = 0; swap = 0;
				printf("%f \n", randomizedSelect(tab1, 0, i - 1, 2));
				printTab(tab2, i);
				quickSort(tab2, 0, i - 1);
				printTab(tab2, i);
				sort::writeToFile(8, i, comp, swap);
				delete[] tab1;

				comp = 0; swap = 0;
				printf("%f \n", select(tab2, 0, i - 1, 2));
				printTab(tab2, i);
				quickSort(tab2, 0, i - 1);
				printTab(tab2, i);
				sort::writeToFile(9, i, comp, swap);
				delete[] tab2;
			}
		}
	}
	sort::plotGnuplot(3);
	return 0;
}