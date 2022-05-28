#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//#define MAX 1000
#define DEFAULT_SZ 3
#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDR 30

enum Option {   //ö�ٴ��濪��ѡ�����֣����ӿɶ���
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT
};

struct PeoInfo {          //���������Ϣ�ṹ��
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
};

struct Contact {     //����ͨ��¼�ṹ��    
	struct PeoInfo* data;   //���������Ϣָ�� ֮�󿪱ٶ�̬�ڴ�
	int size;  //��¼��ǰ������Ϣ����
	int capacity;  //��¼��ǰ�������
};

void InitContact(struct Contact* ps);  //������ʼͨѶ¼����
void AddContact(struct Contact* ps);  //������Ӹ�����Ϣ����
void ShowContact(const struct Contact* ps); //����ͨѶ¼չʾ����
void DelContact(struct Contact* ps);  //����ɾ��ĳ��������Ϣ����
void SearchContact(struct Contact* ps);  //������ѯĳ����Ϣ����
void ModifyContact(struct Contact* ps);  //�����޸�ĳ��������Ϣ����
void SortContact(struct Contact* ps);  //������ͨѶ¼��Ϣ������
void CheckCapacity(struct Contact* ps);  //������̬�ڴ����ݺ���
void DestoryContact(struct Contact* ps);  //������̬�ڴ����ٺ���