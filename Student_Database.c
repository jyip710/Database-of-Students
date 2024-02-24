#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Program 4: Database of Students
Course: CS 211, Spring 2023, UIC
System: Windows, VSCode
Author: Jacky Yip
*/

typedef struct {
	char* name;
	char* id;
	double gpa;
	int creditHours;
} Student;

typedef struct StudentNode{
	Student* pStudent;
	struct StudentNode* pNext;
} StudentNode;

typedef struct {
	StudentNode* pIDList;
	StudentNode* pHonorRollList;
	StudentNode* pAcademicProbationList;
	StudentNode* pFreshmanList;
	StudentNode* pSophomoreList;
	StudentNode* pJuniorList;
	StudentNode* pSeniorList;
} Database;

void appendStudentId(StudentNode **head, char* name[], char* id[], double gpa[], int creditHours[], Student **info){
	StudentNode *newNode = (StudentNode*)malloc(sizeof(StudentNode));
	Student* newStudent = (Student*)malloc(sizeof(Student));
	StudentNode *pTemp = *head;

	newStudent->name = *name;
	newStudent->id = *id;
	newStudent->gpa = *gpa;
	newStudent->creditHours = *creditHours;

	(*info)->name = newStudent->name;
	(*info)->id = newStudent->id;
	(*info)->gpa = newStudent->gpa;
	(*info)->creditHours = newStudent->creditHours;

	newNode->pStudent = *info;
	newNode->pNext = NULL;

	if(*head == NULL){
		*head = newNode;
	}
	else{
		while(pTemp->pNext != NULL && (strcmp(*id, pTemp->pNext->pStudent->id) > 0)){ //string compare in while
			pTemp = pTemp->pNext;
		}

		if(strcmp(*id, (*head)->pStudent->id) < 0){
			newNode->pNext = *head;
			*head = newNode;
		}
		else{
			newNode->pNext = pTemp->pNext; //(insert and/or append)
			pTemp->pNext = newNode;
		}
	}
}

void appendStudentName(StudentNode **head, Student **info){
	StudentNode *newNode = (StudentNode*)malloc(sizeof(StudentNode));
	StudentNode *pTemp = *head;

	newNode->pStudent = *info;
	newNode->pNext = NULL;

	if(*head == NULL){
		*head = newNode;
	}
	else{
		while(pTemp->pNext != NULL && (strcmp((*info)->name, pTemp->pNext->pStudent->name) > 0)){ //string compare in while
			pTemp = pTemp->pNext;
		}

		if(strcmp((*info)->name, (*head)->pStudent->name) < 0){
			newNode->pNext = *head;
			*head = newNode;
		}
		else{
			newNode->pNext = pTemp->pNext; //(insert and/or append)
			pTemp->pNext = newNode;
		}
	}
}

void appendStudentGpa(StudentNode **head, Student **info){
	StudentNode *newNode = (StudentNode*)malloc(sizeof(StudentNode));
	StudentNode *pTemp = *head;

	newNode->pStudent = *info;
	newNode->pNext = NULL;

	if(*head == NULL){
		*head = newNode;
	}
	else{
		while(pTemp->pNext != NULL && (**info).gpa > pTemp->pNext->pStudent->gpa){ //string compare in while
			pTemp = pTemp->pNext;
		}

		if((**info).gpa < (*head)->pStudent->gpa){
			newNode->pNext = *head;
			*head = newNode;
		}
		else{
			newNode->pNext = pTemp->pNext; //(insert and/or append)
			pTemp->pNext = newNode;
		}
	}
}

void printList(StudentNode *node){
	if(node == NULL){
		printf("There are no students matching that criteria.\n\n");
	}
	while(node != NULL){
		printf("%s: \n\tID - %s\n\tGPA - %.2f\n\tCredit Hours - %d\n\n",node->pStudent->name, node->pStudent->id, node->pStudent->gpa, node->pStudent->creditHours);
		node = node->pNext;
	}
}

void printList10(StudentNode *node, int size){
	for(int i = 0; i < size; i++){
		if(i == 10){
			return;
		}
		printf("%s: \n\tID - %s\n\tGPA - %.2f\n\tCredit Hours - %d\n\n",node->pStudent->name, node->pStudent->id, node->pStudent->gpa, node->pStudent->creditHours);
		node = node->pNext;
	}
}

