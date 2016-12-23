#include <iostream>
#include <random>
#include <ctime>
#include <thread>
#include <fstream>

using namespace std;
int *arr; // исходнй массив данных
int *tempArr; // Вспомогательный массив
ofstream fout("InfoCPP.log");


void updateArr(int n, int typeOfUpdate) // n - количевстов элементов, typeOfUpdate: 0 - Random, 1 - Возрастаюшая, 2 - Убывающая последовательность
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

void printArr(int size, int t = 1) // Вывод на экран массива данных
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

void quickSort(int l, int r) // Алгоритм Быстрой сортировки
{
	int x = arr[l + (r - l) / 2]; // Определение опорного элемента
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

void newFinalSort(int l, int r, int s = -1)
{
	int size = r - l + 1;
	int firstIndex = l;
	int secondIndex = l + size / 2;
	if (size % 2 != 0)
		secondIndex++;
	int center = secondIndex;
	if (s != -1)
	{
		center = s;
		secondIndex = center;
	}
	int index = 0;
	while ( firstIndex < center && secondIndex < l + size )
	{
		if (arr[firstIndex] <= arr[secondIndex])
		{
			tempArr[index] = arr[firstIndex];
			firstIndex++;
		}
		else
		{
			tempArr[index] = arr[secondIndex];
			secondIndex++;
		}
		index++;
	}
	if (firstIndex < center)
	{
		for (int i = index; i < size; i++)
		{
			tempArr[i] = arr[firstIndex];
			firstIndex++;
		}
	}
	else
	{
		for (int i = index; i < size; i++)
		{
			tempArr[i] = arr[secondIndex];
			secondIndex++;
		}
	}

	int j = l;
	for (int i = 0; i < size; i++, j++) // Копируем значения из временного массива в исходный
	{
		arr[j] = tempArr[i];
	}

	printf("%i, %i, %i\n", l, r, s);

}

void finalSort(int l, int r, int s = -1) // Функция объединения двух отсортированных участков
{
	int size = r - l + 1; //Размер участка
	int first_index = l;
	int second_index = l + size / 2; // Индекс второй сортированной половины
	if (size % 2 != 0)
		second_index++;
	int start_second_index = second_index;
	if (s != -1)   
	{
		second_index = s;
		start_second_index = s;
	}

	unsigned int index = 0;

	for (int i = first_index; i < first_index + size; i++, index++)
	{
		if (arr[first_index] < arr[second_index]) // Если элемент из первой половины меньше, чем из второй, то заносим его первым. Увеличиваем first_index, чтобы сравнивть следующий элемент
		{
			tempArr[index] = arr[first_index];
			first_index++;
		}
		else if (arr[second_index] < arr[first_index])
		{
			tempArr[index] = arr[second_index];
			second_index++;
		}
		else
		{
			tempArr[index] = arr[first_index];
			first_index++;
			index++;
			i++;
			tempArr[index] = arr[second_index];
			second_index++;
		}

		if (first_index >= start_second_index) // Если проверили все элементы первой половины, то оставшиеся из второй записываем без изменения их порядка, они уже отсортированы
		{
			i++;
			index++;
			for (int k = i; index < size; k++, index++)
			{
				tempArr[index] = arr[k];
			}
			break;
		}

		if (second_index > r) // Аналогично предыдущему действию, только для первой половины
		{
			i++;
			index++;
			for (int k = first_index; index < size; k++, index++)
			{
				tempArr[index] = arr[k];
			}
			break;
		}
	}

	int j = l;
	for (int i = 0; i < r - l; i++, j++) // Копируем значения из временного массива в исходный
	{
		arr[j] = tempArr[i];
	}

}

void merger(int numOfItems, int numOfThr)
{
	int numOfParts = numOfThr;
	int *sizeOfParts = new int[numOfParts];
	int index = 0;
	int *indexes = new int[numOfParts];
	int sizeOfPart = numOfItems / numOfThr;
	int addProc = numOfItems % numOfThr;
	int total_size = 0;
	for (int i = 0; i < numOfParts; i++)
	{
		if (addProc > 0)
		{
			indexes[i] = total_size;
			sizeOfParts[i] = sizeOfPart + 1;
			total_size += sizeOfParts[i];
			addProc--;
			continue;
		}
		indexes[i] = total_size;
		sizeOfParts[i] = sizeOfPart;
		total_size += sizeOfParts[i];
	}

	int prevMin = arr[0];
	int min = arr[0];
	int numMin = min;
	while (index != numOfItems)
	{
		int sumOfPrevIndex = 0;
		printf("%i\n", clock());
		for (int i = 0; i < numOfParts; i++)
		{
			sumOfPrevIndex += sizeOfParts[i];
			if (indexes[i] < sumOfPrevIndex)
			{
				min = arr[indexes[i]];
				numMin = i;
				break;
			}
		}
		printf("%i\n", clock());
		sumOfPrevIndex = 0;
		for (int i = 0; i < numOfParts; i++)
		{
			sumOfPrevIndex += sizeOfParts[i];
			if (indexes[i] < sumOfPrevIndex)
			{
				if (min > arr[indexes[i]])
				{
					prevMin = min;
					min = arr[indexes[i]];
					numMin = i;
				}
			}
		}
		tempArr[index] = min;
		index++;
		indexes[numMin]++;
		prevMin = min;
	}

	for (int i = 0; i < numOfItems; i++)
		arr[i] = tempArr[i];

	delete[] indexes;
	delete[] sizeOfParts;

}

void newFS(int numOfItems, int numOfThr)
{
	int a = 2;
	int numOfLevels = 1;
	while (a < numOfThr)
	{
		a *= 2;
		numOfLevels++;
	}

	int numOfUnprocessed = 0;
	int numOfItemsForProc = numOfItems;
	int processedOnCurrentLvl = 0;
	int prevNumOfParts = numOfThr; // 11
	int currentNumOfParts = prevNumOfParts / 2; // 5
	if (prevNumOfParts % 2 != 0)
		currentNumOfParts++;
	int sizeOfPart = numOfItems / prevNumOfParts; // 22
	int sizeOfCurrentPart = sizeOfPart; // Размер текущей части
	int addProc = numOfItems % prevNumOfParts; // Дополнительные элементы, которые необходимо обработать
	

	for (int i = 0; i < numOfLevels; i++)
	{
		int x1 = -1, x2 = -1, x = -1;
		int separaters = 0;
		for (int j = 0; j < numOfItems; j++)
		{
			if (j == 0)
			{
				x1 = 0;
				j += sizeOfPart - 1;
			}
			if (arr[j - 1] > arr[j])
			{
				separaters++;
				if (separaters % 2 != 0)
				{
					x = j;
					j += sizeOfPart - 1;
				}
				if (separaters % 2 == 0)
				{
					x2 = j;
					newFinalSort(x1, x2 - 1, x);
					x1 = x2;
					j += sizeOfPart - 1;
				}
			}
			if (j >= numOfItems - 1)
			{
				if (separaters % 2 != 0)
				{
					x2 = numOfItems;
					newFinalSort(x1, x2 - 1, x);
					if (x1 == 0 && x2 == numOfItems)
						return;
					j += sizeOfPart - 1;
					continue;
				}
				else
				{
					numOfUnprocessed = numOfItems - x2;
				}
			}
		}
		sizeOfPart *= 2;
	}

}

void startFinalSort(int n, int t) // Функция для упарвления объединением множества результатов сортировок в один
{
	int a = 2;
	int num_of_iter = 1;
	while (a < t)
	{
		a *= 2;
		num_of_iter++;
	}
	int num_of_elem = n;
	int prev_num_of_parts = t; // Количество отсортированных участков на самом нижнем уровне
	int prev_size_of_part = num_of_elem / prev_num_of_parts; // Размер отсортированных областей
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
				newFinalSort(j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
				unprocessed_int = 0;
				process_uproc = false;
				break;
			}
			if (num_of_parts == 1)
			{
				if (process_uproc)
				{
					newFinalSort(j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
				}
				else
				{
					newFinalSort(j * size_of_part, num_of_elem - 1);
				}
				break;
			}
			if (i == num_of_iter - 1 && j == num_of_parts - 1)
			{
				newFinalSort(j * size_of_part, num_of_elem - 1);
				break;
			}
			newFinalSort(j * size_of_part, (j + 1) * size_of_part - 1);
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

int parallelQuickSort(int n, int t) // Функция многопотоковой сортировки
{
	int s_t, e_t = 0; // Переменные для измерения времени выполнения
	if (t == 1) // Если поток только один
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
	tempArr = new int[n];
	fout << "Quick sort starts (" << t << " threads, " << n << " items)" << endl;
	printf("Quick sort starts (%i threads, %i items)\n", t, n);
	s_t = clock();

	int part_size = n / t; // Размер области для выполнения
	int add_proc = n % t; // Дополнительные элементы, которые необходимо обработать
	int prev_index = 0;
	int index = part_size;
	if (add_proc > 0) // Добавление еще одного элемента к интервалу для равномерно распределения задачи
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

	for (int i = 0; i < thrds.size(); i++) // Создание и заупск потоков
	{
		if (thrds[i].joinable())
			thrds[i].join();
	}

	thrds.clear();

	//startFinalSort(n, t);
	printArr(n);

	//merger(n, t);
	newFS(n, t);
	//newFinalSort(0, 11);
	//finalSort(0, 12, 7);

	e_t = clock() - s_t;
	fout << "Quick sort time: " << e_t << endl;
	printf("Quick sort time: %i\n", e_t);
	delete[] tempArr;
	tempArr = NULL;
	return e_t;
}

void startTest(int numOfItems, int numOfThreads, int numOfTests) // Функция тестирования
{
	int typeOfArr = 0; // 0 - Random, 1 - Возрастаюшая, 2 - Убывающая последовательность
	int totalTime = 0; 

	arr = new int[numOfItems]; // Выделение памяти для массива данных

	for (int i = 0; i < numOfTests; i++)
	{
		updateArr(numOfItems, typeOfArr);
		printArr(numOfItems);
		fout << "Test #" << i + 1 << " (Type of Arr : " << typeOfArr << ")" << endl;
		printf("Test #%i (Type of Arr: %i)\n", i + 1, typeOfArr);
		totalTime += parallelQuickSort(numOfItems, numOfThreads);
	}

	fout << "Total time for " << numOfThreads << " threads: " << totalTime << endl << "=============" << endl;
	printf("Total time for %i threads: %i\n=============\n", numOfThreads ,totalTime);
	printArr(numOfItems);
	delete[] arr;
	arr = NULL;
}



int main()
{
	// Проведение тестирования
	startTest(25, 3, 1);
	/*startTest(100000000, 2, 1);
	startTest(100000000, 4, 1);
	startTest(100000000, 8, 1);
	startTest(100000000, 16, 1);
	startTest(100000000, 100, 1);
	startTest(100000000, 1000, 1);*/
	//startTest(1000000, 500, 1);

	printf("Test successfully completed\n");
	system("pause");
	return 0;
}
