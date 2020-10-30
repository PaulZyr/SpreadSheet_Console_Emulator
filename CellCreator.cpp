#include "CellCreator.h"

CellCreator::CellCreator(int max_row, int max_col)
{
	_max_row = max_row;
	_max_col = max_col;
}

Cell* CellCreator::Create()
{
	InputGetter* getter;

	getter = new GetCellColumn(_max_col);
	int _col = getter->GetInput();
	if (_col == -2) return NULL;

	getter = new GetCellRow(_max_row);
	int _row = getter->GetInput();
	if (_row == -2) return NULL;

	getter = new GetCellData();
	int done = getter->GetInput();
	string str = "";
	if (done == 0)
		str = getter->GetStr();
	if (str == "exit") return NULL;

	if (str == "") return new Cell(_row, _col);

	else
	{
		CellType type;
		if (str[0] >= 48 && str[0] <= 57)
		{
			type = _int;
			for (size_t i = 1; i < str.size(); ++i)
			{
				if (str[i] == '.')
				{
					type = _float;
					break;
				}
			}
		}
		else if (str[0] == '\'') type = _string;
		else if (str[0] == '=')
		{
			type = _int;
			for (auto& c : str) c = toupper(c);
			return new Cell(type, _row, _col, "", true, str);
		}
		else return NULL;

		return new Cell(type, _row, _col, str);
	}
}