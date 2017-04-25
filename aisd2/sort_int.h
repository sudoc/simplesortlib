#pragma once
class sort_int
{
private:
	int size;
	double * tab;
	int n;
	int comp;
	int swap;

	void swap_(int* tab, int i, int j);
	int writeToFile(int m, int n, int c, int s);
	int clearFile(int m);

public:
	sort_int();
	virtual ~sort_int();

	void countingSort(int* tab, int n, int exp);
	void radixSort(int* arr, int n);

	int* createTab(int m, int n);
	void plotGnuplot(int m);
	int testSort(int m);
};

