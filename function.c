/********************************
	프로그래밍 연습 in C

		기말 프로젝트

	주제: 전화번호부 프로그램

		2015. 5. 30.

		김봉근 (141013)

********************************/
#include "list.h"

extern node_t *dummy;
extern int count;


// 더미 노드 생성
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

// 메뉴 화면 출력
void showMenu()
{
	printf("┌━━━━━━━━━━━━━━━┐\n");
	printf("│                              │\n");
	printf("│      연락처 메뉴             │\n");
	printf("│                              │\n");
	printf("├━━━━━━━━━━━━━━━┤\n");
	printf("│    0. 연락처 파일 불러오기   │\n");
	printf("├━━━━━━━━━━━━━━━┤\n");
	printf("│    1. 연락처 추가            │\n");
	printf("├━━━━━━━━━━━━━━━┤\n");
	printf("│    2. 연락처 삭제            │\n");
	printf("├━━━━━━━━━━━━━━━┤\n");
	printf("│    3. 연락처 검색            │\n");
	printf("├━━━━━━━━━━━━━━━┤\n");
	printf("│    4. 연락처 수정            │\n");
	printf("├━━━━━━━━━━━━━━━┤\n");
	printf("│    5. 전체 연락처 보기       │\n");
	printf("├━━━━━━━━━━━━━━━┤\n");
	printf("│    6. 연락처 파일 저장       │\n");
	printf("├━━━━━━━━━━━━━━━┤\n");
	printf("│    7. 나가기                 │\n");
	printf("└━━━━━━━━━━━━━━━┘\n");
	printf("\n메뉴 번호를 입력하세요: ");
}


// 메뉴 화면에서 사용자 입력값 확인
int inputChoice()
{
	char input[MAX_CHAR];
	int num;

	while (1){
		fflush(stdin);
		scanf("%s", input);

		num = atoi(input);

		if (((strlen(input)) > 1) || (num < 0) || (num > 7))
			printf("\n잘못된 입력입니다. 다시 입력하세요: ");
		else
			return num;
	}
}


// 입력 내용에서 공백 없애기
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


// 파일 불러오기
list_t* fileOpen(list_t *phonelist)
{
	int state, readCount = 0;
	char *readRecord;
	char buffer[MAX_SAVED_CHARACTER_PER_RECORD];
	node_t *curNode, *nextNode;

	puts("\n현재 디렉토리에 있는 SIMPLEphoneBOOK.txt 로부터 연락처를 불러옵니다.");

	FILE *file = fopen("SIMPLEphoneBOOK.txt", "rt");

	if (file == NULL){
		puts("파일 불러오기에 실패했습니다.");
		return phonelist;
	}

	memset(buffer, 0, sizeof(buffer)); // 버퍼 초기화
	readRecord = fgets(buffer, sizeof(buffer), file);

	state = isPhoneBookEmpty(buffer);

	if (state == 1)				// 전화번호부 파일이 비어 있는 경우 리턴
		return phonelist;
	
	curNode = (node_t *)malloc(sizeof(node_t));
			
	while (1){

		readCount++;
		insertFromBufferToNode(curNode, buffer);

		if (readCount == 1){ // 맨 처음 입력되는 노드인 경우
			dummy->next = curNode;
			curNode->prev = dummy;
		}

		memset(buffer, 0, sizeof(buffer));
		readRecord = fgets(buffer, sizeof(buffer), file);

		if (readRecord != NULL){ // 뒤에 입력될 내용이 있는 경우
						
			nextNode = (node_t *)malloc(sizeof(node_t));
			curNode->next = nextNode;
			nextNode->prev = curNode;
			curNode = nextNode;
		
		} else{  // 더 이상 입력될 연락처 정보가 없는 경우
			curNode->next = dummy;
			dummy->prev = curNode;
			
			break;
		}
	}

	state = fclose(file);
	if (state != 0)
		puts("불러온 파일 닫기에 실패했습니다.");

	return phonelist;
}


// 전화번호부 파일이 비어 있는지 확인
int isPhoneBookEmpty(char buf[])
{
	char *ptr;

	ptr = buf;

	if (*ptr == '\n'){
		puts("\nSIMPLEphoneBOOK.txt 파일이 비어 있습니다.\n");
		return 1;
	}
	return 0;
}


