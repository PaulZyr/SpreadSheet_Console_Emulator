#ifndef _SHEET_H_
#define _SHEET_H_

#include <iomanip>
#include "Cell.h"
#include "CellCreator.h"

using namespace std;

class Sheet
{
	// Склад - хранит ящики на трех складах:
	// 1) Главный _sheet
	// 2) Временные _undo и _redo - до 50 ящиков
	// управляют складом кладовщики - каждый знает только свою задачу
	// Логика у складаЖ
	//  1 - пересчитывать ящики,которые ссылаются на других;
	//  2 - увеличивать вместимость склада
private:
	//string _name;
	string _path;
	int _size_row;
	int _size_col;
	int _print_cell_size;
	int _precision;
	vector<vector<Cell*>> _sheet;
	vector<Cell*> _undo;
	vector<Cell*> _redo;
	
	bool CountCell(int i, int j);
public:
	Sheet(string path = "sheet.sht", int size_row = 5, int size_col = 5);
	~Sheet();

	void SetPath(string str);
	void SetSizeRow(int n);
	void SetSizeCol(int n);
	void SetPrintSizeCell(int n);
	void SetPrecision(int n);
	void SetUndo(Cell* cell);
	void SetRedo(Cell* cell);

	string GetPath();
	int GetSizeRow();
	int GetSizeCol();
	int GetPrintSizeCell();
	int GetPrecision();
	Cell* GetCell(int i, int j);
	vector<vector<Cell*>> GetSheet();
	Cell* GetUndo();
	Cell* GetRedo();

	void FillSheetEmptyCell();

	bool SetCell(Cell* cell, bool b = true);

	void AddColumn();
	void AddRow();

	void CountSheet();

	void Clear();

};
#endif // !_SHEET_H_