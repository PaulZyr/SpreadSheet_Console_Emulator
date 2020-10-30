#include "Cell.h"

Cell::Cell() :_cell_type(_empty), _cell_row(-1),
_cell_column(-1), _data(""),
_influenced(false), _influenced_data("")
{}

Cell::Cell(int cell_row, int cell_column)
{
	_cell_type = _empty;
	_cell_row = cell_row;
	_cell_column = cell_column;
	_data = "";
	_influenced = false;
	_influenced_data = "";
}
Cell::Cell(CellType cell_type, int cell_row,
	int cell_column, string data,
	bool influenced, string influenced_data)
{
	_cell_type = cell_type;
	_cell_row = cell_row;
	_cell_column = cell_column;
	_data = data;
	_influenced = influenced;
	_influenced_data = influenced_data;
}
void Cell::SetType(const CellType cell_type) { _cell_type = cell_type; }
void Cell::SetRow(const int row) { _cell_row = row; }
void Cell::SetColumn(const char col) { _cell_column = col; }
void Cell::SetData(const string data) { _data = data; }
void Cell::SetInfluenced(bool b) { _influenced = b; }
void Cell::SetInfluencedData(string str) { _influenced_data = str; }

CellType Cell::GetType() { return _cell_type; }
string Cell::GetTypeAsString()
{
	switch (_cell_type)
	{
	case CellType::_int: return "int";
	case CellType::_float: return "float";
	case CellType::_string: return "string";
	case CellType::_empty: return "empty";
	case CellType::_wrong: return "wrong";
	}
	return "unknown";
}
int Cell::GetRow() { return _cell_row; }
int Cell::GetColumn() { return _cell_column; }
char Cell::GetColumnAsChar() {
	return static_cast<char>(_cell_column + 65);
}
string Cell::GetData() { return _data; }
bool Cell::GetInfluenced() { return _influenced; }
string Cell::GetInfluencedData() { return _influenced_data; }

string Cell::SaveToString()
{
	stringstream sout;
	sout << _influenced << " ";
	if (_influenced)
		sout << _influenced_data << " ";
	sout << _cell_type << " " << _cell_row
		<< " " << _cell_column << " " << _data;
	return sout.str();
}
void Cell::ReadFromString(string str)
{
	int type;
	int infl;
	stringstream sin;
	sin.str(str);
	sin >> infl;
	if (infl == 1)
	{
		_influenced = true;
		sin >> _influenced_data;
	}

	sin >> type >> _cell_row >> _cell_column;
	sin.ignore(1, ' ');
	getline(sin, _data);
	_cell_type = static_cast<CellType>(type);
}

string Cell::PrintCell()
{
	stringstream ss;
	ss << GetColumnAsChar() << _cell_row + 1 << ", Type = " << GetTypeAsString()
		<< ", data = " << _data;
	if (_influenced) ss << ", Formula: " << _influenced_data;
	return ss.str();
}