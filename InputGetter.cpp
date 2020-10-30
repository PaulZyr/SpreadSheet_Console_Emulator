#include "InputGetter.h"

int GetPrintCellSize::GetInput()
{
	int n = 0;
	string str = "";
	cout << "Input new print cell size: ";
	getline(cin, str);
	try
	{
		n = stoi(str);
	}
	catch (...)
	{
		return -1;
	}
	if (n > 5 && n <= 20) return n;
	else if (n < 6) return -2;
	else return -3;
}

int GetPrecision::GetInput()
{
	int n = 0;
	string str = "";
	cout << "Input new print Precision: ";
	getline(cin, str);
	try
	{
		n = stoi(str);
	}
	catch (...)
	{
		return -1;
	}
	if (n > 0 && n <= 6) return n;
	else if (n <= 0) return -2;
	else return -3;
}

GetCellRow::GetCellRow() { _max_row = 0; }
GetCellRow::GetCellRow(int n) { _max_row = n; }
int GetCellRow::GetInput()
{
	string str;
	while (true)
	{
		cout << "Input Cell Row (type exit to return): ";
		getline(cin, str);
		if (str == "exit") return -2;
		int _row = -1;
		try
		{
			_row = stoi(str) - 1;
		}
		catch (...) {
			cout << "Wrong Input!\n";
		}
		if (_row >= 0 && _row < _max_row) return _row;
	}
}

GetCellColumn::GetCellColumn() { _max_col = 0; }
GetCellColumn::GetCellColumn(int n) { _max_col = n; }
int GetCellColumn::GetInput()
{
	while (true)
	{
		cout << "Input Cell Column (type exit to return): ";
		string str;
		getline(cin, str);
		if (str == "exit") return -2;
		int _col = -1;

		if (str[0] >= 'A' && str[0] <= 'Z')
		{
			_col = str[0] - 65;
		}
		else if (str[0] >= 'a' && str[0] <= 'z')
		{
			_col = str[0] - 97;
		}
		else cout << "Wrong Input!\n";

		if (_col >= 0 && _col <= _max_col) return _col;
	}
}

int GetCellData::GetInput()
{
	cout << "Input Cell Data (type exit to return)\n"
		<< "('string, 123, 12.34, =A2+B3*C4):\n";
	getline(cin, _str);
	return 0;
}
string GetCellData::GetStr() { return _str; }