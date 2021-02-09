#include <iostream>

using namespace std;

int board[3][3] = {{11,12,13}, {21,22,23}, {31,32,33}};
bool boolBoard[3][3] = {{false,false,false}, {false,false,false}, {false,false,false}};
int row = 3;
int col = 3;

void round(int x, int y){

for(int i = x-1; i < x+2; i++)
	for(int j = y-1; j < y+2; j++)
		if(i >= 0 && i < row && j >= 0 && j < col && boolBoard[i][j] == false){
			cout << board[i][j] << " ";
			boolBoard[i][j] = true;
			round(x+1,y+1);
			}
}

void round2(int x, int y){

for(int i = x-1; i < x+2; i++)
	for(int j = y-1; j < y+2; j++)
		if(i >= 0 && i < row && j >= 0 && j < col && boolBoard[i][j] == false){
			cout << board[i][j] << " ";
			}
}

int main(){
	round2(1,1);
	cout << "Hello World" << endl;
	round(0,0);
	

	return 0;
}
/*
Handle Flags; bug where it can be clicked and can be revealed by empty click
Bonus; detect flag and display around
*/