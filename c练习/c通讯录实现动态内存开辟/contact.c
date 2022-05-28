#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"

void InitContact(struct Contact* ps) {
	ps->data = (struct PeoInfo*)malloc(DEFAULT_SZ * sizeof(struct PeoInfo));  //Ϊ������Ϣ���ٶ�̬�洢�ռ�
	if (ps->data == NULL) {
		return;
	} //����size��ʼֵΪ0
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;  //���ó�ʼ�Ķ�̬�ڴ�ռ�Ĵ�С
}

void CheckCapacity(struct Contact* ps) {  //��鿪�ٵĿռ��Ƿ�����������������������ռ�
	if (ps->size == ps->capacity) {
		struct PeoInfo* ptr = realloc(ps->data, ((ps->capacity) + 2) * sizeof(struct PeoInfo));
		if (ptr != NULL) {
			ps->data = ptr;
			ps->capacity += 2;
		}
		else {
			printf("����ʧ�ܣ�\n");
		}
	}
}

void AddContact(struct Contact *ps) {
	CheckCapacity(ps);
	printf("���������֣�");
	scanf("%s", ps->data[ps->size].name);
	printf("���������䣺");
	scanf("%d", &(ps->data[ps->size].age));
	printf("�������Ա�");
	scanf("%s", ps->data[ps->size].sex);
	printf("������绰��");
	scanf("%s", ps->data[ps->size].tele);
	printf("�������ַ��");
	scanf("%s", ps->data[ps->size].addr);
	ps->size++;
	printf("��ӳɹ���\n");
	/*if (ps->size == MAX) {        
		printf("ͨѶ¼���ˣ�\n");
	}
	else {
		printf("���������֣�");
		scanf("%s", ps->data[ps->size].name);
		printf("���������䣺");
		scanf("%d", &(ps->data[ps->size].age));
		printf("�������Ա�");
		scanf("%s", ps->data[ps->size].sex);
		printf("������绰��");
		scanf("%s", ps->data[ps->size].tele);
		printf("�������ַ��");
		scanf("%s", ps->data[ps->size].addr);
		ps->size++;   
		printf("��ӳɹ���\n");
	}*/
}

void ShowContact(const struct Contact* ps) {
	if (0 == ps->size) {    //��ͨѶ¼��ӡ ��sizeΪ0 ��ͨѶ¼Ϊ��
		printf("ͨѶ¼Ϊ��\n");
	}
	else {   //��ӡͨѶ¼
		int i = 0;
		printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "סַ");
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

static int FindByName(const struct Contact* ps, char name[MAX_NAME]) {  //ͨ�����ֱ�������
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
	printf("��������ɾ���˵�������");
	scanf("%s", name);
	pos = FindByName(ps, name); //���ҵ�ɾ���˵�����
	if (-1 == pos) {
		printf("Ҫɾ���˲����ڻ��������\n");
	}
	else {
		int j = 0;
		for (j = pos; j < ps->size - 1; j++) {  //��ɾ�������ֺ���ĸ�����Ϣ������ǰ���ǴӶ��ﵽɾ��Ŀ�ģ���������ͨѶ¼��������
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;  //����ͬʱҲ��һ�����������һ��������Ϣ��֮����ӻḲ��
		printf("ɾ���ɹ���\n");
	}
}

void SearchContact(const struct Contact* ps) {  
	char name[MAX_NAME];
	printf("������Ҫ�����˵�������");
	scanf("%s", name);
	int pos = FindByName(ps, name); //���ղ�ѯ����ָ����Ϣ���±�
	if (-1 == pos) {
		printf("Ҫ���ҵ��˲����ڻ��������\n");
	}
	else {
		printf("%-15s\t%-4s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "סַ");
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
	printf("������Ҫ�޸��˵�������");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (-1 == pos) {
		printf("Ҫ�޸ĵ��˲����ڻ��������\n");
	}
	else {   //����¼��Ҫ�޸��˵���Ϣ
		printf("���������֣�");  
		scanf("%s", ps->data[pos].name);
		printf("���������䣺");
		scanf("%d", &(ps->data[pos].age));
		printf("�������Ա�");
		scanf("%s", ps->data[pos].sex);
		printf("������绰��");
		scanf("%s", ps->data[pos].tele);
		printf("�������ַ��");
		scanf("%s", ps->data[pos].addr);
		printf("�޸ĳɹ���\n");
	}
}

static int SortByAgeL(const void* d1, const void* d2) {  //�Ӵ�С���������й���
	return (((struct PeoInfo*)d2)->age) -
		(((struct PeoInfo*)d1)->age);
}

static int SortByAgeS(const void* d1, const void* d2) {  //��С�����������й���
	return (((struct PeoInfo*)d1)->age) -
		(((struct PeoInfo*)d2)->age);
}

static int SortByName(const void* d1,const void* d2) {  //���������й���
	return strcmp((((struct PeoInfo*)d1)->name) ,
		(((struct PeoInfo*)d2)->name));
}

void SortContact(struct Contact* ps) {
	int input = 0;
	printf("��ѡ����������ķ�ʽ��\n");
	printf("****  1.������������  2.��������(С����)����  ****\n");
	printf("****  3.�������䣨��С������  0.�˳�ѡ��    ****\n");
	if (ps->size == 0) {
		printf("�����ݽ�����������ӣ�\n");
	}
	do {  //ѡ�����еķ�ʽ
		scanf("%d", &input);
		switch (input) {
		case 1:
			qsort(ps->data, ps->size, sizeof(struct PeoInfo), SortByName);
			printf("����ɹ�������ѡ��չʾ�鿴��\n");
			break;
		case 2:
			qsort(ps->data, ps->size, sizeof(struct PeoInfo), SortByAgeS);
			printf("����ɹ�������ѡ��չʾ�鿴��\n");
			break;
		case 3:
			qsort(ps->data, ps->size, sizeof(struct PeoInfo), SortByAgeL);
			printf("����ɹ�������ѡ��չʾ�鿴��\n");
			break;
		case 0:
			printf("�˳���������ѡ��\n");
			break;
		default:
			printf("����������������룺\n");
			break;
		}
	} while (input != 1 && input != 2 && input!=3 && input != 0);
}	

void DestoryContact(struct Contact* ps) {  //��������󽫿��ٵĶ�̬�ڴ�����
	free(ps->data);
	ps->data = NULL;
}