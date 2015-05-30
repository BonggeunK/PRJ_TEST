/********************************
	���α׷��� ���� in C

		�⸻ ������Ʈ
	
	����: ��ȭ��ȣ�� ���α׷�

		2015. 5. 30.

		����� (141013)

********************************/
#ifndef _PHONE_BOOK
#define _PHONE_BOOK

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 20
#define MAX_PHONE_NUMBER 30
#define MAX_SAVED_CHARACTER_PER_RECORD 70

typedef struct person{

	char name[MAX_CHAR];
	char phone[MAX_PHONE_NUMBER];
	char nickName[MAX_CHAR];

} person_t;


enum { OPEN = 0, INSERT, DELETE, SEARCH, UPDATE, PRINT, FILESAVE, EXIT };


#endif