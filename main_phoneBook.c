/********************************
	프로그래밍 연습 in C
	
		기말 프로젝트
	
	주제: 전화번호부 프로그램
	
		2015. 5. 30.

		김봉근 (141013)

********************************/
#include "list.h"

// 더미 노드 선언
node_t *dummy;

// count 초기화
int count = 0;


int main()
{
	node_t *record;
	list_t *phonelist;
	int choice, goOrStop;
	

	// 더미 노드를 가진 circular 더블 linked list 생성
	makeDummy();

	// 헤드 초기화
	phonelist = (list_t *)malloc(sizeof(list_t));
	phonelist->head = dummy;


	// 메뉴 실행
	while (1){
		
		system("cls");
		showMenu();
		choice = inputChoice();
		
		if ((count == 0) && ((choice == DELETE) || (choice == SEARCH) || (choice == UPDATE) || (choice == FILESAVE) || (choice == PRINT)))
			printf("\n전화번호부가 비어 있습니다. 다른 입력이 필요합니다.");
		else{
			switch (choice){

				case OPEN:
					phonelist = fileOpen(phonelist);
					break;
					
				case INSERT:
					record = inputData();
					insertNode(phonelist, record);
					break;

				case DELETE:
					deleteNode(phonelist);				
					break;

				case SEARCH:
					record = searchNode(phonelist);
					break;

				case UPDATE:
					updateNode(phonelist);
					break;

				case PRINT:
					showAllPerson(phonelist);
					break;

				case FILESAVE:
					filePrint(phonelist);
					break;

				case EXIT:
					break;
				}

			if (choice == EXIT)
				break;
		}
		
		goOrStop = endOfCommand();
		if (goOrStop == 2) break;
	}

	// 전체 메모리 해제
	freeAll(phonelist);
	
	return 0;
}