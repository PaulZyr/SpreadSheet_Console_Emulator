#ifndef _SHEET_KEEPER_
#define _SHEET_KEEPER_

#include "Sheet.h"
#include "CellCreator.h"
#include "InputGetter.h"

class SheetKeeper
{
	// Кладовщик - Работает со складом.
	// Обрабатывает запрос, выполняет, отсылает отчет
protected:
	Sheet* _sheet;
public:
	SheetKeeper(Sheet* sheet) { _sheet = sheet; }
	virtual string Open(string path = "sheet.sht") { return ""; }
	virtual string Save(string path = "sheet.sht") { return ""; }
	virtual string Print() { return ""; }
	virtual string PrintCell() { return ""; }
	virtual string Clear() { return ""; }
	virtual string SetNewCell() { return ""; }
	virtual string Undo() { return ""; }
	virtual string Redo() { return ""; }
	virtual string SetPrintSizeCell(int n) { return ""; }
	virtual string SetPrecision(int n) { return ""; }
	virtual string AddColumn() { return ""; }
	virtual string AddRow() { return ""; }
};

class SheetKeeperOpen : public SheetKeeper
{
public:
	SheetKeeperOpen(Sheet* sheet)
		: SheetKeeper(sheet)
	{}
	string Open(string path);
};

class SheetKeeperSave : public SheetKeeper
{
public:
	SheetKeeperSave(Sheet* sheet)
		: SheetKeeper(sheet) 
	{}
	string Save(string path);
};

class SheetKeeperPrint : public SheetKeeper
{
public:
	SheetKeeperPrint(Sheet* sheet)
		: SheetKeeper(sheet)
	{}
	string Print();
};

class SheetKeeperPrintCell : public SheetKeeper
{
public:
	SheetKeeperPrintCell(Sheet* sheet)
		: SheetKeeper(sheet)
	{}
	string PrintCell();
};

class SheetKeeperClear : public SheetKeeper
{
public:
	SheetKeeperClear(Sheet* sheet)
		: SheetKeeper(sheet)
	{}
	string ClearSheet();
};

class SheetKeeperSetNewCell : public SheetKeeper
{
public:
	SheetKeeperSetNewCell(Sheet* sheet)
		: SheetKeeper(sheet)
	{}
	string SetNewCell();
};

class SheetKeeperUndo : public SheetKeeper
{
public:
	SheetKeeperUndo(Sheet* sheet)
		: SheetKeeper(sheet)
	{}
	string Undo();
};
class SheetKeeperRedo : public SheetKeeper
{
public:
	SheetKeeperRedo(Sheet* sheet)
		: SheetKeeper(sheet)
	{}
	string Redo();
};

class SheetKeeperSetPrintSizeCell : public SheetKeeper
{
public:
	SheetKeeperSetPrintSizeCell(Sheet* sheet)
		: SheetKeeper(sheet)
	{}
	string SetPrintSizeCell(int n);
};

class SheetKeeperSetPrecision : public SheetKeeper
{
public:
	SheetKeeperSetPrecision(Sheet* sheet)
		: SheetKeeper(sheet)
	{}
	string SetPrecision(int n);
};

class SheetKeeperAddColumn : public SheetKeeper
{
public:
	SheetKeeperAddColumn(Sheet* sheet)
		: SheetKeeper(sheet)
	{}
	string AddColumn();
};

class SheetKeeperAddRow : public SheetKeeper
{
public:
	SheetKeeperAddRow(Sheet* sheet)
		: SheetKeeper(sheet)
	{}
	string AddRow();
};

#endif // !_SHEET_KEEPER_