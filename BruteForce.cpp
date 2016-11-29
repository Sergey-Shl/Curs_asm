#include <string>
#include <thread>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <time.h>

typedef unsigned long int uli;

using namespace std;

const uli PASS_LENGHT = 5;
bool solved = false;
int start_time = 0;
int finish_time = 0;

uli* passList;

uli num_of_signs(uli lenght)
{
	uli l = 10;
	l = pow(l, lenght - 1);
	return l;
}

void genPass(uli passLenght, char* p, bool genNum = false)
{
	string pass = "";
	//printf("%s", pass);
	srand(passLenght);
	char c = ' ';
	if (!genNum)
		for (uli i = 0; i < passLenght - 1; i++)
		{
			p[i] = (rand() % 25 + 65);
		}
	else
		for (uli i = 0; i < passLenght - 1; i++)
		{
			p[i] = (rand() % 10 + 48);
		}
	p[passLenght - 1] = '\0';
}

uli genPassInt(uli passLenght)
{
	srand(passLenght);
	return rand();
}

void genPassList(uli pass_lenght, bool to_mem)
{
	//char* pass = new char[pass_lenght];
	if (to_mem)
		for (uli i = 0; i < num_of_signs(pass_lenght); i++)
		{
			passList[i] = i;
		}
	else
	{
		ofstream fout;
		fout.open("passlist.txt");
		for (uli i = 0; i < num_of_signs(pass_lenght); i++)
		{
			fout << i << endl;
		}
		fout.close();	
	}

}

void loadPassList(uli size)
{	
	ifstream fin;
	fin.open("passlist.txt");

	for (uli i = 0; i < size; i++)
	{
		fin >> passList[i];
	}

	fin.close();
}

void makeBrute(uli thr_id, uli lenght, uli true_pass)
{
	for (int i = (thr_id * lenght); i < (thr_id + 1) * lenght; i++)
	{
		if (solved)
			break;
		if (passList[i] == true_pass)
		{
			finish_time = clock();
			finish_time = finish_time - start_time;
			solved = true;
			printf("True pass: %i\nTime: %i msec\n", passList[i], finish_time);
			break;
		}
	}
}

void startBrute(int p_lenght, int t_num, char* pass)
{
	vector<thread> threads;

	printf("Brute began (%i threads)\n", t_num);
	start_time = clock();

	uli size_of_part = num_of_signs(p_lenght) / t_num;

	for (uli i = 0; i < t_num; i++)
	{
		threads.push_back(std::thread(makeBrute, i, size_of_part, std::stoi(pass)));
	}

	for (uli i = 0; i < t_num; i++)
	{
		threads[i].join();
	}

	solved = false;
}

void initPassList(uli p_lenght, char* pass, uli t_num, bool to_memory = true)
{
	passList = new uli[num_of_signs(p_lenght)];

	genPass(p_lenght, pass, true);
	printf("Original pass: %i\n", std::stoi(pass));

	printf("Generating a pass list...\n");
	genPassList(p_lenght, to_memory);
	printf("Generation completed\n");

	if (!to_memory)
	{
		printf("Loading a pass list...\n", t_num);
		loadPassList(num_of_signs(p_lenght));
		printf("Load completed\n");
	}
}

uli main()
{
	uli p_lenght = 0;
	cin >> p_lenght;
	p_lenght++;
	uli t_num = 0;
	cin >> t_num;
	char* pass;
	pass = new char[p_lenght];
	
	initPassList(p_lenght, pass, t_num);

	//startBrute(p_lenght, 1, pass);
	startBrute(p_lenght, t_num, pass);

	system("pause");
	return 0;
}
