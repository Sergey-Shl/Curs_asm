#include <iostream>
#include <random>
#include <ctime>
#include <thread>

typedef unsigned long int uli;

using namespace std;
uli *arr;
uli *finalArr;

void printArr(uli size, uli t);
void foo1(uli n, uli t);

void finalSort(uli size)
{
	uli first_half_index = 0;
	uli half = size / 2;
	uli second_half_index = size / 2;
	for (uli i = 0; i < size; i++)
	{
		if (arr[first_half_index] < arr[second_half_index])
		{
			finalArr[i] = arr[first_half_index];
			first_half_index++;
		}
		else if (arr[first_half_index] > arr[second_half_index])
		{
			finalArr[i] = arr[second_half_index];
			second_half_index++;
		}
		else {
			finalArr[i] = arr[first_half_index];
			i++;
			finalArr[i] = arr[second_half_index];
			first_half_index++;
			second_half_index++;
		}

		if (first_half_index > half) {
			for (uli j = i; j < size; j++)
				finalArr[j] = arr[j];
			break;
		}
		if (second_half_index > size) {
			for (uli j = first_half_index; j < half; j++, i++)
				finalArr[i] = arr[j];
			break;
		}
	}
}

//+
void finalSortNew(uli l, uli r, uli s = -1) {
	uli j = 0;
	uli size = r - l + 1;
	//finalArr = new uli[size];
	uli first_index = l;
	uli second_index = l + size / 2;
	if (size % 2 != 0)
		second_index++;
	uli start_second_index = second_index;
	if (s != -1)
	{
		second_index = s;
		start_second_index = s;
	}

	for (uli i = first_index; i < first_index + size; i++, j++)
	{
		if (arr[first_index] < arr[second_index])
		{
			finalArr[j] = arr[first_index];
			//printf("\n%i", finalArr[j]);
			first_index++;
		} 
		else if (arr[second_index] < arr[first_index])
		{
			finalArr[j] = arr[second_index];
			//printf("\n%i", finalArr[j]);
			second_index++;
		}
		else
		{
			finalArr[j] = arr[first_index];
			//printf("\n%i", finalArr[j]);
			first_index++;
			j++;
			i++;
			finalArr[j] = arr[second_index];
			//printf("\n%i", finalArr[j]);
			second_index++;
		}

		if (first_index >= start_second_index)
		{
			i++;
			j++;
			for (uli k = i; j < size; k++, j++)
			{
				finalArr[j] = arr[k];
				//printf("\n%i", finalArr[j]);
			}
			break;
		}

		if (second_index > r)
		{
			i++;
			j++;
			for (uli k = first_index; j < size; k++, j++)
			{
				finalArr[j] = arr[k];
				//printf("\n%i", finalArr[j]);
			}
			break;
		}
	}

	j = l;
	for (uli i = 0; i < size; i++, j++)
	{
		arr[j] = finalArr[i];
		//printf("\n%i", finalArr[i]);
		//printf("\n%i", arr[j]);
	}
	
	//delete[] finalArr;
}

void finalSortInt(uli a, uli b, bool first_one = true) //0, 3
{
	uli size = b - a + 1; //4
	uli first_half_index = a; //0
	uli half = (a + b) / 2; //2
	uli second_half_index = a + size / 2; //2

	for (uli i = a; i < a + size; i++)
	{
		if (arr[first_half_index] < arr[second_half_index])
		{
			finalArr[i] = arr[first_half_index];
			first_half_index++;
		}
		else if (arr[first_half_index] > arr[second_half_index])
		{
			finalArr[i] = arr[second_half_index];
			second_half_index++;
		}
		else {
			finalArr[i] = arr[first_half_index];
			first_half_index++;
			i++;
			finalArr[i] = arr[second_half_index];
			second_half_index++;
		}

		if (first_half_index > half) {
			i++;
			for (uli j = second_half_index; j < a + size; j++, i++)
				finalArr[i] = arr[j];
			break;
		}

		if (second_half_index > b) {
			i++;
			for (uli j = first_half_index; j < b; j++, i++)
				finalArr[i] = arr[j];
			break;
		}
	}

	//for (uli i = a; i < a + size; i++)
		//arr[i] = finalArr[i];
}

void bubbleSort(uli sz)
{
	for (uli i = 0; i < sz; i++)
	{
		// Массив просматривается с конца до
		// позиции i и "легкие элементы всплывают"
		for (uli j = sz - 1; j > i; j--)
		{
			// Если соседние элементы расположены
			// в неправильном порядке, то меняем
			// их местами
			if (arr[j] < arr[j - 1])
			{
				swap(arr[j], arr[j - 1]);
			}
		}
	}
}