void createStudentDatabase(Database **head, char* name[], char* id[], double gpa[], int creditHours[], int size){
	StudentNode* idList = NULL;
	StudentNode* honorList = NULL;
	StudentNode* probationList = NULL;
	StudentNode* freshmanList = NULL;
	StudentNode* sophomoreList = NULL;
	StudentNode* juniorList = NULL;
	StudentNode* seniorList = NULL;
	
	for(int i = 0; i < size; i++){
		Student *data = (Student*)malloc(sizeof(Student));
		appendStudentId(&idList,  &name[i], &id[i], &gpa[i], &creditHours[i], &data);

		if(gpa[i] >= 3.50){
			appendStudentGpa(&honorList, &data);
		}

		if(gpa[i] < 2.00){
			appendStudentGpa(&probationList, &data);
		}

		if(creditHours[i] <= 29){
			appendStudentName(&freshmanList, &data);
		}

		if(creditHours[i] >= 30 && creditHours[i] <= 59){
			appendStudentName(&sophomoreList, &data);
		}

		if(creditHours[i] >= 60 && creditHours[i] <= 89){
			appendStudentName(&juniorList, &data);
		}

		if(creditHours[i] >= 90){
			appendStudentName(&seniorList, &data);
		}

		// printf("%s\n",newList->pStudent->id);
		// newList = newList->pNext;
	}
	(*head)->pIDList = idList;
	(*head)->pHonorRollList = honorList;
	(*head)->pAcademicProbationList = probationList;
	(*head)->pFreshmanList = freshmanList;
	(*head)->pSophomoreList = sophomoreList;
	(*head)->pJuniorList = juniorList;
	(*head)->pSeniorList = seniorList;
	// printList(*head);
}

void findID(char* toFind[], StudentNode *list){
	while(list != NULL){
		if(strcmp(*toFind,list->pStudent->id) == 0){
			printf("%s:\n\tID - %s\n\tGPA - %.2f\n\tCredit Hours - %d\n\n",list->pStudent->name, list->pStudent->id, list->pStudent->gpa, list->pStudent->creditHours);
			return;
		}
		list = list->pNext;
	}
	printf("Sorry, there is no student in the database with the id %s.\n\n",*toFind);
}

int inList(char* toFind[], StudentNode *list){
	while(list != NULL){
		if(strcmp(*toFind,list->pStudent->id) == 0){
			return 1;
		}
		list = list->pNext;
	}
}

void deleteStudent(StudentNode **list, char* toFind[]){
	StudentNode *prev = NULL;
	StudentNode *nodeToDelete = *list;

	while(nodeToDelete != NULL && (strcmp(*toFind,nodeToDelete->pStudent->id) != 0)){
		prev = nodeToDelete;
		nodeToDelete = nodeToDelete->pNext;
	}

	if(nodeToDelete == *list){
		*list = (*list)->pNext;
		free(nodeToDelete);
	}
	else{
		prev->pNext = nodeToDelete->pNext;
		free(nodeToDelete);
	}
}

void freeNodes(StudentNode *pHead){
	StudentNode *pTemp = pHead;
	StudentNode *curr;

	while(pTemp != NULL){
		curr = pTemp;
		pTemp = pTemp->pNext;
		free(curr);
	}
}

