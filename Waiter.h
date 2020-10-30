#ifndef _WAITER_H_
#define _WAITER_H_

#include <iostream>
#include <string>
using namespace std;

class Waiter
{
	/*
	* Официант - Принять заказ от юзера, и отправить админу(Invoker) на исполнение
	*/
public:
	int Wait(string msg = "")
	{
		int q = -1;
		int res = -1;
		while (q != 0)
		{
			cout << "1 - Set/Change\n"
				<< "2 - Undo\n"
				<< "3 - Redo\n"
				<< "4 - Open\n"
				<< "5 - Save\n"
				<< "6 - Add Column\n"
				<< "7 - Add Row\n"
				<< "8 - Show Cell' Formula and Data\n"
				<< "9 - Set Cell Print Size\n"
				<< "10 - Set Precision for printing FLOAT (1 through 6)\n"
				<< "0 - Exit\n";
			if (msg != "") cout << "Message: " << msg << endl;
			string str;
			cout << "Input: ";
			getline(cin, str);
			try
			{
				q = stoi(str);
			}
			catch (...)
			{
				msg = "Wrong input!\n";
			}
			switch (q)
			{
			case 1: res = 1; break;
			case 2: res = 2; break;
			case 3: res = 3; break;
			case 4: res = 4; break;
			case 5: res = 5; break;
			case 6: res = 6; break;
			case 7: res = 7; break;
			case 8: res = 8; break;
			case 9: res = 9; break;
			case 10: res = 10; break;
			case 0: res = 0; break;
			default: msg = "Wrong input! Try better!\n";
			}
			if (res != -1) return res;
		}
		return q;
	}
};

#endif // !_WAITER_H_






