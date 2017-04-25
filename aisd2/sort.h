#pragma once
class sort
{
private:
	int size;
	double * tab;
	int n;
	int comp;
	int swap;
	
	void merge(double* tab, int p, int q, int r);
	int quickSortDivide(double* tab, int l, int r);
	void swap_(double* tab, int i, int j);
<<<<<<< HEAD
	int writeToFile(int m, int n, int c, int s);
=======
	int dualPivotQuickSortDivide(double* tab, int l, int r, int* lp);

	int writeToFile(int m, int n, int c, int s, char* filename);
	int writeToFile(int m, int n, int c, int s, int time, char* filename);
>>>>>>> 7f2a5f3... Revert "Revert "Revert "Revert "Add project files.""""
	int clearFile(int m);

	int randomizedSelectDivide(double* tab, int l, int r);
	int selectDivide(double* tab, int l, int r, int pivot);
	int chooseMedianDividePoint(double* tab, int l, int r);
	int medianOfFive(double* tab, int l, int r);
public:
	sort();
	virtual ~sort();

	void insertionSort(double* tab, int l, int r);
	void mergeSort(double* tab, int p, int r);
	void quickSort(double* tab, int l, int r);
<<<<<<< HEAD
=======
	void dualPivotQuickSort(double* tab, int l, int r);
>>>>>>> 7f2a5f3... Revert "Revert "Revert "Revert "Add project files.""""
	void quickSortWithInsertionSort(double* tab, int l, int r);
	void mergeSortWithInsertionSort(double* tab, int p, int r);

	double randomizedSelect(double* tab, int l, int r, int k);
	double select(double* tab, int l, int r, int k);

	double* createTab(int m, int n);
	void plotGnuplot(int m);
	int testSort(int m);
<<<<<<< HEAD
=======
	int testSortWithoutStats(int algo, int order);
	int testSortWithStats(char* filename, int k);

>>>>>>> 7f2a5f3... Revert "Revert "Revert "Revert "Add project files.""""
	int testMergedSort(int m);

	int testSearch(int m);
};

