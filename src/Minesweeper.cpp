#include <Minesweeper.h>
#include <random>

Minesweeper::Minesweeper(int rows, int cols, int bombs){
	std::cout << "Making a game of " << rows << " x " << cols << " with " << bombs << " bombs" << std::endl;
	//Gen empty Board
	std::vector<Cell> temp;
	for(int i =0; i < rows; i++){
		for(int j=0; j<cols; j++)
			temp.push_back(Cell()); //empty cell
	board.push_back(temp);//empty row
	temp.clear();
	}
	row = rows;
	col = cols;
	bombCount = bombs;//bombs;
	winState = 0;// 0 is none; 1 is lost; 2 is won
	winCount = ((row) * (col) ) - bombCount;
}	

void Minesweeper::addBombs(int rows, int cols){
	//Fill with bombs
	int i = bombCount;
	while(i != 0){
		auto xRand = rand() % rows;
		auto yRand = rand() % cols;
		
		if(board[xRand][yRand].checkBomb() == false){//place bomb
			board[xRand][yRand].addBomb();//spot = bomb
			std::cout <<"Bomb #"<<i<<" x:"<< yRand <<" y:"<< xRand <<" , ";
			i--;
		}
		else
		{
			//std::cout<< "Bomb Already There; New Num: ";
		}
	}
	std::cout<<" "<<std::endl;
}

void Minesweeper::addCount(int x, int y){
 //Check around bomb
for(int i = x-1; i < x+2; i++)
	for(int j = y-1; j < y+2; j++)
		if(i >= 0 && i < row && j >= 0 && j <col)
			if(board[i][j].checkBomb() == true)//Found bomb in adj or on itself
				board[x][y].addCount();
}

void Minesweeper::reset(){
	std::cout << "Reseting the game" << std::endl;
	// if(board.empty() == true)
	// 	return;//if empty, then finished
	
	//reset every cell to blank
	for(int i =0; i < board.size(); i++)
		for(int j=0; j< board[i].size(); j++)
			board[i][j].reset();

	addBombs(row,col);//place Bombs onto Board

	//Detect if bombs next to the cell
	for(int i =0; i < board.size(); i++)
		for(int j=0; j<board[i].size(); j++)
			addCount(i,j);

	winState = 0;
	winCount = ((row) * (col) ) - bombCount;
}

void Minesweeper::handle(int x, int y, MouseButton button){
	std::string btn;
	//if cell is shown, flagged , or state is != 0; return
	if(winState != 0)//if won or loss, dont do anything
		return;
	//mod spot
	 if (button == right && board[x][y].hidden == true){
		std::cout<<"Right: Flag"<<std::endl;
		btn = "right";
		board[x][y].flagToggle();
	}
	else if(button == left && board[x][y].checkCount() > 0 && board[x][y].hidden == false){
		btn = "left";
		std::cout<<"Left: Reveal Adj"<<std::endl;
		roundHouseClick(x,y);
	}
	else if(board[x][y].flagged == true || winState != 0 ||board[x][y].hidden == false){
		std::cout<<"No change"<<std::endl;
	}
	else if (button == left){
		std::cout<<"Left: Reveal This: ";
		btn = "left";
		board[x][y].hideToggle();
		winCount--;
		if(board[x][y].checkBomb() == true){//if bomb
			std::cout<<" A bomb"<<std::endl;
			winState = 2;}//lose
		else if(board[x][y].checkCount() == 0){
			std::cout<<" WhiteSpace"<<std::endl;
			winCount++;
			reveal(x,y);//reveal surrounding empty
		}
	}
	else
		btn = "unknown";	
	std::cout << "Handling a " << btn << " click on " << y << ", " << x << std::endl;
}

void Minesweeper::roundHouseClick(int x, int y){
			int flagCount = 0;//count flags around self
			//Detect if flag next to the cell
			for(int i = x-1; i < x+2; i++)
				for(int j = y-1; j < y+2; j++)
					if(i >= 0 && i < row && j >= 0 && j <col && board[i][j].flagged == true)
						flagCount++;
			//If there is the correct num of flags around, reveal round
			if(flagCount == board[x][y].checkCount()){
				std::cout<<"Revealing Around x:"<<x<<" y:"<<y<<std::endl;
				for(int i = x-1; i < x+2; i++)
					for(int j = y-1; j < y+2; j++)
						if(i >= 0 && i < row && j >= 0 && j <col)
							if(board[i][j].flagged != true && board[i][j].hidden == true)
								reveal(i,j);
			}
			else{
				std::cout<<"Wrong # of Flags: "<<flagCount<<" Needs:"<<board[x][y].checkCount()<<std::endl;
			}
}

void Minesweeper::reveal(int x, int y){
	if(board[x][y].flagged == true)
		return;
	board[x][y].hideToggle();
	winCount--;
	 if(board[x][y].checkBomb() == true)
		winState = 2;
	 if(board[x][y].checkCount() != 0)
	 	return;
	if(x+1>= 0 && x+1 < row && y >= 0 && y <col)
		if(board[x+1][y].hidden == true)
			reveal(x+1,y);
	if(x>= 0 && x < row && y+1 >= 0 && y+1 <col)
		if(board[x][y+1].hidden == true)
			reveal(x,y+1);
	if(x-1>= 0 && x-1 < row && y >= 0 && y <col)
		if(board[x-1][y].hidden == true)
			reveal(x-1,y);
	if(x>= 0 && x < row && y-1 >= 0 && y-1 <col)
		if(board[x][y-1].hidden == true)
		reveal(x,y-1);
	if(x-1>= 0 && x-1 < row && y-1 >= 0 && y-1 <col)
		if(board[x-1][y].hidden == true)
			reveal(x-1,y-1);
	if(x+1>= 0 && x+1 < row && y+1 >= 0 && y+1 <col)
		if(board[x+1][y+1].hidden == true)
			reveal(x+1,y+1);
	if(x-1>= 0 && x-1 < row && y+1 >= 0 && y+1 <col)
		if(board[x-1][y+1].hidden == true)
			reveal(x-1,y+1);
	if(x+1>= 0 && x+1 < row && y-1 >= 0 && y-1 <col)
		if(board[x+1][y-1].hidden == true)
			reveal(x+1,y-1);
	
	/*for(int i = x-1; i < x+2; i++)
		for(int j = y-1; j < y+2; j++)
			if(i >= 0 && i < row && j >= 0 && j <col){
				board[i][j].hideToggle();
				//reveal(i,j);
				std::cout <<"Revealing: x:"<<i<<" y:"<<j<< std::endl;
				}*/
}

ucm::json Minesweeper::getBoard(){
	ucm::json tempBoard;
	ucm::json temp;

	if(winCount == 0 && winState == 0)
		winState = 1;


	for(int i=0; i<board.size(); i++){
		for(int j=0; j<board[i].size(); j++){
			//std::cout <<"at: x:"<< i <<" y: "<< j << " Board"<< board[i][j].show();
			if(winState != 0){//If win or Loss, reveal whole board
				if(board[i][j].flagged = true)
					board[i][j].flagToggle();
				board[i][j].hideToggle();
			}
			ucm::json temp2 = board[i][j].show();
			temp.push_back(board[i][j].show());
			
		}
	tempBoard.push_back(temp);//store into result
	temp.clear();
	}

	ucm::json Board;
	Board["board"] = tempBoard;
	Board["win"] = std::to_string(winState);
	std::cout<<" Tiles left to Reveal: " << winCount<<std::endl;
	return Board;
}

Minesweeper::~Minesweeper(){

}