int main() {
	char fileContents[500][1000];
	Database* studentsList = (Database*)malloc(sizeof(Database));

	char *names[1000];
	char *id[1000];
	char *gpa[1000];
	char *creditHours[1000];
	int listTracker = 0;

	double gpaNum[1000];
	int creditHoursNum[1000];

	studentsList->pIDList = NULL;
	studentsList->pHonorRollList = NULL;
	studentsList->pAcademicProbationList = NULL;
	studentsList->pFreshmanList = NULL;
	studentsList->pSophomoreList = NULL;
	studentsList->pJuniorList = NULL;
	studentsList->pSeniorList = NULL;

	printf("CS 211, Spring 2023\n");
	printf("Program 4: Database of Students\n\n");

	printf("Enter E to start with an empty database, \n");
	printf("or F to start with a database that has information on students from a file.\n");
	int firstMenu = 1;

	while(firstMenu != 0){
		printf("Your choice --> ");
		char firstChoice;
		scanf("%s", &firstChoice);
		if(firstChoice == 'E'){
			firstMenu = 0;
		}
		else if(firstChoice == 'F'){
			printf("Enter the name of the file you would like to use: ");
			char fileName[81];
			scanf("%s", fileName);
			FILE *file;
			file = fopen(fileName, "r");

			if(file == NULL){
				printf("Error opening file.\n");
			}

			int index = 0;

			while(!feof(file)){
				if(fgets(fileContents[index],1000,file) != NULL){
					index++;
				}
			}
			fclose(file);

			int countString = 0;
			for(int i = 1; i < index; i++){
				char *pt;
				int ptIndex = 0;
				pt = strtok(fileContents[i],",");

				while(pt != NULL){
					if(ptIndex == 0){
						names[listTracker] = pt;
						pt = strtok(NULL,",");
						ptIndex++;
					}
					else if(ptIndex == 1){
						id[listTracker] = pt;
						pt = strtok(NULL,",");
						ptIndex++;
					}
					else if(ptIndex == 2){
						gpa[listTracker] = pt;
						pt = strtok(NULL,",");
						ptIndex++;
					}
					else if(ptIndex == 3){
						creditHours[listTracker] = pt;
						pt = strtok(NULL,",");
					}
				}
				listTracker++;
			}

			for(int i = 0; i < listTracker; i++){
				char *pt;
				pt = strtok(creditHours[i],"\n");

				while(pt != NULL){
					creditHours[i] = pt;
					pt = strtok(NULL,"\n");
				}
			}
			for(int i = 0; i < listTracker; i++){
				double val = strtod(gpa[i], NULL);
				gpaNum[i] = val;
			}
			
			char *end;
			for(int i = 0; i < listTracker; i++){
				int val = strtol(creditHours[i], &end, 10);
				creditHoursNum[i] = val;
			}

			//Creates Student ID list
			createStudentDatabase(&studentsList, names, id, gpaNum, creditHoursNum, listTracker);

			firstMenu = 0;
		}
		else{
			printf("Sorry, that input was invalid. Please try again.\n");
		}
	}
	int continueProgram = 1;
	while(continueProgram != 0){
		printf("\nEnter: \tC to create a new student and add them to the database,\n");
		printf("\tR to read from the database,\n");
		printf("\tD to delete a student from the database, or\n");
		printf("\tX to exit the program.\n");
		printf("Your choice --> ");
		char secondChoice;
		scanf("%s", &secondChoice);
		getchar();

		if(secondChoice == 'C'){
			char *newName = malloc(sizeof(char)*1000);
			char *newId = malloc(sizeof(char)*1000);
			char *newGpa = malloc(sizeof(char)*1000);;
			char *newCreditHours = malloc(sizeof(char)*1000);

			double newGpaNum = 0;
			int newCreditHoursNum = 0;

			printf("Enter the name of the new student: ");
			fgets(newName, 1000, stdin);
			newName[strcspn(newName, "\n")] = 0;

			printf("Enter the ID of the new student: ");
			fgets(newId, 1000, stdin);
			newId[strcspn(newId, "\n")] = 0;
			// printf("%s\n",newId);

			printf("Enter the GPA of the new student: ");
			fgets(newGpa, 1000, stdin);
			newGpa[strcspn(newGpa, "\n")] = 0;

			printf("Enter the credit hours of the new student: ");
			fgets(newCreditHours, 1000, stdin);
			newCreditHours[strcspn(newCreditHours, "\n")] = 0;

			double val = strtod(newGpa, NULL);
			newGpaNum = val;

			char *end;
			int val2 = strtol(newCreditHours, &end, 10);
			newCreditHoursNum = val2;
			listTracker++;
			Student* newStudent = (Student*)malloc(sizeof(Student));

			//For ID list
			appendStudentId(&studentsList->pIDList, &newName, &newId, &newGpaNum, &newCreditHoursNum,&newStudent);

			//For honor roll
			if(newGpaNum >= 3.50){
				appendStudentGpa(&studentsList->pHonorRollList, &newStudent);
			}

			// //For probation
			if(newGpaNum < 2.00){
				appendStudentGpa(&studentsList->pAcademicProbationList, &newStudent);
			}

			// //For year
			if(newCreditHoursNum <= 29){
				appendStudentName(&studentsList->pFreshmanList, &newStudent);
			}
			else if(newCreditHoursNum >= 30 && newCreditHoursNum <= 59){
				appendStudentName(&studentsList->pSophomoreList, &newStudent);
			}
			else if(newCreditHoursNum >= 60 && newCreditHoursNum <= 89){
				appendStudentName(&studentsList->pJuniorList, &newStudent);
			}
			else if(newCreditHoursNum >= 90){
				appendStudentName(&studentsList->pSeniorList, &newStudent);
			}
			printf("Successfully added the following student to the database!\n");
			printf("%s:\n\tID - %s\n\tGPA - %.2f\n\tCredit Hours - %d\n\n",newName, newId, newGpaNum, newCreditHoursNum);
		}
		else if(secondChoice == 'R'){
			int inR = 1;
			printf("Select one of the following: \n");
			printf("\t1) Display the head (first 10 rows) of the database\n");
			printf("\t2) Display students on the honor roll, in order of their GPA\n");
			printf("\t3) Display students on academic probation, in order of their GPA\n");
			printf("\t4) Display freshmen students, in order of their name\n");
			printf("\t5) Display sophomore students, in order of their name\n");
			printf("\t6) Display junior students, in order of their name\n");
			printf("\t7) Display senior students, in order of their name\n");
			printf("\t8) Display the information of a particular student\n");
			
			while(inR != 0){
				printf("Your choice --> ");
				int rChoice;
				scanf("%d", &rChoice);
				getchar();

				if(rChoice == 1){
					printList10(studentsList->pIDList,listTracker);
					inR = 0;
				}
				else if(rChoice == 2){
					printList(studentsList->pHonorRollList);
					inR = 0;
				}
				else if(rChoice == 3){
					printList(studentsList->pAcademicProbationList);
					inR = 0;
				}
				else if(rChoice == 4){
					printList(studentsList->pFreshmanList);
					inR = 0;
				}
				else if(rChoice == 5){
					printList(studentsList->pSophomoreList);
					inR = 0;
				}
				else if(rChoice == 6){
					printList(studentsList->pJuniorList);
					inR = 0;
				}
				else if(rChoice == 7){
					printList(studentsList->pSeniorList);
					inR = 0;
				}
				else if(rChoice == 8){
					printf("Enter the id of the student to find: ");
					char *idToFind = malloc(sizeof(char)*1000);
					fgets(idToFind, 1000, stdin);
					idToFind[strcspn(idToFind, "\n")] = 0;

					findID(&idToFind,studentsList->pIDList);
					inR = 0;
				}
				else{
					printf("Sorry, that input was invalid. Please try again.\n");
				}
			}
		}
		else if(secondChoice == 'D'){
			printf("Enter the id of the student to be removed: ");
			char *idToFind = malloc(sizeof(char)*1000);
			fgets(idToFind, 1000, stdin);
			idToFind[strcspn(idToFind, "\n")] = 0;

			int listCheckId = inList(&idToFind,studentsList->pIDList);
			if(listCheckId != 1){
				printf("Sorry, there is no student in the database with the id %s.\n\n",idToFind);
			}

			int listCheckHonor = inList(&idToFind,studentsList->pHonorRollList);
			int listCheckFreshman = inList(&idToFind,studentsList->pFreshmanList);
			int listCheckProbation = inList(&idToFind,studentsList->pAcademicProbationList);
			int listCheckJunior = inList(&idToFind,studentsList->pJuniorList);
			int listCheckSenior = inList(&idToFind,studentsList->pSeniorList);
			int listCheckSophomore = inList(&idToFind,studentsList->pSophomoreList);

			if(listCheckId == 1){
				deleteStudent(&studentsList->pIDList,&idToFind);
				listTracker--;
			}
			if(listCheckHonor == 1){
				deleteStudent(&studentsList->pHonorRollList,&idToFind);
			}
			if(listCheckFreshman == 1){
				deleteStudent(&studentsList->pFreshmanList,&idToFind);
			}
			if(listCheckProbation == 1){
				deleteStudent(&studentsList->pAcademicProbationList,&idToFind);
			}
			if(listCheckJunior == 1){
				deleteStudent(&studentsList->pJuniorList,&idToFind);
			}
			if(listCheckSenior == 1){
				deleteStudent(&studentsList->pSeniorList,&idToFind);
			}
			if(listCheckSophomore == 1){
				deleteStudent(&studentsList->pSophomoreList,&idToFind);
			}
		}
		else if(secondChoice == 'X'){
			printf("\n");
			continueProgram = 0;
		}
		else{
			printf("Invalid option. Try again.\n");
		}
	}

	printf("Thanks for playing!\n");
	printf("Exiting...\n");

	freeNodes(studentsList->pAcademicProbationList);
	free(studentsList);
	
	return 0;
}