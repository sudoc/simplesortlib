// aisd2.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "sort.h"
#include "sort_int.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// algorithm
	int algo = 0;
	// sorting order
	int order = 0;
	// stat mode
	int stat = 0;
	// filename for stats (in stat mode)
	char* filename = "";
	// ammount of replays (in stat mode)
	int k = 0;
	// data type (for searching)
	int data_type = 0;
	// parse args
	for (int i = 1; i < argc; i++)
	{
		//std::cout << argv[i] << std::endl;
		if (strcmp(argv[i], "--type") == 0)
		{
			if (strcmp(argv[i + 1], "insert") == 0)
			{
				algo = 1;
			}
			else if (strcmp(argv[i + 1], "merge") == 0)
			{
				algo = 2;
			}
			else if (strcmp(argv[i + 1], "quick") == 0)
			{
				algo = 3;
			}
			else if (strcmp(argv[i + 1], "select") == 0)
			{
				algo = 4;
			}
			else if (strcmp(argv[i + 1], "heap") == 0)
			{
				algo = 5;
			}
			else if (strcmp(argv[i + 1], "mquick") == 0)
			{
				algo = 6;
			}
			i++;
		}
		else if (strcmp(argv[i], "--asc") == 0)
		{
			order = 1;
		}
		else if (strcmp(argv[i], "--desc") == 0)
		{
			order = 2;
		}
		else if (strcmp(argv[i], "--stat") == 0)
		{
			filename = argv[i + 1];
			k = atoi(argv[i + 2]);
			stat = 1;
			i = i + 2;
		}
		else if (strcmp(argv[i], "--r") == 0)
		{
			data_type = 1;
		}
		else if (strcmp(argv[i], "--p") == 0)
		{
			data_type = 4;
		}
	}
	sort sort;
	sort_int sort_int;
	if (stat == 0)
	{
		if (data_type == 0)
			if (algo == 0 || order == 0)
				return sort.testBinarySearchWithoutStats();
			else
				sort.testSortWithoutStats(algo, order);
		else
			sort.testSearchWithoutStats(data_type);
	}
	else if (stat == 1)
	{
		sort.testSortWithStats(filename, k);
		//sort_int.testSortWithStats(filename, k);
		//sort.testSortWithStats(filename, k);
	}
	//free (filename);
	//sort sort;
	//sort_int sort_int;
	//sort.testSort(1);
	//sort.testMergedSort(1);
	//sort.testSearch(1);
	//sort_int.testSort(1);
	//getchar();
	return 0;
}

