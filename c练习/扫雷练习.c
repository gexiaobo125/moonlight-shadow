#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW 9  //确定地图大小
#define COL 9
#define ROWS ROW+2  //将地图扩大一圈，防止扫描边界周围代码繁杂
#define COLS COL+2
#define MINE_COUNT 10   //确定雷数
voidDisPlayBoard(char board[ROWS][COLS],int row,int col);

voidExpandMap(int signmap[ROWS][COLS],char mine[ROWS][COLS],char show[ROWS][COLS],int x,int y){  //当输入位置周围有一定范围都无雷时，地图扩展至周围有雷的位置 周围无雷为空格
	int i,Fx,Fy,count;
	int dir[8][2]={{-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};  //用于扫描该位置周围点
	Fx=x;
	Fy=y;
    signmap[x][y]=1;  //将扩展的初始位置 标记为1 放置递归时母位置与子位置重复来回循环 
	for(i=0;i<8;i++){
		x=x+dir[i][0];
		y=y+dir[i][1];
			if(x>=1 && x<=ROW && y>=1 && y<=COL && (x==Fx && y==Fy)==0 && signmap[x][y]!=1){
               count=get_mine_count(mine,x,y);
			   if(count==0 && mine[x][y]!='1' ){
               show[x][y]=' ';
               
               ExpandMap(signmap,mine,show,x,y);  //若周围无雷 开始递归扩展扫描
			   }
			   else{
				  show[x][y]=count+'0';
			   }
			}
			x=Fx;
			y=Fy;
	}
    
}

int get_mine_count(char mine[ROWS][COLS],int x,int y)  //扫描四周是否有雷 有雷返回雷数 无雷返回0
{
	return mine[x-1][y]+mine[x-1][y-1]+mine[x][y-1]+mine[x+1][y-1]+mine[x+1][y]+mine[x+1][y+1]+mine[x][y+1]+mine[x-1][y+1]-8*'0';
}

void FindMine(int signmap[ROWS][COLS],char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col){
	int x,y,win=0;
	while(win<row*col-MINE_COUNT){
	printf("请输入排雷的坐标：");
	scanf("%d%d",&x,&y);
	if(x>=1 && x<=row && y>=1 && y<=col) //确保输入坐标在范围内
	{
        if(mine[x][y]=='1'){   //雷的位置为字符1
			printf("很遗憾，你踩到雷了...\n");
            DisPlayBoard(mine,row,col);
			break;
		}
		else{
			int count=get_mine_count(mine,x,y);  //get_mine_count为扫描该位置周围位置是否有雷
			if(count==0){  //若周围无雷，则该位置为空格
                show[x][y]=' ';
                ExpandMap(signmap,mine,show,x,y); //周围无雷 该位置为空格，同时地图向四周扩展，直到遇到周围有雷的位置停止
			}
			else{
            show[x][y]=count+'0';
			}
            DisPlayBoard(show,row,col);
			win++;
		}
	}
	else{
		printf("输入坐标超出范围，请重新输入！\n");
	}
	}
	if(win==row*col-MINE_COUNT){  //当非雷区全部排完时
		printf("恭喜你，获胜了！\n");
        DisPlayBoard(mine,row,col);
	}

}

void SetMine(char board[ROWS][COLS],int row,int col){  //布置雷区
	int count=MINE_COUNT,x,y;
	while(count){
		x=rand()%row+1;
		y=rand()%col+1;
		if(board[x][y]=='0'){  //确保雷不会重复布置在一个区域
			board[x][y]='1';
			count--;
		}
	}
}

void DisPlayBoard(char board[ROWS][COLS],int row,int col)  //打印地图
{
	int i,j;
	for(i=0;i<=col;i++){
		printf("%d ",i);
	}
	printf("\n");
	for(i=1;i<=row;i++)
	{
		printf("%d ",i);
		for(j=1;j<=col;j++){
			printf("%c ",board[i][j]);
		}
		printf("\n");
	}
}

void InitBoard(char board[ROWS][COLS],int rows,int cols,char set){  //初始化地图
	int i,j;
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			board[i][j]=set;
		}
	}

}

void game(){
    int signmap[ROWS][COLS]={0};  //用于标记特定位置
	char mine[ROWS][COLS]={0};  //雷区数组
	char show[ROWS][COLS]={0};  //玩家视图
	InitBoard(mine,ROWS,COLS,'0');  //初始化地雷地图
	InitBoard(show,ROWS,COLS,'*');  //初始化玩家视图
	DisPlayBoard(mine,ROW,COL);  //打印地雷图
    DisPlayBoard(show,ROW,COL);  //打印玩家视图
	SetMine(mine,ROW,COL);  //布雷
	FindMine(signmap,mine,show,ROW,COL);  //查找雷
}

void menu(){
	printf("******************************\n");
	printf("*** 1.开始游戏  0.退出游戏 ***\n");
	printf("******************************\n");
}

void test(){
    int input;
	srand((unsigned int)time(NULL));
	do{
		menu();                   //打印菜单
		printf("请选择：\n");
		scanf("%d",&input);
		switch(input){
		case 1:
			game();   
			break;
		case 0:
			printf("游戏结束\n");
			break;
		default:
			printf("选择错误，请重新选择！\n");
			break;
		}

	}while(input);
}

int main(){
	test();
	return 0;
}