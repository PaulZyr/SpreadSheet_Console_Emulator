#ifndef _INVOKER_H_
#define _INVOKER_H_

#include "Sheet.h"
#include "Command.h"
#include "Waiter.h"

using namespace std;
class Invoker
{
private:
	Sheet* _sheet;
	// Администратор получает заказ от официанта(Waiter)
	// Отправляет посыльного(Command)
public:
	Invoker()
	{
		_sheet = new Sheet;
	}
	~Invoker()
	{
		delete _sheet;
	}
	void Start()
	{
		Waiter* waiter = new Waiter();
		Command* print = new CommandPrintSheet(_sheet);
		Command* command;
		string _msg = "";
		int q = -1;
		while (q != 0)
		{
			command = NULL;
			system("CLS");
			print->Execute();
			q = waiter->Wait(_msg);
			switch (q)
			{
			case 1:
				command = new CommandSetNewCell(_sheet);
				break;
			case 2:
				command = new CommandUndo(_sheet);
				break;
			case 3:
				command = new CommandRedo(_sheet);
				break;
			case 4:
				command = new CommandOpenFile(_sheet);
				break;
			case 5:
				command = new CommandSaveToFile(_sheet);
				break;
			case 6:
				command = new CommandAddColumn(_sheet);
				break;
			case 7:
				command = new CommandAddRow(_sheet);
				break;
			case 8:
				command = new CommandPrintCell(_sheet);
				break;
			case 9:
				command = new CommandSetPrintSizeCell(_sheet);
				break;
			case 10:
				command = new CommandSetPrecision(_sheet);
				break;
			case 0: break;
			}
			if(command != NULL) _msg = command->Execute();
			command = NULL;
		}
		
		
	}
};

#endif // !_INVOKER_H_
