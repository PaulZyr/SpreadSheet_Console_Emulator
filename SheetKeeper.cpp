#include "SheetKeeper.h"

string SheetKeeperOpen::Open(string path)
{
	bool b = false;
	_sheet->Clear();
	_sheet->SetPath(path);
	ifstream fin;
	fin.open(path, ios_base::out);
	if (fin.is_open())
	{
		b = true;
		Cell* tmp;
		int size_row = 0, size_col = 0;
		int row = -1, col = -1;
		string str;
		getline(fin, str);
		if (str == "<beginning>")
		{
			getline(fin, str);
			stringstream ss(str);
			ss >> size_row >> size_col;

			for (int i = 0; i < size_row; ++i)
			{
				for (int j = 0; j < size_col; ++j)
				{
					getline(fin, str);
					if (str != "<end>")
					{
						tmp = new Cell;
						tmp->ReadFromString(str);
						_sheet->SetCell(tmp, false);
						tmp = NULL;
					}
					else break;
				}
			}
		}
		getline(fin, str);
		if (str == "<end>") b = true;
		_sheet->CountSheet();
		fin.close();
	}
	else return "No such file!";
	return "done";
}

string SheetKeeperSave::Save(string path)
{
	ofstream fout;
	fout.open(path, ios_base::out);
	fout << "<beginning>\n";
	fout << _sheet->GetSizeRow() << " " << _sheet->GetSizeCol() << "\n";
	for (auto row : _sheet->GetSheet())
		for (auto cell : row)
			fout << cell->SaveToString() << "\n";
	fout << "<end>";
	fout.close();
	return "done";
}

string SheetKeeperPrint::Print()
{
	cout << "Path: " << _sheet->GetPath() << "\n";

	int cell_size = _sheet->GetPrintSizeCell();

	int length = (cell_size + 3) * _sheet->GetSizeCol() + 5;
	
	for (int j = 0; j < length; ++j) cout << "-";
	cout << "\n|  ";
	for (int i = 0; i < _sheet->GetSizeCol(); ++i)
	{
		
		cout << " | " << setw(cell_size - 3)
			<< (char)(i + 65) << "   ";
	}
	cout << " |\n";
	for (int j = 0; j < length; ++j) cout << "-";
	cout << "\n";

	for (int i = 0; i < _sheet->GetSizeRow(); ++i)
	{
		cout << "| " << i + 1;

		for (int j = 0; j < _sheet->GetSizeCol(); ++j)
		{
			int is_str = 0;
			if (_sheet->GetCell(i, j)->GetType() == _string) is_str = 1;
			cout << " | " << setw(cell_size)
				<< _sheet->GetCell(i, j)->GetData().substr(is_str, cell_size);
		}
			
		cout << " |\n";
		for (int j = 0; j < length; ++j) cout << "-";
		cout << "\n";
	}
	cout << "\n";
	return "done";
}

string SheetKeeperPrintCell::PrintCell()
{
	int col = GetCellColumn(_sheet->GetSizeCol()).GetInput();
	int row = GetCellRow(_sheet->GetSizeRow()).GetInput();

	return _sheet->GetSheet()[row][col]->PrintCell();
}

string SheetKeeperClear::ClearSheet()
{
	_sheet->Clear();
	return "done";
}

string SheetKeeperSetNewCell::SetNewCell()
{
	Cell* cell = CellCreator(_sheet->GetSizeRow(),
		_sheet->GetSizeCol()).Create();
	if (cell == NULL) return "Cell wasn't created/changed";
	Cell* old_cell = _sheet->GetCell(cell->GetRow(), cell->GetColumn());
	if (_sheet->SetCell(cell))
	{
		_sheet->SetUndo(old_cell);
		return "done";
	}
	else return "Wrong input";
}

string SheetKeeperUndo::Undo()
{
	Cell* cell = _sheet->GetUndo();
	if (cell == NULL) return "Nothing UNDO!";
	Cell* tmp = _sheet->GetCell(cell->GetRow(), cell->GetColumn());
	if (_sheet->SetCell(cell))
	{
		_sheet->SetRedo(tmp);
		return "done";
	}
	else return "Can't Undo!";
}

string SheetKeeperRedo::Redo()
{
	Cell* cell = _sheet->GetRedo();
	if (cell == NULL) return "Nothing REDO!";
	Cell* tmp = _sheet->GetCell(cell->GetRow(), cell->GetColumn());
	if (_sheet->SetCell(cell))
	{
		_sheet->SetUndo(tmp);
		return "done";
	}
	else return "Can't Redo!";
}

string SheetKeeperSetPrintSizeCell::SetPrintSizeCell(int n)
{
	_sheet->SetPrintSizeCell(n);
	return "done";
}

string SheetKeeperSetPrecision::SetPrecision(int n)
{
	_sheet->SetPrecision(n);
	return "done";
}

string SheetKeeperAddColumn::AddColumn()
{
	_sheet->AddColumn();
	return "done";
}

string SheetKeeperAddRow::AddRow()
{
	_sheet->AddRow();
	return "done";
}


