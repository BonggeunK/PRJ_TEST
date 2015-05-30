/********************************
	프로그래밍 연습 in C

		기말 프로젝트

	주제: 전화번호부 프로그램

		2015. 5. 30.

		김봉근 (141013)

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



// 더미 노드 생성 함수
void makeDummy();

// 전체 메모리 해제 함수
void freeAll(list_t *phonelist);

// 메뉴 관련 함수
void showMenu();
int inputChoice();

// 파일 불러오기 함수
list_t* fileOpen(list_t *phonelist);
int isPhoneBookEmpty(char buf[]);
void insertFromBufferToNode(node_t* curNode, char buffer[]);

// 입력 관련 함수
char* removeSpace(char temp[]);
node_t* inputData(void);
void nameInput(node_t *input);
void phoneInput(node_t *input);
void nicknameInput(node_t *input);
void insertNode(list_t *phonelist, node_t *record);

// 화면 출력 관련 함수
void showPerson(node_t *input);
void printPerson(node_t *curNode);
void showAllPerson(list_t *phonelist);

// 삭제 함수
void deleteNode(list_t *phonelist);

// 수정 함수
void updateNode(list_t *phonelist);

// 검색 관련 함수
int searchOption(int num);
int inputCheck(char input[]);
node_t* searchNode(list_t *phonelist);

// 파일 저장 함수
void filePrint(list_t *phonelist);

// 메뉴 되돌아가기 함수
int endOfCommand(void);

#endif