#pragma once
class sort
{
private:
	int size;
	double * tab;
	int n;
	int comp;
	int swap;
	int getRand(const int& A, const int& B);
	void printTab(double* tab, int n);

	void merge(double* tab, int p, int q, int r);
	void mergeReverse(double* tab, int p, int q, int r);
	int quickSortDivide(double* tab, int l, int r);
	int quickSortDivideReverse(double* tab, int l, int r);
	int chooseDividePointMedian(double *tab, int l, int r);
	int quickSortDivideMedian(double* tab, int l, int r);
	void swap_(double* tab, int i, int j);
	int dualPivotQuickSortDivide(double* tab, int l, int r, int* lp);
	void heapify(double* tab, int heap_size, int i);
	void heapifyReverse(double* tab, int heap_size, int i);
	int checkSortingAlgorithm(double *tab, int l, int p, int order);

	int writeToFile(int m, int n, int c, int s, char* filename);
	int writeToFile(int m, int n, int c, int s, int time, char* filename);
	int clearFile(int m);

	int randomizedSelectDivide(double* tab, int l, int r);
	int selectDivide(double* tab, int l, int r, int pivot);
	int chooseRandomDividePoint(int l, int r);
	int chooseMedianDividePoint(double* tab, int l, int r);
	int medianOfFive(double* tab, int l, int r);
public:
	sort();
	virtual ~sort();

	void insertionSort(double* tab, int l, int r);
	void insertionSortReverse(double* tab, int l, int r);
	void mergeSort(double* tab, int p, int r);
	void mergeSortReverse(double* tab, int p, int r);
	void quickSort(double* tab, int l, int r);
	void quickSortReverse(double* tab, int l, int r);
	void dualPivotQuickSort(double* tab, int l, int r);
	void quickSortWithInsertionSort(double* tab, int l, int r);
	void mergeSortWithInsertionSort(double* tab, int p, int r);
	void quickSortWithInsertionSortAndMedian(double* tab, int l, int r);
	void selectionSort(double* tab, int l, int r);
	void selectionSortReverse(double* tab, int l, int r);
	void heapSort(double* tab, int l, int r);
	void heapSortReverse(double* tab, int l, int r);

	int randomizedSelect(double* tab, int l, int r, int k);
	int select(double* tab, int l, int r, int k);
	int binarySearch(double* tab, int l, int r, double v);

	double* createTab(int m, int n);
	void plotGnuplot(int m);
	int testSort(int m);
	int testSortWithoutStats(int algo, int order);
	int testSortWithStats(char* filename, int k);

	int testMergedSort(int m);

	int testSearch(int m);
	int testSearchWithoutStats(int data_type);
	int testBinarySearchWithoutStats();
	int testSearchWithStats(char* filename, int k);
};

