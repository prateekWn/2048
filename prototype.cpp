#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>

using namespace std;

int board[4][4];

int dircRow[] = {0,1,0,-1};

int dircCol[] = {1,0,-1,0};

/*
directional mapping it will be unpleasent to write if cases,
whenever we are pressing a key.
we will map the direction up down left and right 
and map them to numbers from 0 to 3
0 will be down so we are increasing the row by going down and we dont change the col, 
1 will be for right so we dont chnage the row but we are increasing the col,
2 will be for up which will decrease the row and we will not change the col, 
and 3 will be for left which will decrease th col and it leave the row unchanged.
==> In the row and col array 0 means no change , 1 means increment and -1 means decrement 
*/

pair<int,int> generateUnOccupiedPosition(){

	int occupied = 1 , row , col;

	while(occupied){

		row = rand() % 4;
		col = rand() % 4;

		if(board[row][col]==0)
			occupied=0;

	}

	return make_pair(row,col);
}

pair<int,int> produceRandomNo(){

	pair<int,int> pos = generateUnOccupiedPosition();
	board[pos.first][pos.second] = 2;
}

void newGame(){

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			board[i][j]=0;
		}	
	}

	produceRandomNo();

}

void print2048Board(){

	system("cls");

	for(int i=0; i<4; i++){

		for(int j=0; j<4; j++){

			if(board[i][j]==0)
				cout<<setw(4)<<"[]";
			
			else
				cout<<setw(4)<<board[i][j];

		}

		cout<<endl;
	}

	cout<<"n: newGame, w: up, s: down, a: left, d: right, q: quit the game"<<endl;

}

bool canMoveOrNot(int i , int j , int nextRow , int nextCol){

	if(nextCol<0 || nextRow<0 || nextCol>=4 || nextRow>=4 
		|| board[i][j] != board[nextRow][nextCol] && board[nextRow][nextCol] != 0)
		return false;

	return true;

} 

void applyMove(int direction){

	int startRow = 0, startCol = 0, rowStep = 1, colStep = 1;

	if(direction==0){

		startRow = 3;

		rowStep = -1;
	}

	if(direction==1){

		startCol = 3;

		colStep = -1;
	}

	int movePossible = 0 , canaddpiece = 0;

	do{

		movePossible = 0;
		for (int i = startRow; i>=0 && i<4; i +=rowStep)
		{
			for (int j = startCol; j>=0 && j < 4; j +=colStep)
			{
				int nextR = i + dircCol[direction];
				int nextC = j + dircRow[direction];
				// cout<<i<<" "<<j<<" "<<nextR<<" "<<nextC<<endl;
				if (board[i][j]!=0 && canMoveOrNot(i , j , nextR , nextC)){
					board[nextR][nextC] += board[i][j];
					board[i][j] = 0;
					movePossible = 1;
					canaddpiece = 1;
				}
			}	
		}	
		print2048Board();
	}
	while(movePossible);		
	if(canaddpiece){
		produceRandomNo();
	}
		
}

int main(int argc, char const *argv[])
{
	
	srand(time(0));

	char whereToMove[128];

	whereToMove['s'] = 0;
	whereToMove['d'] = 1;
	whereToMove['w'] = 2;
	whereToMove['a'] = 3;
	
	newGame();

	while(true){

		print2048Board();
		
		char enter;

		cin >> enter;

		if( enter =='n')
			newGame();

		else if( enter =='q')
			break;
		
		else{
			
			int directionToMove = whereToMove[ enter ];
			// cout<<directionToMove<<endl;
			applyMove(directionToMove);
		}
	
	}

	return 0;
}