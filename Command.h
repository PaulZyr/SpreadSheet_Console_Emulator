#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "Sheet.h"
#include "SheetKeeper.h"
#include "InputGetter.h"

using namespace std;

class Command
{
	// Посыльный - сообщает кладовщику (SheetKeeper) задание
protected:
	Sheet* _sheet;
public:
	Command()
	{
		_sheet = NULL;
	}
	Command(Sheet* sheet)
	{
		_sheet = sheet;
	}
	virtual string Execute() = 0;
};

class CommandOpenFile : public Command
{
public:
	//CommandOpenFile() {}
	CommandOpenFile(Sheet* sheet)
		: Command(sheet) {}
	string Execute()
	{
		if (_sheet != NULL)
		{
			SheetKeeper* work = new SheetKeeperOpen(_sheet);
			return work->Open();
		}
		else return "No sheet!";
		/*if (!_sheet->Open()) return "No such file";
		_sheet->CountSheet();*/

		//return "done";
	}
};

class CommandSaveToFile : public Command
{
public:
	//CommandSaveToFile() {}
	CommandSaveToFile(Sheet* sheet)
		: Command(sheet) {}
	string Execute()
	{
		SheetKeeper* work = new SheetKeeperSave(_sheet);
		return work->Save();
	}
};

class CommandPrintSheet : public Command
{
public:
	//CommandPrintSheet() {}
	CommandPrintSheet(Sheet* sheet) : Command(sheet) {}
	string Execute()
	{
		SheetKeeper* work = new SheetKeeperPrint(_sheet);
		return work->Print();
	}
};

class CommandPrintCell : public Command
{
public:
	//CommandPrintCell() {}
	CommandPrintCell(Sheet* sheet) : Command(sheet) {}
	string Execute()
	{
		SheetKeeper* work = new SheetKeeperPrintCell(_sheet);
		return work->PrintCell();
	}
};

class CommandSheetClear : public Command
{
public:
	//CommandSheetClear() {}
	CommandSheetClear(Sheet* sheet) : Command(sheet) {}
	string Execute()
	{
		SheetKeeper* work = new SheetKeeperClear(_sheet);
		return work->Clear();
	}
};

class CommandSetNewCell : public Command
{
public:
	//CommandSetNewCell()	{}
	CommandSetNewCell(Sheet* sheet) : Command(sheet) {}
	string Execute()
	{
		SheetKeeper* work = new SheetKeeperSetNewCell(_sheet);
		return work->SetNewCell();
	}
};

class CommandUndo : public Command
{
public:
	//CommandSetNewCell()	{}
	CommandUndo(Sheet* sheet) : Command(sheet) {}
	string Execute()
	{
		SheetKeeper* work = new SheetKeeperUndo(_sheet);
		return work->Undo();
	}
};

class CommandRedo : public Command
{
public:
	//CommandSetNewCell()	{}
	CommandRedo(Sheet* sheet) : Command(sheet) {}
	string Execute()
	{
		SheetKeeper* work = new SheetKeeperRedo(_sheet);
		return work->Redo();
	}
};

class CommandSetPrintSizeCell : public Command
{
public:
	//CommandSetNewCell()	{}
	CommandSetPrintSizeCell(Sheet* sheet) : Command(sheet) {}
	string Execute()
	{
		InputGetter* get = new GetPrintCellSize;
		int n = get->GetInput();
		switch (n)
		{
		case -1:
			return "Wrong input!";
		case -2:
			return "Too small number";
		case -3:
			return "Too big number";
		default:
			SheetKeeper* work = new SheetKeeperSetPrintSizeCell(_sheet);
			return work->SetPrintSizeCell(n);
		}
	}
};

class CommandSetPrecision : public Command
{
public:
	//CommandSetNewCell()	{}
	CommandSetPrecision(Sheet* sheet) : Command(sheet) {}
	string Execute()
	{
		InputGetter* get = new GetPrecision;
		int n = get->GetInput();
		switch (n)
		{
		case -1:
			return "Wrong input!";
		case -2:
			return "Too small number";
		case -3:
			return "Too big number";
		default:
			SheetKeeper* work = new SheetKeeperSetPrecision(_sheet);
			return work->SetPrecision(n);
		}
	}
};

class CommandAddColumn : public Command
{
public:
	CommandAddColumn(Sheet* sheet) : Command(sheet) {}
	string Execute()
	{
		SheetKeeper* work = new SheetKeeperAddColumn(_sheet);
		return work->AddColumn();
	}
};

class CommandAddRow : public Command
{
public:
	CommandAddRow(Sheet* sheet) : Command(sheet) {}
	string Execute()
	{
		SheetKeeper* work = new SheetKeeperAddRow(_sheet);
		return work->AddRow();
	}
};

#endif // !_COMMAND_H_