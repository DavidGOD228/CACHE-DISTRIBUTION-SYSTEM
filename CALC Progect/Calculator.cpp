#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <stdlib.h>

using namespace std;

int calculator(string algebr);
bool check_hight_pr(vector<char> a);

ostream& operator<<(ostream& cout, vector<int>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << "\n";
	return cout;
}

int main()
{
	string a;
	/*getline(cin, a);*/
	cout << calculator("78/6*3-6*5+2/6*2-6/3*2") << endl;
	_getch();
}


int calculator(string algebr)
{
	vector<int> numbers;
	vector<char> symbols;
	int L_solution = 0;
	int H_solution = 0;

	for (int i = 0; i <= algebr.size(); i++)
	{
		string temp_number;
		if (algebr[i] == ' ')
		{
			continue;
		}
		for (i; algebr[i] >= 48 && algebr[i] <= 57; i++)
		{
			temp_number += algebr[i];
		}
		if (temp_number != "")
		{
			numbers.push_back(stoi(temp_number));
		}
		if (algebr[i] != ' ' && (algebr[i] == '+' || algebr[i] == '-' || algebr[i] == '*' || algebr[i] == '/' || algebr[i] == '(' || algebr[i] == ')'))
		{
			symbols.push_back(algebr[i]);
		}
	}

	for (int i = 0; i < symbols.size(); i++)
	{
		switch (symbols[i])
		{
		case '*':
			numbers[i] *= numbers[i + 1];
			numbers[i + 1] = numbers[i];
			H_solution = numbers[i + 1];
			break;
		case '/':
			try
			{
				if (numbers[i + 1] == NULL)
				{
					throw numbers[i + 1];
				}
				else
				{
					numbers[i] /= numbers[i + 1];
					numbers[i + 1] = numbers[i];
					H_solution = numbers[i + 1];
				}
			}
			catch (const int ERROR)
			{
				switch (ERROR)
				{
				case 0:
					cout << "You can't division by zero!!!" << endl;
					return NULL;
					break;

				default:
					break;
				}
			}

			break;

		}
	}

	// CORRECTING

	 // 78/6*3-6*5+2/6*2-6/3*2
	for (int i = symbols.size() - 1; i >= 0; i--)
	{
		if (symbols[i] == '*' || symbols[i] == '/')
		{
			numbers[i] = numbers[i + 1];
			H_solution = numbers[i];
		}
	}

	// CORRECTING

	bool check = false;

	for (int i = 0; i < symbols.size(); i++)
	{
		switch (symbols[i])
		{
		case '-':
			numbers[i] -= numbers[i + 1];
			numbers[i + 1] = numbers[i];
			L_solution = numbers[i + 1];
			check = true;
			break;
		case '+':
			numbers[i] += numbers[i + 1];
			numbers[i + 1] = numbers[i];
			L_solution = numbers[i + 1];
			check = true;
			break;

		}
	}

	for (int i = 0; i < symbols.size(); i++)
	{
		switch (symbols[i])
		{
		case '-':
			numbers[i] -= numbers[i + 1];
			numbers[i + 1] = numbers[i];
			L_solution = numbers[i + 1];
			check = true;
			break;
		case '+':
			numbers[i] += numbers[i + 1];
			numbers[i + 1] = numbers[i];
			L_solution = numbers[i + 1];
			check = true;
			break;

		}
	}

	if (check)
	{
		return L_solution;
	}
	else
	{
		return H_solution;
	}
}

bool check_hight_pr(vector<char> a)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] == '*' || a[i] == '/')
		{
			return true;
		}
	}
	return false;
}
