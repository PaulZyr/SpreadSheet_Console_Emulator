#ifndef _INPUT_GETTER_
#define _INPUT_GETTER_

#include <iostream>
#include <string>
using namespace std;

class InputGetter
{
public:
	virtual int GetInput() = 0;
	virtual string GetStr() { return ""; }
};

class GetPrintCellSize : public InputGetter
{
public:
	int GetInput();
};

class GetPrecision : public InputGetter
{
public:
	int GetInput();
};

class GetCellRow : public InputGetter
{
	int _max_row;
public:
	GetCellRow();
	GetCellRow(int n);
	int GetInput();
};

class GetCellColumn : public InputGetter
{
	int _max_col;
	
public:
	GetCellColumn();
	GetCellColumn(int n);
	int GetInput();
};

class GetCellData : public InputGetter
{
	string _str;
public:
	int GetInput();
	string GetStr();
};

#endif // !_INPUT_GETTER_