#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW 3
#define COL 3

int IsFull(char board[ROW][COL],int row,int col){   //棋盘是否下满
     int i,j;
	 for(i=0;i<row;i++){
		 for(j=0;j<col;j++){
			 if(board[i][j]==' '){
				 return 0;			 
			 }
		 }
	 }
	 return 1;
}

char IsWin(char board[ROW][COL],int row,int col){   //行列对角线是否相同，棋盘是否下满
	int i;
	for(i=0;i<row;i++){
		if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][1]!=' ')
			return board[i][1];
	}
	for(i=0;i<col;i++){
		if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[1][i]!=' ')
			return board[1][i];
	}
	if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[1][1]!=' '){
		return board[1][1];
	}
	if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[1][1]!=' '){
		return board[1][1];
	}
	if(1==IsFull(board,ROW,COL)){
		return 'Q';
	}
	return 'C';
}

void ComputerMove(char board[ROW][COL],int row,int col){
	int x=0,y=0;
	printf("电脑下棋：\n");
	while(1){
	x=rand() % row+0;
	y=rand() % col+0;
    if(board[x][y]==' ')
	{
		board[x][y]='#';
		break;
	}
		
	}
}

void PlayerMove(char board[ROW][COL],int row,int col){
	int x,y;
	printf("玩家走：\n");
	while(1){
		printf("请输入棋子走的目标：");
		scanf("%d%d",&x,&y);
		if(x>=1 && x<=row && y>=1 && y<=col){  //输入范围满足要求
			if(board[x-1][y-1]==' '){
				board[x-1][y-1]='*';
				break;
			}
			else{
				printf("该位置已被占用\n");
			}
		}
		else{
			printf("输入超出范围，请重新输入！\n");
		}
	}
}

void InitBoard(char board[ROW][COL],int row,int col){
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){              //初始棋盘元素为空格
			board[i][j]=' ';
		}
	}
}

void DisplayBoard(char board[ROW][COL],int row,int col){
	int i,j;
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++){
			printf(" %c ",board[i][j]);    //打印出有格子效果的棋盘
			if(j<col-1){
				printf("|");
			}
		}
		printf("\n");
		if(i<row-1){
			for(j=0;j<col;j++){
				printf("---");
				if(j<col-1)
				printf("|");
			}
			printf("\n");
		}
	}
}

void menu(){
	printf("*********************************\n");
    printf("**** 1.开始游戏   0.结束游戏 ****\n");
    printf("*********************************\n");
}

void game(){
	char ret;
	char board[ROW][COL]={0};
	InitBoard(board,ROW,COL);  //初始化棋盘
	DisplayBoard(board,ROW,COL); //打印棋盘
	while(1){
	PlayerMove(board,ROW,COL);  //玩家选择移动
	DisplayBoard(board,ROW,COL); //打印棋盘
    ret=IsWin(board,ROW,COL);  //检测是否获胜 失败 平局
	if(ret!='C'){
		break;
	}
	ComputerMove(board,ROW,COL); //电脑随机选择移动
    DisplayBoard(board,ROW,COL);
    ret=IsWin(board,ROW,COL);
	if(ret!='C'){
		break;
	}
	}
	if(ret=='*'){
		printf("玩家赢\n");
	}
	else if(ret=='#'){
		printf("电脑赢\n");
	}
	else if(ret=='Q'){
		printf("平局！\n");
	}
}

void test(){
	int input=0;
	srand((unsigned int)time(NULL));  //电脑棋子随机布置
	do
	{
		menu();  //打印菜单
		printf("请选择：\n");
		scanf("%d",&input);
		switch(input){
		case 1:
			game();  //开启游戏
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误，重新选择");
			break;
		}
	}while(input);
}
int main(){
	test();
	return 0;
}