void quickSort(uli l, uli r)
{
	uli x = arr[l + (r - l) / 2];
	//запись эквивалентна (l+r)/2, 
	//но не вызввает переполнения на больших данных
	uli i = l;
	uli j = r;
	//код в while обычно выносят в процедуру particle
	while (i <= j)
	{
		while (arr[i] < x) i++;
		while (arr[j] > x) j--;
		if (i <= j)
		{
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	if (i<r)
		quickSort(i, r);

	if (l<j)
		quickSort(l, j);
}

void QuickSortT1(uli n) {
	uli s_t, e_t;
	finalArr = new uli[n];

	printf("\nQuick sort starts (%i thread, %i items)\n", 1, n);
	s_t = clock();
	quickSort(0, n - 1);
	e_t = clock() - s_t;
	printf("Quick sort time: %i", e_t);
}

void QuickSortT2(uli n) {
	uli s_t, e_t;
	finalArr = new uli[n];
	printf("\nQuick sort starts (%i thread, %i items)\n", 2, n);

	s_t = clock();
	thread t1(quickSort, 0, n / 2 - 1);
	thread t2(quickSort, n / 2, n - 1);
	t1.join();
	t2.join();
	printf("Quick sort time witout final sort: %i\n", clock() - s_t);
	finalSortNew(0, n - 1);
	e_t = clock() - s_t;

	printf("Quick sort time: %i", e_t);

	delete[] finalArr;
}

void QuickSortT4(uli n) {
	uli arr_size = n;
	uli s_t, e_t = 0;
	finalArr = new uli[n];
	printf("\nQuick sort starts (%i thread, %i items)\n", 4, n);
	s_t = clock();
	thread t1(quickSort, 0, n / 4 - 1);
	thread t2(quickSort, n / 4, n / 2 - 1);
	thread t3(quickSort, n / 2, 0.75 * n - 1);
	thread t4(quickSort, 0.75 * n, n - 1);
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	finalSortNew(0, n / 2 - 1);
	finalSortNew(n / 2, n - 1);
	finalSortNew(0, n - 1);
	
	e_t = clock() - s_t;
	printf("Quick sort time: %i", e_t);
	delete[] finalArr;

}

void QuickSortT(uli n, uli t) {
	vector<std::thread> thrds;
	uli s_t, e_t = 0;
	finalArr = new uli[n];
	printf("\nQuick sort starts (%i thread, %i items)\n", t, n);
	s_t = clock();

	uli part_size = n / t;
	uli add_proc = n % t;
	uli prev_index = 0;
	uli index = part_size;
	if (add_proc > 0)
	{
		index++;
		add_proc--;
	}
	for (uli i = 0; i < t; i++)
	{
		if (i == t - 1)
		{
			thrds.push_back(std::thread(quickSort, prev_index, n - 1));
			//printf("Thread %i  started [%i, %i]\n", i, prev_index, n - 1);
			break;
		}
		thrds.push_back(std::thread(quickSort, prev_index, index - 1));
		//printf("Thread %i was started [%i, %i]\n", i, prev_index, index - 1);
		prev_index = index;
		index += part_size;
		if (add_proc > 0)
		{
			index++;
			add_proc--;
		}
	}

	for (uli i = 0; i < t; i++)
	{
		thrds[i].join();
	}

	foo1(n, t);

	e_t = clock() - s_t;
	printf("Quick sort time: %i", e_t);
	delete[] finalArr;
}

void foo(uli t, uli n)
{
	uli num_lvls = 0; //2
	uli a = 2;
	while (a < t)
	{
		a = pow(a, 2);
		num_lvls++;
	}

	//n = 120
	//t = 5
	uli num_of_elem = n; // 120
	uli prev_num_of_parts = t; // 5
	uli prev_size_of_part[2];
	prev_size_of_part[0] = n / prev_num_of_parts; // 24
	prev_size_of_part[1] = 0; // 0
	uli num_of_parts = t / 2; // 3
	if (prev_num_of_parts % 2 != 0)
		num_of_parts++; // 3
	uli size_of_part[2];
	size_of_part[0] = prev_size_of_part[0] * 2; //48
	size_of_part[1] = prev_size_of_part[1]; // 0
	if (prev_num_of_parts % 2 != 0)
		size_of_part[1] = prev_size_of_part[0]; // 24
	uli counter = 0;
	for (uli i = 0; i < num_lvls; i++)
	{
		counter = 0;
		for (uli j = 0; j < num_of_parts; j++)
		{
			if (j == num_of_parts - 1 && prev_num_of_parts % 2 != 0)
			{
				break;
			}
			if (j == num_of_parts - 1 && counter + size_of_part[0] != n)
				printf("\n%i %i %i", j * size_of_part[0], n, counter);
			printf("\n%i %i", j * size_of_part[0], (j + 1) * size_of_part[0] - 1);
			counter += size_of_part[0];
		}
		prev_num_of_parts = num_of_parts;
		prev_size_of_part[0] = size_of_part[0];
		prev_size_of_part[1] = size_of_part[1];
		size_of_part[0] *= 2;
		num_of_parts /= 2;
		if (prev_num_of_parts % 2 != 0)
		{
			num_of_parts++;
			size_of_part[1] = prev_size_of_part[1];
		}
	}

	if (counter != n)
		printf("\n%i %i %i", 0, n - 1, counter);
	else
		printf("\n%i %i", 0, n - 1);

}

//+
void foo1(uli n, uli t)
{
	uli a = 2;
	uli num_of_iter = 1;
	while (a < t)
	{
		a *= 2;
		num_of_iter++;
	}
	uli num_of_elem = n; 
	uli prev_num_of_parts = t; 
	uli prev_size_of_part = num_of_elem / prev_num_of_parts;
	uli num_of_parts = prev_num_of_parts / 2;
	uli size_of_part = num_of_elem / num_of_parts;
	
	if (prev_num_of_parts % 2 != 0)
	{
		size_of_part = (num_of_elem - prev_size_of_part) / num_of_parts;
		num_of_parts++;
	}
	uli counter = 0;
	uli unprocessed_int = 0;
	bool process_uproc = false;

	for (uli i = 0; i < num_of_iter; i++)
	{
		for (uli j = 0; j < num_of_parts; j++)
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
				finalSortNew(j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
				//printf("\n%i %i %i\n", j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
				unprocessed_int = 0;
				process_uproc = false;
				break;
			}
			if (num_of_parts == 1)
			{
				if (process_uproc)
				{
					finalSortNew(j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
 					//printf("\n%i %i %i\n", j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
				}
				else
				{
					finalSortNew(j * size_of_part, num_of_elem - 1);
					//printf("\n%i %i\n", j * size_of_part, num_of_elem - 1);
				}
				break;
			}
			if (i == num_of_iter - 1 && j == num_of_parts - 1)
			{
				finalSortNew(j * size_of_part, num_of_elem - 1);
				//printf("\n%i %i\n", j * size_of_part, num_of_elem - 1);
				break;
			}
			finalSortNew(j * size_of_part, (j + 1) * size_of_part - 1);
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

void BubbleSortTest(uli n){
	uli s_t, e_t;
	
	cout << "Bubble sort starts\n";
	s_t = clock();
	bubbleSort(n);
	e_t = clock() - s_t;
	cout << "Buuble sort time: " << e_t << endl;
}

//+
void printArr(uli size, uli t)
{
	printf("\n");
	if (t == 0)
	{
		printf("Arr: \n");
		srand(size*size);
		for (uli i = 0; i < 9; i++)
		{
			printf("%i ", arr[rand() % size]);
		}
		printf("%i ", arr[size - 1]);
	}
	if (t == 1)
	{
		printf("Arr: \n");
		for (uli i = 0; i < size; i++)
		{
			printf("%i ", arr[i]);
		}
	}
	printf("\n");
}

void update_arr(uli n)
{
	srand(n);
	for (uli i = 0; i < n; i++)
	{
		arr[i] = rand() % 11;
	}
}

uli main()
{
	uli n;//количество элементов в массиве
	uli t;
	cin >> n;
	cin >> t;
	arr = new uli[n];

	//printf("\n=====");
	//update_arr(n);
	////printArr(n, 0);
	//QuickSortT1(n);
	////printArr(n, 0);

	printf("\n=====");
	update_arr(n);
	//printArr(n, 0);
	QuickSortT2(n);
	//printArr(n, 0);

	printf("\n=====");
	update_arr(n);
	//printArr(n, 0);
	QuickSortT4(n);
	//printArr(n, 0);

	////for (uli i = t; i < t + 10; i++)
	//	printf("\n=====");
	//	update_arr(n);
	//	printArr(n, 0);
	//	QuickSortT(n, t);
	//	printArr(n, 0);

	delete[] arr;
	printf("\n");
	system("pause");
	return 0;
}
