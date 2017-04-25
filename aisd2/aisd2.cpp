// aisd2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sort.h"
#include "sort_int.h"

<<<<<<< HEAD
int main()
{
=======
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
			i++;
		}
		else if (strcmp(argv[i], "--comp") == 0)
		{
			if (strcmp(argv[i + 1], ">=") == 0)
			{
				order = 1;
			}
			else if (strcmp(argv[i + 1], "<=") == 0)
			{
				order = 2;
			}
			i++;
		}
		else if (strcmp(argv[i], "--stat") == 0)
		{
			filename = argv[i + 1];
			k = atoi(argv[i + 2]);
			stat = 1;
			i = i + 2;
		}
	}
	sort sort;
	if (stat == 0)
	{
		sort.testSortWithoutStats(algo, order);

	}
	else if (stat == 1)
	{
		sort.testSortWithStats(filename, k);
	}
	//free (filename);
>>>>>>> 7f2a5f3... Revert "Revert "Revert "Revert "Add project files.""""
	//sort sort;
	//sort_int sort_int;
	//sort.testSort(1);
	//sort.testMergedSort(1);
	//sort.testSearch(1);
	//sort_int.testSort(1);
<<<<<<< HEAD
=======
	getchar();
>>>>>>> 7f2a5f3... Revert "Revert "Revert "Revert "Add project files.""""
	return 0;
}

