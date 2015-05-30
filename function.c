/********************************
	���α׷��� ���� in C

		�⸻ ������Ʈ

	����: ��ȭ��ȣ�� ���α׷�

		2015. 5. 30.

		����� (141013)

********************************/
#include "list.h"

extern node_t *dummy;
extern int count;


// ���� ��� ����
void makeDummy()
{
	dummy = (node_t *)malloc(sizeof(node_t));
	dummy->next = dummy;
	dummy->prev = dummy;
}

void freeAll(list_t *phonelist)
{
	node_t* tempNode;
	node_t* curNode = dummy->next;

	while (curNode != dummy){
		tempNode = curNode;
		curNode = curNode->next;
		free(tempNode);
	}

	free(dummy);
	free(phonelist);
}

// �޴� ȭ�� ���
void showMenu()
{
	printf("����������������������������������\n");
	printf("��                              ��\n");
	printf("��      ����ó �޴�             ��\n");
	printf("��                              ��\n");
	printf("����������������������������������\n");
	printf("��    0. ����ó ���� �ҷ�����   ��\n");
	printf("����������������������������������\n");
	printf("��    1. ����ó �߰�            ��\n");
	printf("����������������������������������\n");
	printf("��    2. ����ó ����            ��\n");
	printf("����������������������������������\n");
	printf("��    3. ����ó �˻�            ��\n");
	printf("����������������������������������\n");
	printf("��    4. ����ó ����            ��\n");
	printf("����������������������������������\n");
	printf("��    5. ��ü ����ó ����       ��\n");
	printf("����������������������������������\n");
	printf("��    6. ����ó ���� ����       ��\n");
	printf("����������������������������������\n");
	printf("��    7. ������                 ��\n");
	printf("����������������������������������\n");
	printf("\n�޴� ��ȣ�� �Է��ϼ���: ");
}


// �޴� ȭ�鿡�� ����� �Է°� Ȯ��
int inputChoice()
{
	char input[MAX_CHAR];
	int num;

	while (1){
		fflush(stdin);
		scanf("%s", input);

		num = atoi(input);

		if (((strlen(input)) > 1) || (num < 0) || (num > 7))
			printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���: ");
		else
			return num;
	}
}


// �Է� ���뿡�� ���� ���ֱ�
char* removeSpace(char temp[])
{
	int i = 0, j = 0;
	char real[MAX_CHAR];

	while (temp[i] != '\0'){
		if (temp[i] != ' '){
			real[j] = temp[i];
			j++;
		}
		i++;
	}
	real[j] = '\0';

	return real;
}


// ���� �ҷ�����
list_t* fileOpen(list_t *phonelist)
{
	int state, readCount = 0;
	char *readRecord;
	char buffer[MAX_SAVED_CHARACTER_PER_RECORD];
	node_t *curNode, *nextNode;

	puts("\n���� ���丮�� �ִ� SIMPLEphoneBOOK.txt �κ��� ����ó�� �ҷ��ɴϴ�.");

	FILE *file = fopen("SIMPLEphoneBOOK.txt", "rt");

	if (file == NULL){
		puts("���� �ҷ����⿡ �����߽��ϴ�.");
		return phonelist;
	}

	memset(buffer, 0, sizeof(buffer)); // ���� �ʱ�ȭ
	readRecord = fgets(buffer, sizeof(buffer), file);

	state = isPhoneBookEmpty(buffer);

	if (state == 1)				// ��ȭ��ȣ�� ������ ��� �ִ� ��� ����
		return phonelist;
	
	curNode = (node_t *)malloc(sizeof(node_t));
			
	while (1){

		readCount++;
		insertFromBufferToNode(curNode, buffer);

		if (readCount == 1){ // �� ó�� �ԷµǴ� ����� ���
			dummy->next = curNode;
			curNode->prev = dummy;
		}

		memset(buffer, 0, sizeof(buffer));
		readRecord = fgets(buffer, sizeof(buffer), file);

		if (readRecord != NULL){ // �ڿ� �Էµ� ������ �ִ� ���
						
			nextNode = (node_t *)malloc(sizeof(node_t));
			curNode->next = nextNode;
			nextNode->prev = curNode;
			curNode = nextNode;
		
		} else{  // �� �̻� �Էµ� ����ó ������ ���� ���
			curNode->next = dummy;
			dummy->prev = curNode;
			
			break;
		}
	}

	state = fclose(file);
	if (state != 0)
		puts("�ҷ��� ���� �ݱ⿡ �����߽��ϴ�.");

	return phonelist;
}


