/**
 * Luong Duc Duong
 * 27/03/2020
 *
 * C_advance
 * phoneBook.h
 */

#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#include <stdio.h>
#include <stdlib.h>
#include "entry.h"

int getChoose(int max);
Entry makePhone(void *name, void *phone);
int comparePhone(void *key1, void *key2);
void printMenu(void);
void createOrGetInfo(SymbolTable *book);
void addPhone(SymbolTable *book);
void getPhone(SymbolTable book);
void dropPhoneBook(SymbolTable *book);


int getChoose(int max) {
    int choose = 0;
    printf("Enter number : ");
    do {
        scanf("%d", &choose); getchar();
        if (choose < 1 || choose > max) {
            printf("(!) Your choose must bigger than 0\n");
            printf("    and smaller than %d\n\n", max + 1);
            printf("Re Enter number : ");
        }
    } while (max < choose || choose < 1);
    return choose;
}
void printMenu() {
	printf("\nMENU :\n");
	printf("1. Create Phone Book or get info Phone Book.\n");
	printf("2. Add phone number.\n");
	printf("3. Get phone number.\n");
	printf("4. Drop Phone Book.\n");
    printf("5. Exit.\n");
    printf("\n? which one do you want to choose ?\n");
}

Entry makePhone(void *name, void *phone) {
	Entry res;
	res.key = strdup((char *) name);
	res.value = (long *) malloc(sizeof(long));
	memcpy(res.value, phone, sizeof(long));
	return res;
}
int comparePhone(void *key1, void *key2) {
	return strcmp((char *) key1, (char *) key2);
}

void createOrGetInfo(SymbolTable *book) {
	printf("\n");
	if (book->entries == NULL) {
		printf("** Creating phone book ...\n");
		*book = createSymbolTable(makePhone, comparePhone);
		printf("** Create phone book successed !\n");
	}
	printf(" - Total element     : %d\n", book->total);
	printf(" - Size PhoneEntries : %d\n", book->size);
}
void addPhone(SymbolTable *book) {
	printf("\n");
    if (book->entries == NULL) {
        printf("Phone Book 's entriesPointer now is NULL\n");
        printf("(!) You have choose <1. Create Phone Book> first\n");
        printf("     to choose <2. Add phone>\n");
        return;
    }
	printf("How many phones do you want to add ?\n");
    int number = getChoose(9999999);
	printf("** Enter data to import phone book\n\n");
	for (int i = 0; i < number; i++) {
		printf("Data %d:\n", i + 1);
		printf(" - Enter name : "); char name[80] = "\0";
		scanf("%79[^\n]s", name); getchar();
		printf(" - Enter phone : "); long number;
		scanf("%ld", &number); getchar();
		addEntry(name, &number, book);
	}
	insertionSort(book);
}
void getPhone(SymbolTable book) {
	printf("\n");
	printf("Enter name to get number : ");
	char name[80] = "\0";
	scanf("%79[^\n]s", name); getchar();
	Entry* target = getEntry(name, book, 0, book.total);
	if (target == NULL) 
		printf("[!] Cannot find name you type in.\n");
	else 
		printf("** Number : %ld\n", *(long *)(target->value));
}
void dropPhoneBook(SymbolTable *book) {
	printf("\n");
	dropSymbolTable(book);
	printf(" - Total element     : %d\n", book->total);
    printf(" - Size PhoneEntries : %d\n", book->size);
}
#endif /* phoneBook.h */


