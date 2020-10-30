#ifndef _CELL_CREATOR_H_
#define _CELL_CREATOR_H_

#include "Cell.h"
#include "InputGetter.h"

class CellCreator
{
	int _max_row;
	int _max_col;
	// Создает новые ящики, получает от юзера данные, кладет в ящик
	// Отдает ящик посыльному
public:
	CellCreator(int max_row, int max_col);
	Cell* Create();
};

#endif // !_CELL_CREATOR_H_