// ��ȭ��ȣ�� ������ ��� �ִ��� Ȯ��
int isPhoneBookEmpty(char buf[])
{
	char *ptr;

	ptr = buf;

	if (*ptr == '\n'){
		puts("\nSIMPLEphoneBOOK.txt ������ ��� �ֽ��ϴ�.\n");
		return 1;
	}
	return 0;
}


// ������ �����͸� ���� �����ϱ�
void insertFromBufferToNode(node_t* curNode, char buffer[])
{
	char *ptr, *token, *endOfString;
	char record[MAX_SAVED_CHARACTER_PER_RECORD];
	char *tempString;
	int i = 0, j = 1;

	ptr = buffer;
	token = strstr(buffer, " �� ");
	endOfString = strstr(buffer, "\n");

	while (*ptr != '\0'){

		record[i] = *ptr;

		if (ptr == token){

			record[i] = '\0';

			if (j == 1){ // ��� �������� �̸��� �Է�
				tempString = removeSpace(record);
				strcpy(curNode->data.name, tempString);
				j = 2;
			}
			else { // ��� �������� ��ȭ��ȣ�� �Է�
				tempString = removeSpace(record);
				strcpy(curNode->data.phone, tempString);
				j = 1;
			}

			i = 0;
			ptr += strlen(" �� ");
			token = strstr(ptr, " �� ");

		}
		else if (ptr == endOfString){

			record[i] = '\0';
			tempString = removeSpace(record);
			strcpy(curNode->data.nickName, tempString);	// ��� �������� ���� �Է�

			break;
		}
		else{
			ptr++;
			i++;
		}
	}

	count++;
}


/*
node_t* insertFromBufferToNode(list_t *phonelist, char buffer[])
{
	node_t *curNode, *nextNode;
	char *ptr, *dataToken, *personToken;
	char record[MAX_SAVED_CHARACTER_PER_RECORD];
	char *tempString;
	int i = 0, j = 1;
	
	personToken = strstr(buffer, "\n");
	dataToken = strstr(buffer, " �� ");

	// ���� ��忡 ����Ǵ� ù ��° ���� �Է�
	curNode = (node_t *)malloc(sizeof(node_t));
	phonelist->head->next = curNode;
	curNode->prev = phonelist->head;
	count++;

	while (*ptr != 1){
		
		record[i] = *ptr;

		if (ptr == dataToken){

			record[i] = '\0';

			if (j == 1){ // ��� �������� �̸��� �Է�
				tempString = removeSpace(record);
				strcpy(curNode->data.name, tempString);
				j = 2;
			} else { // ��� �������� ��ȭ��ȣ�� �Է�
				tempString = removeSpace(record);
				strcpy(curNode->data.phone, tempString);
				j = 1;
			}

			i = 0;
			ptr += strlen(" �� ");
			dataToken = strstr(ptr, " �� ");

		} else if (ptr == personToken){

			record[i] = '\0';
			tempString = removeSpace(record);
			strcpy(curNode->data.nickName, tempString);	// ��� �������� ���� �Է�

			i = 0;
			ptr++;
			personToken = strstr(ptr, "\n");

			if (personToken != NULL){ // �ڿ� �� �Էµ� ����ó ������ �ִ� ���

				nextNode = (node_t *)malloc(sizeof(node_t));
				curNode->next = nextNode;
				nextNode->prev = curNode;
				curNode = nextNode;

				count++;

			} else {	// �� �̻� �Էµ� ����ó ������ ���� ���
				curNode->next = dummy;
				dummy->prev = curNode;
			}

		} else{
			ptr++;
			i++;
		}

	}

	return phonelist;
}
*/


