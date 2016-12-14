#include <iostream>
#include <random>
#include <ctime>
#include <thread>
#include <fstream>

using namespace std;
int *arr;
int *finalArr;
ofstream fout("InfoCPP.log");


void updateArr(int n, int typeOfUpdate) // typeOfUpdate: 0 - Random, 1 - Increase, 2 - Decrease
{
	if (typeOfUpdate == 0)
	{
		srand(n);
		for (int i = 0; i < n; i++)
		{
			arr[i] = rand() % 11;
		}
	}
	else if (typeOfUpdate == 1)
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] = i;
		}
	}
	else
	{
		int j = n - 1;
		for (int i = 0; i < n - 1; i++, j--)
		{
			arr[i] = j;
		}
	}
}

void printArr(int size, int t)
{
	printf("\n");
	if (t == 0)
	{
		printf("Arr: \n");
		srand(size*size);
		for (int i = 0; i < 9; i++)
		{
			printf("%i ", arr[rand() % size]);
		}
		printf("%i ", arr[size - 1]);
	}
	if (t == 1)
	{
		printf("Arr: \n");
		for (int i = 0; i < size; i++)
		{
			printf("%i ", arr[i]);
		}
	}
	printf("\n");
}

void quickSort(int l, int r)
{
	//запись эквивалентна (l+r)/2, но не вызввает переполнения на больших данных
	int x = arr[l + (r - l) / 2];
	int i = l;
	int j = r;
	int temp = 0;
	
	while (i <= j)
	{
		while (arr[i] < x) i++;
		while (arr[j] > x) j--;
		if (i <= j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}
	if (i<r)
		quickSort(i, r);

	if (l<j)
		quickSort(l, j);
}

void finalSort(int l, int r, int s = -1) {
	int j = 0;
	int size = r - l + 1;
	int first_index = l;
	int second_index = l + size / 2;
	if (size % 2 != 0)
		second_index++;
	int start_second_index = second_index;
	if (s != -1)
	{
		second_index = s;
		start_second_index = s;
	}

	for (int i = first_index; i < first_index + size; i++, j++)
	{
		if (arr[first_index] < arr[second_index])
		{
			finalArr[j] = arr[first_index];
			first_index++;
		} 
		else if (arr[second_index] < arr[first_index])
		{
			finalArr[j] = arr[second_index];
			second_index++;
		}
		else
		{
			finalArr[j] = arr[first_index];
			first_index++;
			j++;
			i++;
			finalArr[j] = arr[second_index];
			second_index++;
		}

		if (first_index >= start_second_index)
		{
			i++;
			j++;
			for (int k = i; j < size; k++, j++)
			{
				finalArr[j] = arr[k];
			}
			break;
		}

		if (second_index > r)
		{
			i++;
			j++;
			for (int k = first_index; j < size; k++, j++)
			{
				finalArr[j] = arr[k];
			}
			break;
		}
	}

	j = l;
	for (int i = 0; i < size; i++, j++)
	{
		arr[j] = finalArr[i];
	}
	
}

void separateFinalSort(int n, int t)
{
	int a = 2;
	int num_of_iter = 1;
	while (a < t)
	{
		a *= 2;
		num_of_iter++;
	}
	int num_of_elem = n; 
	int prev_num_of_parts = t; 
	int prev_size_of_part = num_of_elem / prev_num_of_parts;
	int num_of_parts = prev_num_of_parts / 2;
	int size_of_part = num_of_elem / num_of_parts;
	
	if (prev_num_of_parts % 2 != 0)
	{
		size_of_part = (num_of_elem - prev_size_of_part) / num_of_parts;
		num_of_parts++;
	}
	int counter = 0;
	int unprocessed_int = 0;
	bool process_uproc = false;

	for (int i = 0; i < num_of_iter; i++)
	{
		for (int j = 0; j < num_of_parts; j++)
		{
			if (prev_num_of_parts % 2 != 0 && j == num_of_parts - 1)
			{
				unprocessed_int = num_of_elem - counter;
				process_uproc = true;
				break;
			}
			if (num_of_parts % 2 == 0 && unprocessed_int != 0 && j == num_of_parts - 1)
			{
				if (j * size_of_part == num_of_elem - unprocessed_int)
					break;
				finalSort(j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
				//printf("\n%i %i %i\n", j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
				unprocessed_int = 0;
				process_uproc = false;
				break;
			}
			if (num_of_parts == 1)
			{
				if (process_uproc)
				{
					finalSort(j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
 					//printf("\n%i %i %i\n", j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
				}
				else
				{
					finalSort(j * size_of_part, num_of_elem - 1);
					//printf("\n%i %i\n", j * size_of_part, num_of_elem - 1);
				}
				break;
			}
			if (i == num_of_iter - 1 && j == num_of_parts - 1)
			{
				finalSort(j * size_of_part, num_of_elem - 1);
				//printf("\n%i %i\n", j * size_of_part, num_of_elem - 1);
				break;
			}
			finalSort(j * size_of_part, (j + 1) * size_of_part - 1);
			//printf("\n%i %i\n", j * size_of_part, (j + 1) * size_of_part - 1);
			counter += size_of_part;
		}
		prev_num_of_parts = num_of_parts;
		prev_size_of_part = size_of_part;
		num_of_parts = prev_num_of_parts / 2;
		if (num_of_parts == 0)
			return;
		size_of_part = prev_size_of_part * 2;
		if (prev_num_of_parts % 2 != 0)
		{
			num_of_parts++;
		}
		counter = 0;
	}
}

int quickSortT(int n, int t) {
	int s_t, e_t = 0;
	if (t < 2)
	{
		fout << "Quick sort starts (" << t << " threads, " << n << " items)" << endl;
		printf("Quick sort starts (%i threads, %i items)\n", t, n);
		s_t = clock();
		quickSort(0, n - 1);
		e_t = clock() - s_t;
		fout << "Quick sort time: " << e_t << endl;
		printf("Quick sort time: %i\n", e_t);
		return e_t;
	}

	vector<std::thread> thrds(t);
	finalArr = new int[n];
	fout << "Quick sort starts (" << t << " threads, " << n << " items)" << endl;
	printf("Quick sort starts (%i threads, %i items)\n", t, n);
	s_t = clock();

	int part_size = n / t;
	int add_proc = n % t;
	int prev_index = 0;
	int index = part_size;
	if (add_proc > 0)
	{
		index++;
		add_proc--;
	}
	for (int i = 0; i < t; i++)
	{
		if (i == t - 1)
		{
			thrds.push_back(std::thread(quickSort, prev_index, n - 1));
			break;
		}
		else
		{
			thrds.push_back(std::thread(quickSort, prev_index, index - 1));
			prev_index = index;
			index += part_size;
			if (add_proc > 0)
			{
				index++;
				add_proc--;
			}
		}
	}

	for (int i = 0; i < thrds.size(); i++)
	{
		if (thrds[i].joinable())
			thrds[i].join();
	}
	
	separateFinalSort(n, t);

	e_t = clock() - s_t;
	fout << "Quick sort time: " << e_t << endl;
	printf("Quick sort time: %i\n", e_t);
	delete[] finalArr;
	return e_t;
}

void startTest(int numOfI)
{
	const int numOfTests = 5;
	const int numOfTestThreads = 5;
	int timeArr[numOfTestThreads];
	for (int i = 0; i < numOfTestThreads; i++)
		timeArr[i] = 0;
	int numOfItems = numOfI;
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < numOfTests; i++)
		{ 
			fout << "Test #" << i + 1 << " (Type of Arr : " << j << ")" << endl;
			printf("Test #%i (Type of Arr: %i)\n", i + 1, j);
			updateArr(numOfItems, j);
			timeArr[0] += quickSortT(numOfItems, 1);

			updateArr(numOfItems, j);
			timeArr[1] += quickSortT(numOfItems, 2);

			updateArr(numOfItems, j);
			timeArr[2] += quickSortT(numOfItems, 4);

			updateArr(numOfItems, j);
			timeArr[3] += quickSortT(numOfItems, 8);

			updateArr(numOfItems, j);
			timeArr[4] += quickSortT(numOfItems, 16);
		}
		fout << "Time for 1 thread: "<< timeArr[0] << endl;
		printf("Time for 1 thread: %i\n", timeArr[0]);
		fout << "Time for 2 thread: " << timeArr[1] << endl;
		printf("Time for 2 thread: %i\n", timeArr[1]);
		fout << "Time for 4 thread: " << timeArr[2] << endl;
		printf("Time for 4 thread: %i\n", timeArr[2]);
		fout << "Time for 8 thread: " << timeArr[3] << endl;
		printf("Time for 8 thread: %i\n", timeArr[3]);
		fout << "Time for 16 thread: " << timeArr[4] << endl;
		printf("Time for 16 thread: %i\n", timeArr[4]);
	}
}

int main()
{
	const int numOfTestItems = 5;
	int arrOfTestItems[numOfTestItems];
	arrOfTestItems[0] = 100;
	arrOfTestItems[1] = 5000;
	arrOfTestItems[2] = 100000;
	arrOfTestItems[3] = 5000000;
	arrOfTestItems[4] = 100000000;

	fout << "Max hardware threads: " << thread::hardware_concurrency() << endl;

	for (int i = 0; i < numOfTestItems; i++)
	{
		arr = new int[arrOfTestItems[i]];
		startTest(arrOfTestItems[i]);
		delete[] arr;
	}

	printf("Test successfully completed\n");
	system("pause");
	return 0;
}
