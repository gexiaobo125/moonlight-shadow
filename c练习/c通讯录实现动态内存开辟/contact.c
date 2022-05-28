#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"

void InitContact(struct Contact* ps) {
	ps->data = (struct PeoInfo*)malloc(DEFAULT_SZ * sizeof(struct PeoInfo));  //为个人信息开辟动态存储空间
	if (ps->data == NULL) {
		return;
	} //设置size初始值为0
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;  //设置初始的动态内存空间的大小
}

void CheckCapacity(struct Contact* ps) {  //检查开辟的空间是否满，若满则继续申请两个空间
	if (ps->size == ps->capacity) {
		struct PeoInfo* ptr = realloc(ps->data, ((ps->capacity) + 2) * sizeof(struct PeoInfo));
		if (ptr != NULL) {
			ps->data = ptr;
			ps->capacity += 2;
		}
		else {
			printf("增容失败！\n");
		}
	}
}

void AddContact(struct Contact *ps) {
	CheckCapacity(ps);
	printf("请输入名字：");
	scanf("%s", ps->data[ps->size].name);
	printf("请输入年龄：");
	scanf("%d", &(ps->data[ps->size].age));
	printf("请输入性别：");
	scanf("%s", ps->data[ps->size].sex);
	printf("请输入电话：");
	scanf("%s", ps->data[ps->size].tele);
	printf("请输入地址：");
	scanf("%s", ps->data[ps->size].addr);
	ps->size++;
	printf("添加成功！\n");
	/*if (ps->size == MAX) {        
		printf("通讯录满了！\n");
	}
	else {
		printf("请输入名字：");
		scanf("%s", ps->data[ps->size].name);
		printf("请输入年龄：");
		scanf("%d", &(ps->data[ps->size].age));
		printf("请输入性别：");
		scanf("%s", ps->data[ps->size].sex);
		printf("请输入电话：");
		scanf("%s", ps->data[ps->size].tele);
		printf("请输入地址：");
		scanf("%s", ps->data[ps->size].addr);
		ps->size++;   
		printf("添加成功！\n");
	}*/
}

void ShowContact(const struct Contact* ps) {
	if (0 == ps->size) {    //将通讯录打印 当size为0 则通讯录为空
		printf("通讯录为空\n");
	}
	else {   //打印通讯录
		int i = 0;
		printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "名字", "年龄", "性别", "电话", "住址");
		for (i = 0; i < ps->size; i++) {
			printf("%-15s\t%-4d\t%-5s\t%-12s\t%-20s\n",
				ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].tele,
				ps->data[i].addr);
		}
	}
}

static int FindByName(const struct Contact* ps, char name[MAX_NAME]) {  //通过名字遍历查找
	int i = 0;
	for (i = 0; i < ps->size; i++) {
		if (0 == strcmp(ps->data[i].name, name)) {
			return i;
		}
	}
	return -1;
}

void DelContact(struct Contact* ps) {  
	char name[MAX_NAME];
	int pos;
	printf("请输入想删除人的姓名：");
	scanf("%s", name);
	pos = FindByName(ps, name); //查找到删除人的名字
	if (-1 == pos) {
		printf("要删除人不存在或输入错误\n");
	}
	else {
		int j = 0;
		for (j = pos; j < ps->size - 1; j++) {  //将删除人名字后面的个人信息依次向前覆盖从而达到删除目的，并且排列通讯录排列完整
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;  //数量同时也减一，最后多余出来一个个人信息在之后添加会覆盖
		printf("删除成功！\n");
	}
}

void SearchContact(const struct Contact* ps) {  
	char name[MAX_NAME];
	printf("请输入要查找人的姓名：");
	scanf("%s", name);
	int pos = FindByName(ps, name); //接收查询到的指定信息的下标
	if (-1 == pos) {
		printf("要查找的人不存在或输入错误！\n");
	}
	else {
		printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "名字", "年龄", "性别", "电话", "住址");
			printf("%-15s\t%-4d\t%-5s\t%-12s\t%-20s\n",
				ps->data[pos].name,
				ps->data[pos].age,
				ps->data[pos].sex,
				ps->data[pos].tele,
				ps->data[pos].addr);
		
	}
}

void ModifyContact(struct Contact* ps) {
	char name[MAX_NAME];
	printf("请输入要修改人的姓名：");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (-1 == pos) {
		printf("要修改的人不存在或输入错误！\n");
	}
	else {   //重新录入要修改人的信息
		printf("请输入名字：");  
		scanf("%s", ps->data[pos].name);
		printf("请输入年龄：");
		scanf("%d", &(ps->data[pos].age));
		printf("请输入性别：");
		scanf("%s", ps->data[pos].sex);
		printf("请输入电话：");
		scanf("%s", ps->data[pos].tele);
		printf("请输入地址：");
		scanf("%s", ps->data[pos].addr);
		printf("修改成功！\n");
	}
}

static int SortByAgeL(const void* d1, const void* d2) {  //从大到小按年龄排列规则
	return (((struct PeoInfo*)d2)->age) -
		(((struct PeoInfo*)d1)->age);
}

static int SortByAgeS(const void* d1, const void* d2) {  //从小到大按年龄排列规则
	return (((struct PeoInfo*)d1)->age) -
		(((struct PeoInfo*)d2)->age);
}

static int SortByName(const void* d1,const void* d2) {  //按名字排列规则
	return strcmp((((struct PeoInfo*)d1)->name) ,
		(((struct PeoInfo*)d2)->name));
}

void SortContact(struct Contact* ps) {
	int input = 0;
	printf("请选择排序整理的方式：\n");
	printf("****  1.按照姓名排序  2.按照年龄(小到大)排序  ****\n");
	printf("****  3.按照年龄（大到小）排序  0.退出选择    ****\n");
	if (ps->size == 0) {
		printf("无内容进行排序，请添加！\n");
	}
	do {  //选择排列的方式
		scanf("%d", &input);
		switch (input) {
		case 1:
			qsort(ps->data, ps->size, sizeof(struct PeoInfo), SortByName);
			printf("排序成功！可以选择展示查看！\n");
			break;
		case 2:
			qsort(ps->data, ps->size, sizeof(struct PeoInfo), SortByAgeS);
			printf("排序成功！可以选择展示查看！\n");
			break;
		case 3:
			qsort(ps->data, ps->size, sizeof(struct PeoInfo), SortByAgeL);
			printf("排序成功！可以选择展示查看！\n");
			break;
		case 0:
			printf("退出排序整理选择！\n");
			break;
		default:
			printf("输入错误！请重新输入：\n");
			break;
		}
	} while (input != 1 && input != 2 && input!=3 && input != 0);
}	

void DestoryContact(struct Contact* ps) {  //程序结束后将开辟的动态内存销毁
	free(ps->data);
	ps->data = NULL;
}