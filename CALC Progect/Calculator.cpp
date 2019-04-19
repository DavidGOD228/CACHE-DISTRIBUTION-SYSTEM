#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <stdlib.h>

using namespace std;

double calculator(string algebr);

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
	getline(cin, a);
	system("cls");
	cout << a << " = " << calculator(a) << endl;
	_getch();

	//string a;
	//system("cls");
	//cout << a << " = " << calculator("(12 + 2 * 2) + 3 * 2 + 2") << endl;
	//_getch();
}


double calculator(string algebr)
{
	vector<double> numbers; 
	vector<char> symbols;
	vector<double> splited_numbers;
	vector<char> splited_symbols;
	
	double L_solution = 0;
	double H_solution = 0;

	bool error_scobe = false;
	int col_scob = 0;

	for (int i = 0; i <= algebr.size(); i++)
	{
		string temp_number;
		if (algebr[i] == ' ')
		{
			continue;
		}
		for (i; algebr[i] >= 48 && algebr[i] <= 57 || algebr[i] == 46; i++)
		{
			temp_number += algebr[i];
		}
		if (algebr[i] == '(')
		{
			error_scobe = true;
			col_scob++;
		}
		else if (algebr[i] == ')')
		{
			if (error_scobe)
			{
				error_scobe = false;
			}
			else
			{
				error_scobe = true;
			}
			col_scob++;
		}
		if (temp_number != "")
		{
			numbers.push_back(stod(temp_number));
		}
		if (algebr[i] != ' ' && (algebr[i] == '+' || algebr[i] == '-' || algebr[i] == '*' || algebr[i] == '/' || algebr[i] == '(' || algebr[i] == ')'))
		{
			symbols.push_back(algebr[i]);
		}
		else if (algebr[i] == '=')
		{
			cout << "ERROR" << endl;
			return 0;
		}
	}

	// CHECK
	int difference = symbols.size() - col_scob;
	int size = numbers.size();

	if (error_scobe)
	{
		cout << "ERROR" << endl;
		return 0;
	}
	if (col_scob % 2 != 0)
	{
		cout << "ERROR" << endl;
		return 0;
	}
	if(difference >= size)
	{
		cout << "ERROR" << endl;
		return 0;
	}
	else if (numbers.size() == 1)
	{
		return numbers[0];
	}
	// CHECK


	// DYGKI
	int place_st = 0;
	int place_end = 0;
	double temp_number;
	if (col_scob != 0)
	{
		for (int i = 0; i < algebr.size(); i++)
		{
			if (algebr[i] == '(')
			{
				place_st = i;
				string temp = " ";
				i++;
				for (i; algebr[i] != ')'; i++)
				{
					temp += algebr[i];
				}
					temp_number = calculator(temp);
				for ( i = place_st; symbols[i]!=')'; i++)
				{
					numbers.erase(numbers.begin() + i);
				}
				place_end = i;
				numbers.insert(numbers.begin() + place_st, temp_number);
			}
		}
	}

	for (int i = 0; i < symbols.size(); i++)
	{
		if (symbols[i] == '(')
		{
				for (; symbols[i] != ')';)
				{
					symbols.erase(symbols.begin() + i);
				}
				symbols.erase(symbols.begin() + i);
		}
	}

	// DYGKI



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

	for (int i = symbols.size() - 1; i >= 0; i--)
	{
		if (symbols[i] == '*' || symbols[i] == '/')
		{
			numbers[i] = numbers[i + 1];
			H_solution = numbers[i];
		}

	}

	// CORRECTING


	// SPLITTING TO LOW PRIORITTY
	bool next = true;

	if (symbols.size() > 1)
	{
		for (int i = 0; i < symbols.size(); i++)
		{
			if (symbols[i] == '+' || symbols[i] == '-')
			{
				if (next)
				{
					splited_numbers.push_back(numbers[i]);
					next = false;
				}
				splited_numbers.push_back(numbers[i + 1]);
		
				splited_symbols.push_back(symbols[i]);
			}

		}
	}

	else
	{
				splited_numbers.push_back(numbers[0]);
				splited_numbers.push_back(numbers[1]);
				splited_symbols.push_back(symbols[0]);

	}

	numbers.clear();
	symbols.clear();

	// SPLITTING TO LOW PRIORITTY

	bool check = false;

	for (int i = 0; i < splited_symbols.size(); i++)
	{
		switch (splited_symbols[i])
		{
		case '-':
			splited_numbers[i] -= splited_numbers[i + 1];
			splited_numbers[i + 1] = splited_numbers[i];
			L_solution = splited_numbers[i + 1];
			check = true;
			break;
		case '+':
			splited_numbers[i] += splited_numbers[i + 1];
			splited_numbers[i + 1] = splited_numbers[i];
			L_solution = splited_numbers[i + 1];
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