// 버퍼의 데이터를 노드로 삽입하기
void insertFromBufferToNode(node_t* curNode, char buffer[])
{
	char *ptr, *token, *endOfString;
	char record[MAX_SAVED_CHARACTER_PER_RECORD];
	char *tempString;
	int i = 0, j = 1;

	ptr = buffer;
	token = strstr(buffer, " │ ");
	endOfString = strstr(buffer, "\n");

	while (*ptr != '\0'){

		record[i] = *ptr;

		if (ptr == token){

			record[i] = '\0';

			if (j == 1){ // 노드 데이터의 이름에 입력
				tempString = removeSpace(record);
				strcpy(curNode->data.name, tempString);
				j = 2;
			}
			else { // 노드 데이터의 전화번호에 입력
				tempString = removeSpace(record);
				strcpy(curNode->data.phone, tempString);
				j = 1;
			}

			i = 0;
			ptr += strlen(" │ ");
			token = strstr(ptr, " │ ");

		}
		else if (ptr == endOfString){

			record[i] = '\0';
			tempString = removeSpace(record);
			strcpy(curNode->data.nickName, tempString);	// 노드 데이터의 별명에 입력

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
	dataToken = strstr(buffer, " │ ");

	// 더미 노드에 연결되는 첫 번째 노드로 입력
	curNode = (node_t *)malloc(sizeof(node_t));
	phonelist->head->next = curNode;
	curNode->prev = phonelist->head;
	count++;

	while (*ptr != 1){
		
		record[i] = *ptr;

		if (ptr == dataToken){

			record[i] = '\0';

			if (j == 1){ // 노드 데이터의 이름에 입력
				tempString = removeSpace(record);
				strcpy(curNode->data.name, tempString);
				j = 2;
			} else { // 노드 데이터의 전화번호에 입력
				tempString = removeSpace(record);
				strcpy(curNode->data.phone, tempString);
				j = 1;
			}

			i = 0;
			ptr += strlen(" │ ");
			dataToken = strstr(ptr, " │ ");

		} else if (ptr == personToken){

			record[i] = '\0';
			tempString = removeSpace(record);
			strcpy(curNode->data.nickName, tempString);	// 노드 데이터의 별명에 입력

			i = 0;
			ptr++;
			personToken = strstr(ptr, "\n");

			if (personToken != NULL){ // 뒤에 더 입력될 연락처 정보가 있는 경우

				nextNode = (node_t *)malloc(sizeof(node_t));
				curNode->next = nextNode;
				nextNode->prev = curNode;
				curNode = nextNode;

				count++;

			} else {	// 더 이상 입력될 연락처 정보가 없는 경우
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


// 콘솔에서 데이터 입력받기
node_t* inputData(void)
{
	node_t *input;

	input = (node_t *)malloc(sizeof(node_t));

	nameInput(input); // 이름 입력
	phoneInput(input); // 전화번호 입력
	nicknameInput(input); // 별명 입력

	showPerson(input); // 입력받은 내용 출력
	
	count++;

	return input;
}

// 이름 입력
void nameInput(node_t *input)
{
	char tempName[MAX_CHAR], *personName;

	fflush(stdin);
	printf("\n이름 : ");
	fgets(tempName, sizeof(tempName), stdin);
	tempName[strlen(tempName) - 1] = '\0';
	personName = removeSpace(tempName);
	strcpy(input->data.name, personName);
}

// 전화번호 입력
void phoneInput(node_t *input)
{
	char *phoneNumber, tempNumber[MAX_PHONE_NUMBER];
	int i = 0;

	do {
		fflush(stdin);
		printf("전화번호 : ");
		fgets(tempNumber, sizeof(tempNumber), stdin);
		tempNumber[strlen(tempNumber) - 1] = '\0';
		phoneNumber = removeSpace(tempNumber);

		while (i < (int)strlen(phoneNumber)){
			if (((phoneNumber[i] >= '0') && (phoneNumber[i] <= '9')) || (phoneNumber[i] == '-'))
				i++;
			else{	 // 전화번호에 문자가 포함된 경우, 재입력 요구
				printf("\n전화번호는 숫자와 -만 입력할 수 있습니다.\n");
				printf("전화번호를 다시 입력하세요.\n\n");
				i = 0;
				break;
			}
		}
	} while (i < (int)strlen(phoneNumber));

	strcpy(input->data.phone, phoneNumber);
}

// 별명 입력
void nicknameInput(node_t *input)
{
	char tempName[MAX_CHAR], *personNickname;

	fflush(stdin);
	printf("별명 : ");
	fgets(tempName, sizeof(tempName), stdin);
	tempName[strlen(tempName) - 1] = '\0';
	personNickname = removeSpace(tempName);
	strcpy(input->data.nickName, personNickname);
}

// 방금 입력한 내용 출력
void showPerson(node_t *input)
{
	printf("\n입력된 연락처: %s\t%s\t%s\n", input->data.name, input->data.phone, input->data.nickName);
}


// 입력된 내용을 전화번호부에 노드로 추가
void insertNode(list_t *phonelist, node_t *record)
{
	if (dummy->next == dummy)	// 맨 처음 입력인 경우
		dummy->next = record;
	else
		dummy->prev->next = record;

	record->prev = dummy->prev;
	record->next = dummy;
	dummy->prev = record;

	return;
}


// 전화번호부에서 노드 삭제
void deleteNode(list_t *phonelist)
{
	node_t *curNode;

	printf("\n삭제할 연락처를 검색합니다.\n\n");

	curNode = searchNode(phonelist);

	if (curNode != NULL){
		curNode->next->prev = curNode->prev;
		curNode->prev->next = curNode->next;
		free(curNode);
		count--;
		printf("\n검색된 연락처가 삭제되었습니다.\n\n");
	}
}

// 검색 옵션 (이름/전화번호 검색)
int searchOption(int num)
{
	char input[MAX_CHAR];

	while ((num != 1) && (num != 2)){
		fflush(stdin);
		printf("\n이름으로 검색하시겠습니까? 전화번호로 검색하시겠습니까?\n");
		printf("(이름 검색 = 1, 전화번호 검색 = 2): ");
		scanf("%s", input);

		num = inputCheck(input);
	}
	return num;
}

// 숫자 1, 2 외에 잘못된 입력 확인
int inputCheck(char input[])
{
	int num;

	num = atoi(input);

	if (((strlen(input)) > 1) || (num < 1) || (num > 2))
		printf("\n잘못된 입력입니다.\n");
	return num;
}

// 노드의 연락처를 출력
void printPerson(node_t *curNode)
{
	printf("\n이름: %s\n", curNode->data.name);
	printf("전화번호: %s\n", curNode->data.phone);
	printf("별명: %s\n\n", curNode->data.nickName);
}


// 연락처 검색
node_t* searchNode(list_t *phonelist)
{
	int num = 0;
	char tempName[MAX_CHAR], *personName;
	char tempNumber[MAX_PHONE_NUMBER], *personPhone;
	node_t *curNode;

	num = searchOption(num);

	curNode = phonelist->head->next;

	if (num == 1){	// 이름으로 검색
		fflush(stdin);
		printf("\n검색할 이름: ");
		fgets(tempName, sizeof(tempName), stdin);
		tempName[strlen(tempName) - 1] = '\0';
		personName = removeSpace(tempName);

		while (strcmp(curNode->data.name, personName)){
			curNode = curNode->next;
			if (curNode == dummy){
				printf("\n입력한 사람의 연락처가 존재하지 않습니다.\n");
				return (node_t*)NULL;
			}
		}
		printPerson(curNode);
		return curNode;

	}
	else{	// 전화번호로 검색
		fflush(stdin);
		printf("\n검색할 전화번호: ");
		fgets(tempNumber, sizeof(tempNumber), stdin);
		tempNumber[strlen(tempNumber) - 1] = '\0';
		personPhone = removeSpace(tempNumber);

		while (strcmp(curNode->data.phone, personPhone)){
			curNode = curNode->next;
			if (curNode == dummy){
				printf("\n입력한 전화번호가 존재하지 않습니다.\n");
				return (node_t*)NULL;
			}
		}
		printPerson(curNode);
		return curNode;
	}
}


// 연락처 수정
void updateNode(list_t *phonelist)
{
	node_t *curNode;

	printf("\n수정할 연락처를 검색합니다.\n\n");

	curNode = searchNode(phonelist);

	if (curNode != NULL){
		printf("\n연락처를 수정합니다.\n\n");
		nameInput(curNode);
		phoneInput(curNode);
		nicknameInput(curNode);
		printf("\n수정된 연락처로 저장되었습니다.\n\n");
	}
}


// 전체 연락처 출력
void showAllPerson(list_t *phonelist)
{
	node_t *curNode;
	int i = 0;

	curNode = phonelist->head->next;

	puts("━━━━━━━━━━━━━━━━━━━━━━━\n");
	puts("     이름         ☏ 전화번호        별명\n");
	puts("━━━━━━━━━━━━━━━━━━━━━━━\n");
	while (curNode != dummy){
		printf("%10s │ %16s │ %8s\n", curNode->data.name, curNode->data.phone, curNode->data.nickName);
		curNode = curNode->next;
		i++;
	}
	puts("━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("\n\t\t이상 %d명\n", i);
}


// 파일로 저장
void filePrint(list_t *phonelist)
{
	node_t *curNode;
	int state;

	FILE *file = fopen("SIMPLEphoneBOOK.txt", "wt");

	if (file == NULL){
		puts("파일 저장에 실패했습니다.");
		return;
	}

	curNode = phonelist->head->next;

	while (curNode != dummy){
		fprintf(file, "%10s │ %16s │ %8s\n", curNode->data.name, curNode->data.phone, curNode->data.nickName);
		curNode = curNode->next;
	}

	puts("\n전화번호부가 SIMPLEphoneBOOK.txt 파일로 저장되었습니다.");

	state = fclose(file);
	if (state != 0)
		puts("저장한 파일 닫기에 실패했습니다.");
}


// 한 번 실행 완료된 후, 다시 메뉴로 돌아갈지 확인
int endOfCommand(void)
{
	char input[MAX_CHAR];
	int num = 0;

	while ((num != 1) && (num != 2)){
		fflush(stdin);
		printf("\n다시 메뉴로 돌아가겠습니까? (예: 1, 아니오: 2) : ");
		scanf("%s", input);

		num = inputCheck(input);
	}
	return num;
}