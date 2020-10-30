#ifndef _CELL_H_
#define _CELL_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum CellType
{
	_int,
	_float, 
	_string, 
	_empty,
	_wrong
};

class Cell
{
protected:
	CellType _cell_type;
	int _cell_row;
	int _cell_column;
	string _data;
	bool _influenced;
	string _influenced_data;
public:
	Cell();
	Cell(int cell_row, int cell_column);
	Cell(CellType cell_type, int cell_row,
		int cell_column, string data,
		bool influenced = false, string influenced_data = "");
	void SetType(const CellType cell_type);
	void SetRow(const int row);
	void SetColumn(const char col);
	void SetData(const string data);
	void SetInfluenced(bool b);
	void SetInfluencedData(string str);

	CellType GetType();
	string GetTypeAsString();
	int GetRow();
	int GetColumn();
	char GetColumnAsChar();
	string GetData();
	bool GetInfluenced();
	string GetInfluencedData();

	string SaveToString();
	void ReadFromString(string str);
	string PrintCell();
};

#endif // !_CELL_H_