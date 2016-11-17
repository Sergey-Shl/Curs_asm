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

void finalSortNew(int l, int r) {
	int size = r - l + 1;
	int first_index = l;
	int second_index = l + size / 2;
	int start_second_index = second_index;
	finalArr = new int[size];
	int j = 0;
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
	cout << "Quick sort starts (2 thread)\n";

	s_t = clock();
	thread t1(quickSort, 0, n / 2 - 1);
	thread t2(quickSort, n / 2, n - 1);
	t1.join();
	t2.join();
	e_t = clock() - s_t;

	finalSort(n);
	cout << "Quick sort time: " << e_t << endl;

	delete[] finalArr;
}

void QuickSortT4(int n) {
	int arr_size = n;
	int s_t, e_t = 0;
	finalArr = new int[n];
	cout << "Quick sort starts (4 thread)\n";
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
	cout << "Quick sort time: " << e_t << endl;
	delete[] finalArr;

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
		for (int i = 0; i < size; i++)
		{
			printf("%i ", arr[i]);
		}
	}
	if (t == 1)
	{
		printf("Final Arr: \n");
		for (int i = 0; i < size; i++)
		{
			printf("%i ", finalArr[i]);
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
	cin >> n;
	arr = new int[n];
	update_arr(n);

	QuickSortT1(n);
	update_arr(n);
	QuickSortT2(n);
	update_arr(n);
	QuickSortT4(n);

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
