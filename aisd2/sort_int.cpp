#include "sort_int.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>


sort_int::sort_int()
{
	srand(time(NULL));
}

sort_int::~sort_int()
{
}

void sort_int::swap_(int* tab, int i, int j)
{
	int tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}

void sort_int::countingSort(int* tab, int n, int exp)
{
	//tablica wyjsciowa
	int* output = new int[n+1];

	//tablica count zawierajaca poszczegolne zliczone elem.
	int count[10] = { 0 };
	int i;
	//memset(count, 0, sizeof(count));

	//policz ile razy wystepuja poszczegone cyfry
	//i zapisz w count
	for (i = 0; i < n; ++i)
		count[(tab[i] / exp) % 10]++;

	//zmodyfikuj count dodajac do siebie poszegolne cyfry po
	//kolei po to aby przedstawialy pozycje w output 
	for (i = 1; i < 10; ++i)
		count[i] += count[i - 1];

	//tworz output poprzez count[] przesuwajac sie po wszystkich
	//elem. w tablicy nieposortowanej, zmiejsz count za kazdym
	//razem gdy zdjemiesz liczbe z oryginalnej tablicy
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(tab[i] / exp) % 10] - 1] = tab[i];
		count[(tab[i] / exp) % 10]--;
	}

	//przekopiuj elementy z output do oryginalnej tablicy
	for (i = 0; i < n; i++ && ++swap)
		tab[i] = output[i];

	delete[] output;
}

/*void countSort(int arr[], int n, int exp)
{
	int output[n]; // output array
	int i, count[10] = { 0 };

	// Store count of occurrences in count[]
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual
	//  position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}*/

void sort_int::radixSort(int* tab, int n)
{
	//znajdz najwieksza liczbe zeby dowiedziec sie ile ma cyfr
	int m = tab[0];
	for (int i = 1; i <= n; ++i)
		if (tab[i] > m)
			m = tab[i];

	//wykonaj countingSort na wszystkich cyfrach po kolei
	for (int exp = 1; m / exp > 0; exp *= 10)
		sort_int::countingSort(tab, n, exp);
}

/*
*	Stworz tablice parametry:
*	m - tryby:
*		1 - ciagi losowe
*		2 - ciagi posortowane
*		3 - ciagi posortowane malejaco
*		dowolna wartosc - ciagi zer
*	n - wielkosc tablicy
*	zwracana wartosc:
*	tab - tablica danych
*/
int* sort_int::createTab(int m, int n)
{
	if (n <= 0)
		return NULL;

	int* tab = new int[n];

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
		radixSort(tab, n);
	}
	//ciagi posortowane malejaco
	else if (m == 3)
	{
		for (int i = 0; i < n; ++i)
		{
			tab[i] = rand();
		}
		radixSort(tab, n);
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

int sort_int::writeToFile(int m, int n, int c, int s)
{
	if (m == 6)
	{
		FILE *f1 = fopen("comp6.txt", "a");
		if (f1 == NULL)
		{
			printf("Error opening file!\n");
			return 1;
		}
		fprintf(f1, "%d %d\n", n, c);
		fclose(f1);

		FILE *f2 = fopen("swap6.txt", "a");
		if (f2 == NULL)
		{
			printf("Error opening file!\n");
			return 1;
		}
		fprintf(f2, "%d %d\n", n, s);
		fclose(f2);
	}
	else if (m == 7)
	{
		FILE *f3 = fopen("comp7.txt", "a");
		if (f3 == NULL)
		{
			printf("Error opening file!\n");
			return 1;
		}
		fprintf(f3, "%d %d\n", n, c);
		fclose(f3);

		FILE *f4 = fopen("swap7.txt", "a");
		if (f4 == NULL)
		{
			printf("Error opening file!\n");
			return 1;
		}
		fprintf(f4, "%d %d\n", n, s);
		fclose(f4);
	}
	return 0;
}

int sort_int::clearFile(int m)
{
	if (m == 6)
	{
		FILE *f1 = fopen("comp6.txt", "w");
		if (f1 == NULL)
		{
			printf("Error opening file!\n");
			return 1;
		}
		fprintf(f1, "");
		fclose(f1);

		FILE *f2 = fopen("swap6.txt", "w");
		if (f2 == NULL)
		{
			printf("Error opening file!\n");
			return 1;
		}
		fprintf(f2, "");
		fclose(f2);
	}
	else if (m == 7)
	{
		FILE *f3 = fopen("comp7.txt", "w");
		if (f3 == NULL)
		{
			printf("Error opening file!\n");
			return 1;
		}
		fprintf(f3, "");
		fclose(f3);

		FILE *f4 = fopen("swap7.txt", "w");
		if (f4 == NULL)
		{
			printf("Error opening file!\n");
			return 1;
		}
		fprintf(f4, "");
		fclose(f4);
	}
	return 0;
}

void sort_int::plotGnuplot(int m)
{
	if (m == 1)
	{
		system("gnuplot -p -e \"plot 'comp06.txt' with lines\"");
	}
	else
	{
		return;
	}
}

void printTab(int* tab, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("tab[%d] = %f\n", i, tab[i]);
	}
}

int sort_int::testSort(int m)
{
	if (m == 1)
	{
		comp = 0; swap = 0;
		clearFile(6);
		// dla wszystkich n
		for (int i = 100; i <= 100000; i += 100)
		{
			// wielokrotnie dla wszystkich n
			for (int j = 0; j < 3; ++j)
			{
				int* tab1 = createTab(1, i);
				//printTab(tab1, i);

				comp = 0; swap = 0;
				radixSort(tab1, i - 1);
				//printTab(tab1, i);
				sort_int::writeToFile(6, i, comp, swap);
				delete[] tab1;
			}
		}
	}
	sort_int::plotGnuplot(1);
	return 0;
}