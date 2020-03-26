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
PhoneBook createPhoneBook() {
	PhoneBook newPb;
	newPb.total = 0;
	newPb.size = INITIAL_SIZE;
	newPb.entries = (PhoneEntry *) malloc(newPb.size * sizeof(PhoneEntry));
	if (newPb.entries == NULL) {
		printf("Malloc not successed !\n");
		exit(1);
	}
	return newPb;
}
void dropPhoneBook(PhoneBook* book) {
	if (book->entries != NULL)
		free(book->entries);
}
PhoneEntry* getPhoneNumber(char * name, PhoneBook book) {
	for (int i = 0; i < book.total; i++) {
		if (strcmp(name, book.entries[i].name) == 0)
			return (book.entries + i);
	}
	return NULL;
}
void reAllocation(PhoneBook *book) {
	book->entries = (PhoneEntry *) 
						realloc(book->entries,
							(book->size += INCREMENTAL_SIZE) * sizeof(PhoneEntry));
	if (book->entries == NULL) {
		printf("Realloc not successed !\n");
		exit(1);
	}
}
void addPhoneNumber(char *name, long number, PhoneBook *book) {
	PhoneEntry *where = getPhoneNumber(name, *book);
	if (where == NULL) {
		if (++book->total > book->size) {
			reAllocation(book);
		}
		book->entries[book->total - 1].number = number;
		strcpy(book->entries[book->total - 1].name, name);
		
	} else where->number = number;
}
