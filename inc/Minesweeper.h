#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <BoardGame.h>
#include <Cell.h>
class Minesweeper: public BoardGame {
	Minesweeper(); // private constructor, it can not be called
public:
	std::vector <std::vector<Cell>> board;
	int winState;
	int bombCount;
	int row;
	int col;
	int winCount;

	Minesweeper(int, int, int);	
	void addBombs(int, int);
	void addCount(int, int);

	void reveal(int, int);
	void roundHouseClick(int,int);

	void reset();

	void handle(int, int, MouseButton=left);

	ucm::json getBoard();

	~Minesweeper();
};


#endif
