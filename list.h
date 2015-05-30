/********************************
	���α׷��� ���� in C

		�⸻ ������Ʈ

	����: ��ȭ��ȣ�� ���α׷�

		2015. 5. 30.

		����� (141013)

********************************/
#ifndef _LIST
#define _LIST

#include "Phonebook_setting.h"

typedef struct node {
	person_t data;
	struct node *next;
	struct node *prev;
} node_t;

typedef struct list {
	node_t *head;
} list_t;



// ���� ��� ���� �Լ�
void makeDummy();

// ��ü �޸� ���� �Լ�
void freeAll(list_t *phonelist);

// �޴� ���� �Լ�
void showMenu();
int inputChoice();

// ���� �ҷ����� �Լ�
list_t* fileOpen(list_t *phonelist);
int isPhoneBookEmpty(char buf[]);
void insertFromBufferToNode(node_t* curNode, char buffer[]);

// �Է� ���� �Լ�
char* removeSpace(char temp[]);
node_t* inputData(void);
void nameInput(node_t *input);
void phoneInput(node_t *input);
void nicknameInput(node_t *input);
void insertNode(list_t *phonelist, node_t *record);

// ȭ�� ��� ���� �Լ�
void showPerson(node_t *input);
void printPerson(node_t *curNode);
void showAllPerson(list_t *phonelist);

// ���� �Լ�
void deleteNode(list_t *phonelist);

// ���� �Լ�
void updateNode(list_t *phonelist);

// �˻� ���� �Լ�
int searchOption(int num);
int inputCheck(char input[]);
node_t* searchNode(list_t *phonelist);

// ���� ���� �Լ�
void filePrint(list_t *phonelist);

// �޴� �ǵ��ư��� �Լ�
int endOfCommand(void);

#endif