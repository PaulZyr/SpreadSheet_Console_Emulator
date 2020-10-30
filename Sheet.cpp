#include "Sheet.h"

Sheet::Sheet(string path, int size_row, int size_col)
{
	_path = path;
	_print_cell_size = 12;
	_size_row = size_row;
	_size_col = size_col;
	_precision = 2;
	FillSheetEmptyCell();
}
Sheet::~Sheet()
{
	if (!_sheet.empty())
	{
		for (int i = 0; i < _size_row; ++i)
		{
			for (int j = 0; j < _size_col; ++j)
			{
				if (_sheet[i][j] != NULL) delete _sheet[i][j];
			}
		}
	}
	if (!_undo.empty())
		for (size_t i = 0; i < _undo.size(); ++i)
			if (_undo.at(i) != NULL) delete _undo[i];
}

void Sheet::SetPath(string str) { _path = str; }
void Sheet::SetSizeRow(int n) { _size_row = n; }
void Sheet::SetSizeCol(int n) { _size_col = n; }
void Sheet::SetPrintSizeCell(int n)
{
	if (n < 5) cout << "Too small size";
	else if (n > 30) cout << "Too big size for cell";
	else _print_cell_size = n;
}
void Sheet::SetPrecision(int n) { _precision = n; }
void Sheet::SetUndo(Cell* cell)
{ 
	if (_undo.size() >= 50) 
		_undo.erase(_undo.begin(), _undo.begin() + 5);
	_undo.push_back(cell); 
}
void Sheet::SetRedo(Cell* cell) 
{ 
	if (_redo.size() >= 50)
		_redo.erase(_redo.begin(), _redo.begin() + 5);
	_redo.push_back(cell);
}

string Sheet::GetPath() { return _path; }
int Sheet::GetSizeRow() { return _size_row; }
int Sheet::GetSizeCol() { return _size_col; }
int Sheet::GetPrintSizeCell() { return _print_cell_size; }
int Sheet::GetPrecision() { return _precision; }
Cell* Sheet::GetCell(int i, int j) { return _sheet[i][j]; }
vector<vector<Cell*>> Sheet::GetSheet() { return _sheet; }

Cell* Sheet::GetUndo()
{
	if (!_undo.empty())
	{
		Cell* cell = _undo.back();
		_undo.pop_back();
		return cell;
	}
	else return NULL;
}
Cell* Sheet::GetRedo()
{
	if (!_redo.empty())
	{
		Cell* cell = _redo.back();
		_redo.pop_back();
		return cell;
	}
	else return NULL;
}

void Sheet::FillSheetEmptyCell()
{
	for (int i = 0; i < _size_row; ++i)
	{
		vector<Cell*> vec_tmp;
		for (int j = 0; j < _size_col; ++j)
		{
			Cell* tmp = new Cell(i, j);
			vec_tmp.push_back(tmp);
			tmp = NULL;
		}
		_sheet.push_back(vec_tmp);
	}
}

bool Sheet::SetCell(Cell* cell, bool b)
{
	if (cell != NULL)
	{
		int col = cell->GetColumn();
		int row = cell->GetRow();
		if (col >= 0 && col < _size_col
			&& row >= 0 && row < _size_row)
		{
			//_undo.push_back(_sheet[row][col]);
			_sheet[row][col] = cell;
			if (b) CountSheet();
			return true;
		}
	}
	return false;
}

void Sheet::CountSheet()
{
	bool changed = true;
	while (changed)
	{
		changed = false;
		for (int i = 0; i < _size_row; ++i)
			for (int j = 0; j < _size_col; ++j)
				if (_sheet[i][j]->GetInfluenced())
					if (CountCell(i, j)) changed = true;
	}
}
bool Sheet::CountCell(int i, int j)
{
	string original = _sheet[i][j]->GetData();
	string str = _sheet[i][j]->GetInfluencedData();
	if (str[0] != '=')
	{
		_sheet[i][j]->SetType(_wrong);
		_sheet[i][j]->SetData("'mistake");
		_sheet[i][j]->SetInfluencedData("");
		return true;
	}
	else
	{
		unsigned index = 1;
		float res = 0;
		char operation = '+';
		while (index < str.size())
		{
			if (str[index] == '+' || str[index] == '-'
				|| str[index] == '*' || str[index] == '/')
			{
				operation = str[index];
				index++;
			}
			if (str[index] >= 'A' && str[index] <= 'Z')
			{
				int col = str[index] - 65;
				index++;

				int row = 0;
				while (str[index] >= 48 && str[index] <= 57)
				{
					row = row * 10 + (str[index] - 49);
					index++;
				}

				float tmp_res = 0;
				switch (operation)
				{
				case '+':
					tmp_res += static_cast<float>(stod(_sheet[row][col]->GetData()));
					res += tmp_res;
					break;
				case '-':
					tmp_res -= static_cast<float>(stod(_sheet[row][col]->GetData()));
					res -= tmp_res;
					break;
				case '*':
					tmp_res = 1;
					tmp_res *= static_cast<float>(stod(_sheet[row][col]->GetData()));
					res *= tmp_res;
					break;
				case '/':
					tmp_res = 1;
					tmp_res /= static_cast<float>(stod(_sheet[row][col]->GetData()));
					res /= tmp_res;
					break;
				}
			}
		}

		if (res - (int)res != 0) _sheet[i][j]->SetType(_float);
		else _sheet[i][j]->SetType(_int);
		stringstream ss;
		ss << fixed << setprecision(_precision) << res;
		if (ss.str() == original) return false;
		else
		{
			_sheet[i][j]->SetData(ss.str());
			return true;
		}
	}
}

void Sheet::AddColumn()
{
	_size_col++;
	for (int i = 0; i < _size_row; ++i)
	{
		Cell* tmp = new Cell(i, _size_col-1);
		_sheet[i].push_back(tmp);
		tmp = NULL;
	}
	
}

void Sheet::AddRow()
{
	_size_row++;
	vector<Cell*> vec_tmp;
	for (int j = 0; j < _size_col; ++j)
	{
		Cell* tmp = new Cell(_size_row - 1, j);
		vec_tmp.push_back(tmp);
		tmp = NULL;
	}
	_sheet.push_back(vec_tmp);
}

void Sheet::Clear()
{
	if (!_sheet.empty())
		for (int i = 0; i < _size_row; ++i)
			for (int j = 0; j < _size_col; ++j)
				if (_sheet[i][j] != NULL) delete _sheet[i][j];
	if (!_undo.empty())
		for (size_t i = 0; i < _undo.size(); ++i)
			if (_undo.at(i) != NULL) delete _undo[i];

	for (int i = 0; i < _size_row; ++i)
		_sheet.clear();

	FillSheetEmptyCell();
}