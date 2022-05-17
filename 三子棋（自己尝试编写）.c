 #include <stdio.h>
#include <stdlib.h>
void printqipan(int qipan[][3])  //打印棋盘
{
    int i2, j2;
    for (i2 = 0; i2 < 3; i2++)
    {
        for (j2 = 0; j2 < 3; j2++)
        {
            printf("%c ", qipan[i2][j2]);
        }
        printf("\n");
    }
}
int bianliqipan(int qipan[][3])  //遍历数组 是否下满 
{
    int i1, j1;
    for (i1 = 0; i1 < 3; i1++)
    {
        for (j1 = 0; j1 < 3; j1++)
        {
            if (qipan[i1][j1] == '#')
            {
                return 1;
            }
        }
    }
    return 0;
}

int qipancircle(int qipan[][3], char c, char d)  //遍历数组找寻获胜平局等情况
{
    int m=0;
    for (m = 0; m < 3; m++)
    {
        if (((qipan[m][0] == qipan[m][1])&&(qipan[m][1]== qipan[m][2])&&(qipan[m][2] == c)) || ((qipan[0][m] == qipan[1][m])&&(qipan[1][m] == qipan[2][m])&&(qipan[2][m] == c)) || ((qipan[0][0] == qipan[1][1])&&(qipan[1][1] == qipan[2][2])&&(qipan[2][2] == c)) || ((qipan[0][2] == qipan[1][1])&&(qipan[1][1] == qipan[2][0])&&(qipan[2][0] == c)))
        {
            return 2;
        }
        else if (((qipan[m][0] == qipan[m][1])&&(qipan[m][1]== qipan[m][2])&&(qipan[m][2] == d)) || ((qipan[0][m] == qipan[1][m])&&(qipan[1][m] == qipan[2][m])&&(qipan[2][m] == d)) || ((qipan[0][0] == qipan[1][1])&&(qipan[1][1] == qipan[2][2])&&(qipan[2][2] == d)) || ((qipan[0][2] == qipan[1][1])&&(qipan[1][1] == qipan[2][0])&&(qipan[2][0] == d)))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
int main()
{
    int qipan[3][3] = {0}, i, j, xa, ya, xb, yb;
    char a = 'X', b = 'O';
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            qipan[i][j] = '#';
        }
    }
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%c ", qipan[i][j]);
        }
        printf("\n");   //初始化并打印最初棋盘
    }
    while (1)
    {
        do
        {
            printf("请A玩家正确输入棋子坐标:\n");
            scanf("%d %d", &xa, &ya);
        } while (xa > 3 || ya > 3);  //当输入坐标溢出时重新输入
        qipan[xa - 1][ya - 1] = a;   //在输入坐标对应的位置覆盖棋子
        printqipan(qipan);    //打印棋盘
        if (qipancircle(qipan, a, b) == 2)  //获胜条件
        {
            printf("恭喜A玩家获胜!\n");
            break;
        }
        else if (bianliqipan(qipan) == 0)
        {
            break;
        }

        do
        {
            printf("请B玩家正确输入棋子坐标：\n");
            scanf("%d %d", &xb, &yb);
        } while (xb > 3 || yb > 3);  //与A同理 以下为B玩家输入时情况
        qipan[xb - 1][yb - 1] = b;
        printqipan(qipan);
        if (qipancircle(qipan, a, b) == 1)
        {
            printf("恭喜B玩家获胜!\n");
            break;
        }
        else if (bianliqipan(qipan) == 0)
        {
            break;
        }
    }
    if (qipancircle(qipan, a, b) == 0)  //qipancircle为判断获胜或平局情况
    {
        printf("未有取胜者...\n");
    }
    printf("游戏结束!\n");

    system("pause");
    return 0;
}