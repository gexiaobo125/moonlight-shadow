#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 1000
#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDR 30

enum Option {   //枚举代替开关选择数字，增加可读性
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT
};

struct PeoInfo {          //定义个人信息结构体
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
};

struct Contact {         //定义通讯录结构体 包含个人信息数组（其中存放MAX个个人信息） size记录当前个人信息的数量。
	struct PeoInfo data[MAX];
	int size;
};

void InitContact(struct Contact* ps);  //声明初始通讯录函数
void AddContact(struct Contact* ps);  //声明添加个人信息函数
void ShowContact(const struct Contact* ps); //声明通讯录展示函数
void DelContact(struct Contact* ps);  //声明删除某个个人信息函数
void SearchContact(struct Contact* ps);  //声明查询某个信息函数
void ModifyContact(struct Contact* ps);  //声明修改某个个人信息函数
void SortContact(struct Contact* ps);  //声明对通讯录信息排序函数