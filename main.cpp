#include <iostream>
#include <random>
#include <ctime>
#include <thread>

using namespace std;
int *arr;
int *finalArr;


void printArr(int n, unsigned t);

void finalSort(int size)
{
	int first_half_index = 0;
	int half = size / 2;
	int second_half_index = size / 2;
	for (int i = 0; i < size; i++)
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
			for (int j = i; j < size; j++)
				finalArr[j] = arr[j];
			break;
		}
		if (second_half_index > size) {
			for (int j = first_half_index; j < half; j++, i++)
				finalArr[i] = arr[j];
			break;
		}
	}
}

void finalSortNew(int l, int r, int s = -1) {
	int j = 0;
	int size = r - l + 1;
	finalArr = new int[size];
	int first_index = l;
	int second_index = l + size / 2;
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
			for (int k = i; j < size; k++, j++)
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
			for (int k = first_index; j < size; k++, j++)
			{
				finalArr[j] = arr[k];
				//printf("\n%i", finalArr[j]);
			}
			break;
		}
	}

	j = l;
	for (int i = 0; i < size; i++, j++)
	{
		arr[j] = finalArr[i];
		//printf("\n%i", finalArr[i]);
		//printf("\n%i", arr[j]);
	}
	
	//delete[] finalArr;
}

void finalSortInt(int a, int b, bool first_one = true) //0, 3
{
	int size = b - a + 1; //4
	int first_half_index = a; //0
	int half = (a + b) / 2; //2
	int second_half_index = a + size / 2; //2

	for (int i = a; i < a + size; i++)
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
			for (int j = second_half_index; j < a + size; j++, i++)
				finalArr[i] = arr[j];
			break;
		}

		if (second_half_index > b) {
			i++;
			for (int j = first_half_index; j < b; j++, i++)
				finalArr[i] = arr[j];
			break;
		}
	}

	//for (int i = a; i < a + size; i++)
		//arr[i] = finalArr[i];
}

