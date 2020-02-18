#include "main.h"
#include <stdio.h>

int main() {
	SymbolTable book;
	book.entries = NULL;
MENU:
	printMenu();
	printf("Enter number to choose : ");
	int choose = 0;
	scanf("%d", &choose); getchar();
	switch(choose) {
		case 1: {
			createOrGetData(book);
			break;
		}
		case 2: {
			addPhone(book);
			break;
		}
		case 3: {
			getPhone(book);
			break;
		}
		default: {
			dropPhoneBook(book);
			return 0;
		}
	}
	goto MENU;
}

