/********************************
	���α׷��� ���� in C
	
		�⸻ ������Ʈ
	
	����: ��ȭ��ȣ�� ���α׷�
	
		2015. 5. 30.

		����� (141013)

********************************/
#include "list.h"

// ���� ��� ����
node_t *dummy;

// count �ʱ�ȭ
int count = 0;


int main()
{
	node_t *record;
	list_t *phonelist;
	int choice, goOrStop;
	

	// ���� ��带 ���� circular ���� linked list ����
	makeDummy();

	// ��� �ʱ�ȭ
	phonelist = (list_t *)malloc(sizeof(list_t));
	phonelist->head = dummy;


	// �޴� ����
	while (1){
		
		system("cls");
		showMenu();
		choice = inputChoice();
		
		if ((count == 0) && ((choice == DELETE) || (choice == SEARCH) || (choice == UPDATE) || (choice == FILESAVE) || (choice == PRINT)))
			printf("\n��ȭ��ȣ�ΰ� ��� �ֽ��ϴ�. �ٸ� �Է��� �ʿ��մϴ�.");
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

	// ��ü �޸� ����
	freeAll(phonelist);
	
	return 0;
}