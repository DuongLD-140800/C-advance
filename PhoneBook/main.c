#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
//Hello cac ban
int main() {
	PhoneBook book;
	book.entries = NULL;
MENU:
	printf("\nMENU :\n");
	printf("1. Create Phone Book or get info Phone Book.\n");
	printf("2. Add phone number.\n");
	printf("3. Get phone number.\n");
	printf("4. Drop Phone Book and Quit.\n");

	printf("Enter number to choose : ");
	int choose = 0;
	scanf("%d", &choose); getchar();

	switch(choose) {
		case 1: {
			printf("\n");
			if (book.entries == NULL) {
				printf("** Creating phone book ...\n");
				book = createPhoneBook();
				printf("** Create phone book successed !\n");
			}
			printf(" - Total element     : %d\n", book.total);
			printf(" - Size PhoneEntries : %d\n", book.size);
			break;
		}
		case 2: {
			printf("\n");
			printf("Enter numbers to add : ");
			int number = 0; scanf("%d", &number); getchar();
			printf("** Enter data to import phone book\n\n");
			for (int i = 0; i < number; i++) {
				printf("Data %d:\n", i + 1);
				PhoneEntry userData = getUserData();
				addPhoneNumber(userData.name, userData.number, &book);
			}
			break;
		}
		case 3: {
			printf("\n");
			printf("Enter name to get number : ");
			char name[80] = "\0";
			scanf("%79[^\n]s", name); getchar();
			PhoneEntry* target = getPhoneNumber(name, book);
			if (target == NULL) 
				printf("[!] Cannot find name you type in.\n");
			else 
				printf("** Number : %ld\n", target->number);
			break;
		}
		default: {
			printf("\n");
			dropPhoneBook(&book);
			printf("Drop phone book successed !\n");
			printf("Exit programs\n");
			return 0;
		}
	}
	goto MENU;
}