void bubbleSort(int sz)
{
	for (int i = 0; i < sz; i++)
	{
		// Массив просматривается с конца до
		// позиции i и "легкие элементы всплывают"
		for (int j = sz - 1; j > i; j--)
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

void quickSort(int l, int r)
{
	int x = arr[l + (r - l) / 2];
	//запись эквивалентна (l+r)/2, 
	//но не вызввает переполнения на больших данных
	int i = l;
	int j = r;
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

void QuickSortT1(int n) {
	int s_t, e_t;
	finalArr = new int[n];

	cout << "\nQuick sort starts (1 thread)\n";
	s_t = clock();
	quickSort(0, n - 1);
	e_t = clock() - s_t;
	cout << "Quick sort time: " << e_t << endl;
}

void QuickSortT2(int n) {
	int s_t, e_t;
	finalArr = new int[n];
	cout << "\nQuick sort starts (2 thread)\n";

	s_t = clock();
	thread t1(quickSort, 0, n / 2 - 1);
	thread t2(quickSort, n / 2, n - 1);
	t1.join();
	t2.join();
	finalSortNew(0, n - 1);
	e_t = clock() - s_t;

	cout << "Quick sort (2 threads) time: " << e_t << endl;

	delete[] finalArr;
}

void QuickSortT4(int n) {
	int arr_size = n;
	int s_t, e_t = 0;
	finalArr = new int[n];
	cout << "\nQuick sort starts (4 thread)\n";
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
	cout << "Quick sort (4 threads) time: " << e_t << endl;
	delete[] finalArr;

}

void QuickSortT(int n, int t) {
	int arr_size = n;
	int s_t, e_t = 0;
	finalArr = new int[n];
	cout << "\nQuick sort starts (4 thread)\n";
	s_t = clock();
	int k = n / t;
	for (int i = 0; i < t; i++)
	{
		thread thr(quickSort, i*k, (i + 1) * k - 1);
	}
	thread t1(quickSort, 0, n / 4 - 1);
	thread t2(quickSort, n / 4, n / 2 - 1);
	thread t3(quickSort, n / 2, 0.75 * n - 1);
	thread t4(quickSort, 0.75 * n, n - 1);
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	int num_lvls = 0; // 2
	int a = 2;
	while (a < t)
	{
		pow(a, 2);
		num_lvls++;
	}

	//n = 120
	//t = 5
	int num_of_elem = n; // 120
	int num_of_parts = t / 2; // 2
	int prev_num_of_parts = t; // 5
	int prev_size_of_part = n / prev_num_of_parts; // 24
	int size_of_part = n / num_of_parts; // 40
	int unproc[2];
	for (int i = 0; i < num_lvls; i++)
	{
		for (int j = 0; j < num_of_parts; j++)
		{
			finalSortNew(j * size_of_part, ((j + 1) * size_of_part) - 1);
			//finalSortNew(j*prev_size_of_part * num_of_parts, ((j + 1) * prev_size_of_part * num_of_parts) - 1);
		}
		if (prev_num_of_parts % 2 != 0)
		{
			unproc[0] = num_of_parts * size_of_part;
			unproc[1] = n;
			finalSortNew(0, unproc[1], unproc[0]);
		}
		prev_num_of_parts = num_of_parts;
		prev_size_of_part = size_of_part;
		num_of_parts /= 2;
		size_of_part *= 2;
	}

	if (t % 2 != 0)
		finalSortNew(0, n - 1, prev_size_of_part);

	finalSortNew(0, n / 2 - 1);
	finalSortNew(n / 2, n - 1);
	finalSortNew(0, n - 1);



	finalSortNew(0, n / 4 - 1);
	finalSortNew(n / 4, n / 2 - 1);
	finalSortNew(n / 2, 3 * n / 4 - 1);
	finalSortNew(3 * n / 4, n -1);
	finalSortNew(0, n / 2 - 1);
	finalSortNew(n / 2, n - 1);
	finalSortNew(0, n - 1);

	e_t = clock() - s_t;
	cout << "Quick sort (4 threads) time: " << e_t << endl;
	delete[] finalArr;
}

void foo(int t, int n)
{
	int num_lvls = 0; //2
	int a = 2;
	while (a < t)
	{
		a = pow(a, 2);
		num_lvls++;
	}

	//n = 120
	//t = 5
	int num_of_elem = n; // 120
	int prev_num_of_parts = t; // 5
	int prev_size_of_part[2];
	prev_size_of_part[0] = n / prev_num_of_parts; // 24
	prev_size_of_part[1] = 0; // 0
	int num_of_parts = t / 2; // 3
	if (prev_num_of_parts % 2 != 0)
		num_of_parts++; // 3
	int size_of_part[2];
	size_of_part[0] = prev_size_of_part[0] * 2; //48
	size_of_part[1] = prev_size_of_part[1]; // 0
	if (prev_num_of_parts % 2 != 0)
		size_of_part[1] = prev_size_of_part[0]; // 24
	int counter = 0;
	for (int i = 0; i < num_lvls; i++)
	{
		counter = 0;
		for (int j = 0; j < num_of_parts; j++)
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

void foo1(int n, int t)
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
				printf("\n%i %i %i", j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
				unprocessed_int = 0;
				process_uproc = false;
				break;
			}
			if (num_of_parts == 1)
			{
				if (process_uproc)
					printf("\n%i %i %i", j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
				else
					printf("\n%i %i", j * size_of_part, num_of_elem - 1);
				break;
			}
			if (i == num_of_iter - 1 && j == num_of_parts - 1)
			{
				printf("\n%i %i", j * size_of_part, num_of_elem - 1);
				break;
			}
			printf("\n%i %i", j * size_of_part, (j + 1) * size_of_part - 1);
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
			//size_of_part = (num_of_elem - unprocessed_int) / num_of_parts;
			num_of_parts++;
		}
		counter = 0;
	}
}

void BubbleSortTest(int n){
	int s_t, e_t;
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 1000;
	}
	cout << "Bubble sort starts\n";
	s_t = clock();
	bubbleSort(n);
	e_t = clock() - s_t;
	cout << "Buuble sort time: " << e_t << endl;
	cout << arr[0] << " ";
	cout << arr[n - 1] << endl;
}

void printArr(int size, unsigned t)
{
	printf("\n");
	if (t == 0)
	{
		printf("Arr: \n");
		srand(size);
		for (int i = 0; i < 10; i++)
		{
			printf("%i ", arr[rand() % size]);
		}
	}
}

void update_arr(int n)
{
	srand(n);
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 11;
	}
}

int main()
{
	int n;//количество элементов в массиве
	int t;
	cin >> n;
	cin >> t;
	arr = new int[n];

	//foo(t, n);
	foo1(n, t);

	/*printf("\n=====");
	update_arr(n);
	printArr(n, 0);
	QuickSortT1(n);
	printArr(n, 0);

	printf("\n=====");
	update_arr(n);
	printArr(n, 0);
	QuickSortT2(n);
	printArr(n, 0);

	printf("\n=====");
	update_arr(n);
	printArr(n, 0);
	QuickSortT4(n);
	printArr(n, 0);*/

	//delete[] arr;
	printf("\n");
	system("pause");
	return 0;
}



























//#include <iostream>
//#include <stdio.h>
//#include <fstream>
//#include <conio.h>
//#include <thread>
//#include <time.h>
//#include <random>
//#include <Windows.h>
//#include <vector>
//
//typedef unsigned int ui;
//using namespace std;
//
////template <typename T>
//
//void quick_sort(ui* arr, ui l, ui r)
//{
//
//	ui i = l;
//	ui j = r;
//	ui m = (l + r) / 2;
//	ui middle = arr[(i + j) / 2];
//
//	do
//	{
//		while (middle > arr[i]) i++;
//		while (middle < arr[j]) j--;
//
//		if (i <= j)
//		{
//			swap(arr[i], arr[j]);
//			i++;
//			j--;
//		}
//
//	} while (i < j);
//	/*
//
//	if(i < r) function1(arr,i,r);
//	if(j > l) function1(arr,l,j);
//
//	*/
//
//
//}
//
//void foo(ui* arr, ui l, ui r)
//{
//	cout << l << endl;
//}
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	srand(time(NULL));
//	cout << "***DEBUG MOD***" << endl;
//	cout << "* Загрузка завершена " << endl /*<< "* Ожидание ввода" << endl*/;
//	/*
//	cout << " Введите размер массива " << endl;
//	ui N;
//	cin >> N;
//	cout << " Введите кол-во потоков (или ядер) " << endl;
//	short y;
//	cin >> y;
//	*/
//	short N = 6;
//
//	ui Long = 12000000;
//	ui *arr = new ui[Long];
//
//
//
//	for (ui i = 0; i < Long; i++)
//	{
//		arr[i] = rand();
//	}
//
//
//	vector <thread> threads;
//	//for (ui i = 1; i < Long; ++i)
//	//{
//	//	threads.push_back(thread(quick_sort, arr, 0, 12000000));
//	//}
//
//	//std::thread t(quick_sort, arr, 2, 4);
//
//	for (ui i = 1; i < Long; ++i)
//	{
//		threads.push_back(thread(quick_sort, arr, 0, 12000000));
//	}
//
//	for (int i = 0; i < N; i++)
//
//
//		cout << endl << "Поток " << "Основной: " << " Завершено" << endl;
//	Sleep(1000);
//	return 0;
//}
