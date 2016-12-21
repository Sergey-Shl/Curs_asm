#include <thread>
#include <iostream>
#include <vector>

using namespace std;

class matrix
{
public:
	int m, n; // n - количество строк, m - столбцов
	float **mtrx; //Сама матрица

	matrix(int m, int n) 
	{
		this->m = m;
		this->n = n;
		mtrx = new float*[m]; // Выделение памяти под двумерный массив
		for (int i = 0; i < m; i++)
			mtrx[i] = new float[n];
		fill();
	}

	void print() // Печать матрицы
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				printf("%f ", mtrx[i][j]);
			}
			printf("\n");
		}
	}

	void fill(float num = 0) //Заполнение матрицы значением = num
	{
		for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
				mtrx[i][j] = num;
	}
};

void parallelMul(matrix& m1, matrix& m2, matrix& m3, int start, int size)
{
	for (int i = start; i < start + size; i++)
		for (int j = 0; j < m2.n; j++)
		{
			for (int k = 0; k < m2.m; k++)
				m3.mtrx[i][j] += (m1.mtrx[i][k] * m2.mtrx[k][j]);
		}
}

bool parallel(matrix& m1, matrix& m2, matrix& m3)
{
	if (m1.n != m2.m)
		return false;

	int numOfThr = 1000;
	int numOfParts = m1.m;
	vector<thread> threads(numOfThr);
	int partSize = numOfParts / numOfThr;

	int s_t = 0, e_t = 0;
	printf("Multiplication started (%i thread)\n", numOfThr);
	s_t = clock();

	for (int i = 0; i < numOfThr; i++)
	{
		if (i == numOfThr - 1)
		{
			threads.push_back(thread(parallelMul, std::ref(m1), std::ref(m2), std::ref(m3), i * partSize, numOfParts - i * partSize));
			continue;
		}
		threads.push_back(thread(parallelMul, std::ref(m1), std::ref(m2), std::ref(m3), i * partSize, partSize));
	}

	for (int i = 0; i < threads.size(); i++)
	{
		if (threads[i].joinable())
			threads[i].join();
	}

	e_t = clock();
	printf("Multiplication time: %i\n", e_t);

	//m3.print();
}

bool mul(matrix& m1, matrix& m2, matrix& m3)
{
	if (m1.n != m2.m)
		return false;

	int s_t = 0, e_t = 0;
	printf("Multiplication started (%i thread)\n", 1);
	s_t = clock();

	for (int i = 0; i < m1.m; i++)
	for (int j = 0; j < m2.n; j++)
	{
		m3.mtrx[i][j] = 0;
		for (int k = 0; k < m2.m; k++)
			m3.mtrx[i][j] += (m1.mtrx[i][k] * m2.mtrx[k][j]);
	}

	e_t = clock();
	printf("Multiplication time: %i\n", e_t);
	//m3.print();

	return true;
}

int main()
{
	matrix m1(1500, 1500);

	m1.mtrx[0][0] = 5;
	m1.mtrx[0][1] = 8;
	m1.mtrx[0][2] = -4;
	m1.mtrx[1][0] = 6;
	m1.mtrx[1][1] = 9;
	m1.mtrx[1][2] = -5;
	m1.mtrx[2][0] = 4;
	m1.mtrx[2][1] = 7;
	m1.mtrx[2][2] = -3;

	matrix m2(1500, 1500);

	m2.mtrx[0][0] = 3;
	m2.mtrx[0][1] = 2;
	m2.mtrx[0][2] = 5;
	m2.mtrx[1][0] = 4;
	m2.mtrx[1][1] = -1;
	m2.mtrx[1][2] = 3;
	m2.mtrx[2][0] = 9;
	m2.mtrx[2][1] = 6;
	m2.mtrx[2][2] = 5;

	matrix m3(m1.m, m2.n);

	parallel(m1, m2, m3);

	mul(m1, m2, m3);

	system("pause");
	return 0;
}