// �ֿܼ��� ������ �Է¹ޱ�
node_t* inputData(void)
{
	node_t *input;

	input = (node_t *)malloc(sizeof(node_t));

	nameInput(input); // �̸� �Է�
	phoneInput(input); // ��ȭ��ȣ �Է�
	nicknameInput(input); // ���� �Է�

	showPerson(input); // �Է¹��� ���� ���
	
	count++;

	return input;
}

// �̸� �Է�
void nameInput(node_t *input)
{
	char tempName[MAX_CHAR], *personName;

	fflush(stdin);
	printf("\n�̸� : ");
	fgets(tempName, sizeof(tempName), stdin);
	tempName[strlen(tempName) - 1] = '\0';
	personName = removeSpace(tempName);
	strcpy(input->data.name, personName);
}

// ��ȭ��ȣ �Է�
void phoneInput(node_t *input)
{
	char *phoneNumber, tempNumber[MAX_PHONE_NUMBER];
	int i = 0;

	do {
		fflush(stdin);
		printf("��ȭ��ȣ : ");
		fgets(tempNumber, sizeof(tempNumber), stdin);
		tempNumber[strlen(tempNumber) - 1] = '\0';
		phoneNumber = removeSpace(tempNumber);

		while (i < (int)strlen(phoneNumber)){
			if (((phoneNumber[i] >= '0') && (phoneNumber[i] <= '9')) || (phoneNumber[i] == '-'))
				i++;
			else{	 // ��ȭ��ȣ�� ���ڰ� ���Ե� ���, ���Է� �䱸
				printf("\n��ȭ��ȣ�� ���ڿ� -�� �Է��� �� �ֽ��ϴ�.\n");
				printf("��ȭ��ȣ�� �ٽ� �Է��ϼ���.\n\n");
				i = 0;
				break;
			}
		}
	} while (i < (int)strlen(phoneNumber));

	strcpy(input->data.phone, phoneNumber);
}

// ���� �Է�
void nicknameInput(node_t *input)
{
	char tempName[MAX_CHAR], *personNickname;

	fflush(stdin);
	printf("���� : ");
	fgets(tempName, sizeof(tempName), stdin);
	tempName[strlen(tempName) - 1] = '\0';
	personNickname = removeSpace(tempName);
	strcpy(input->data.nickName, personNickname);
}

// ��� �Է��� ���� ���
void showPerson(node_t *input)
{
	printf("\n�Էµ� ����ó: %s\t%s\t%s\n", input->data.name, input->data.phone, input->data.nickName);
}


// �Էµ� ������ ��ȭ��ȣ�ο� ���� �߰�
void insertNode(list_t *phonelist, node_t *record)
{
	if (dummy->next == dummy)	// �� ó�� �Է��� ���
		dummy->next = record;
	else
		dummy->prev->next = record;

	record->prev = dummy->prev;
	record->next = dummy;
	dummy->prev = record;

	return;
}


// ��ȭ��ȣ�ο��� ��� ����
void deleteNode(list_t *phonelist)
{
	node_t *curNode;

	printf("\n������ ����ó�� �˻��մϴ�.\n\n");

	curNode = searchNode(phonelist);

	if (curNode != NULL){
		curNode->next->prev = curNode->prev;
		curNode->prev->next = curNode->next;
		free(curNode);
		count--;
		printf("\n�˻��� ����ó�� �����Ǿ����ϴ�.\n\n");
	}
}

// �˻� �ɼ� (�̸�/��ȭ��ȣ �˻�)
int searchOption(int num)
{
	char input[MAX_CHAR];

	while ((num != 1) && (num != 2)){
		fflush(stdin);
		printf("\n�̸����� �˻��Ͻðڽ��ϱ�? ��ȭ��ȣ�� �˻��Ͻðڽ��ϱ�?\n");
		printf("(�̸� �˻� = 1, ��ȭ��ȣ �˻� = 2): ");
		scanf("%s", input);

		num = inputCheck(input);
	}
	return num;
}

// ���� 1, 2 �ܿ� �߸��� �Է� Ȯ��
int inputCheck(char input[])
{
	int num;

	num = atoi(input);

	if (((strlen(input)) > 1) || (num < 1) || (num > 2))
		printf("\n�߸��� �Է��Դϴ�.\n");
	return num;
}

