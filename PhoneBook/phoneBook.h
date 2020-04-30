/**
 * 27/03/2020
 * Luong Duc Duong
 * 
 * C_advance
 * phoneBook.h
 */

#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H


#define INITIAL_SIZE 10 
#define INCREMENTAL_SIZE 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { 
	char name[80]; 
	long number;
} PhoneEntry;

typedef struct { 
	PhoneEntry *entries;
	int total;
	int size;
} PhoneBook;

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook *book);
void addPhoneNumber(char *name, long number, PhoneBook *book);
PhoneEntry* getPhoneNumber(char *name, PhoneBook book);

PhoneEntry getUserData() {
	PhoneEntry userData;
	printf(" - Enter name : ");
	scanf("%79[^\n]s", userData.name); getchar();
	printf(" - Enter phone : ");
	scanf("%ld", &userData.number); getchar();
	return userData;
}
/**
 * create new array with struct PhoneBook & size = INITIAL_SIZE by malloc()
 * @return address of new array
 */
PhoneBook createPhoneBook() {
	PhoneBook newPb;
	newPb.total = 0;
	newPb.size = INITIAL_SIZE;
	newPb.entries = (PhoneEntry *) malloc(newPb.size * sizeof(PhoneEntry));
	if (newPb.entries == NULL) {
		printf("Malloc failed!\n");
		exit(1);
	}
	return newPb;
}
/**
 * drop array *entries in book
 * @param book PhoneBook*
 */
void dropPhoneBook(PhoneBook* book) {
	if (book->entries != NULL)
		free(book->entries);
}
/**
 * find in book with key
 * @param  name char* (key)
 * @param  book PhoneBook
 * @return      address of key
 */
PhoneEntry* getPhoneNumber(char * name, PhoneBook book) {
	for (int i = 0; i < book.total; i++) {
		if (strcmp(name, book.entries[i].name) == 0)
			return (book.entries + i);
	}
	return NULL;
}
/**
 * re Allocate memory for book with size increased by INCREMENTAL_SIZE
 * @param book PhoneBook*
 */
void reAllocPb(PhoneBook *book) {
	book->entries = (PhoneEntry *) 
						realloc(book->entries,
							(book->size += INCREMENTAL_SIZE) * sizeof(PhoneEntry));
	if (book->entries == NULL) {
		printf("Realloc failed!\n");
		exit(2);
	}
}
/**
 * add new entry to book
 * @param name   char*
 * @param number long
 * @param book   PhoneBook
 */
void addPhoneNumber(char *name, long number, PhoneBook *book) {
	PhoneEntry *where = getPhoneNumber(name, *book);
	if (where == NULL) {
		if (++book->total > book->size) {
			reAllocPb(book);
		}
		book->entries[book->total - 1].number = number;
		strcpy(book->entries[book->total - 1].name, name);
		
	} else where->number = number;
}

#endif



