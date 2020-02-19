//
//  main.c
//  Phone Book
//
//  Created by Lương Dương on 2/18/20.
//  Copyright © 2020 Lương Dương. All rights reserved.
//

#include "main.h"
#include <stdio.h>

int main() {
    SymbolTable book;
    book.entries = NULL;
MENU:
    printMenu();
    int choose = getChoose(5);
    switch(choose) {
        case 1: {
            createOrGetData(&book);
            break;
        }
        case 2: {
            addPhone(&book);
            break;
        }
        case 3: {
            getPhone(book);
            break;
        }
        case 4: {
            dropPhoneBook(&book);
            break;
        }
        default: {
            printf("\n");
            if (book.entries != NULL) {
                printf("(!) Phone Book 's entries_Pointer is different from NULL\n");
                printf(" -  You must be obliged to drop Phone Book before.\n");
                goto MENU;
            }
            printf("**Exit   \n");
            printf("This program made by Luong Duc Duong\n\n");
            return 0;
        }
    }
    goto MENU;
}
