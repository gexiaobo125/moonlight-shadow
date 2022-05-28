#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"
void menu() {
	printf("**********************************\n");
	printf("****  1.add         2.del     ****\n");
	printf("****  3.search      4.modify  ****\n");
	printf("****  5.show        6.sort    ****\n");
	printf("****          0.exit          ****\n");
	printf("**********************************\n");
}

int main() {
	int input;
	int size = 0;
	struct Contact con;
	InitContact(&con);
	do {
		menu();
		printf("��ѡ��ѡ��ǰ���֣�\n");
		scanf("%d", &input);
		switch (input) {
		case ADD:
			AddContact(&con);
			break;
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con); 
			break;
		case SHOW:
			ShowContact(&con);
			break;
		case SORT:
			SortContact(&con);
			break;
		case EXIT:
			DestoryContact(&con);
			printf("�˳�ͨѶ¼��\n");
			break;
		default:
			printf("ѡ�񲻺ϣ�\n");
		}
	} while (input);
	return 0;
}