// ����� ����ó�� ���
void printPerson(node_t *curNode)
{
	printf("\n�̸�: %s\n", curNode->data.name);
	printf("��ȭ��ȣ: %s\n", curNode->data.phone);
	printf("����: %s\n\n", curNode->data.nickName);
}


// ����ó �˻�
node_t* searchNode(list_t *phonelist)
{
	int num = 0;
	char tempName[MAX_CHAR], *personName;
	char tempNumber[MAX_PHONE_NUMBER], *personPhone;
	node_t *curNode;

	num = searchOption(num);

	curNode = phonelist->head->next;

	if (num == 1){	// �̸����� �˻�
		fflush(stdin);
		printf("\n�˻��� �̸�: ");
		fgets(tempName, sizeof(tempName), stdin);
		tempName[strlen(tempName) - 1] = '\0';
		personName = removeSpace(tempName);

		while (strcmp(curNode->data.name, personName)){
			curNode = curNode->next;
			if (curNode == dummy){
				printf("\n�Է��� ����� ����ó�� �������� �ʽ��ϴ�.\n");
				return (node_t*)NULL;
			}
		}
		printPerson(curNode);
		return curNode;

	}
	else{	// ��ȭ��ȣ�� �˻�
		fflush(stdin);
		printf("\n�˻��� ��ȭ��ȣ: ");
		fgets(tempNumber, sizeof(tempNumber), stdin);
		tempNumber[strlen(tempNumber) - 1] = '\0';
		personPhone = removeSpace(tempNumber);

		while (strcmp(curNode->data.phone, personPhone)){
			curNode = curNode->next;
			if (curNode == dummy){
				printf("\n�Է��� ��ȭ��ȣ�� �������� �ʽ��ϴ�.\n");
				return (node_t*)NULL;
			}
		}
		printPerson(curNode);
		return curNode;
	}
}


// ����ó ����
void updateNode(list_t *phonelist)
{
	node_t *curNode;

	printf("\n������ ����ó�� �˻��մϴ�.\n\n");

	curNode = searchNode(phonelist);

	if (curNode != NULL){
		printf("\n����ó�� �����մϴ�.\n\n");
		nameInput(curNode);
		phoneInput(curNode);
		nicknameInput(curNode);
		printf("\n������ ����ó�� ����Ǿ����ϴ�.\n\n");
	}
}


// ��ü ����ó ���
void showAllPerson(list_t *phonelist)
{
	node_t *curNode;
	int i = 0;

	curNode = phonelist->head->next;

	puts("����������������������������������������������\n");
	puts("     �̸�         �� ��ȭ��ȣ        ����\n");
	puts("����������������������������������������������\n");
	while (curNode != dummy){
		printf("%10s �� %16s �� %8s\n", curNode->data.name, curNode->data.phone, curNode->data.nickName);
		curNode = curNode->next;
		i++;
	}
	puts("����������������������������������������������\n");
	printf("\n\t\t�̻� %d��\n", i);
}


// ���Ϸ� ����
void filePrint(list_t *phonelist)
{
	node_t *curNode;
	int state;

	FILE *file = fopen("SIMPLEphoneBOOK.txt", "wt");

	if (file == NULL){
		puts("���� ���忡 �����߽��ϴ�.");
		return;
	}

	curNode = phonelist->head->next;

	while (curNode != dummy){
		fprintf(file, "%10s �� %16s �� %8s\n", curNode->data.name, curNode->data.phone, curNode->data.nickName);
		curNode = curNode->next;
	}

	puts("\n��ȭ��ȣ�ΰ� SIMPLEphoneBOOK.txt ���Ϸ� ����Ǿ����ϴ�.");

	state = fclose(file);
	if (state != 0)
		puts("������ ���� �ݱ⿡ �����߽��ϴ�.");
}


// �� �� ���� �Ϸ�� ��, �ٽ� �޴��� ���ư��� Ȯ��
int endOfCommand(void)
{
	char input[MAX_CHAR];
	int num = 0;

	while ((num != 1) && (num != 2)){
		fflush(stdin);
		printf("\n�ٽ� �޴��� ���ư��ڽ��ϱ�? (��: 1, �ƴϿ�: 2) : ");
		scanf("%s", input);

		num = inputCheck(input);
	}
	return num;
}