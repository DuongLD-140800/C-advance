/**
 * Luong Duc Duong
 * 27/03/2020
 *
 * C_advance
 * entry.c
 */


#include "entry.h"

void insertionSort(SymbolTable *book) {
	Entry pivot;
	int j = 0;
	for (int i = 0; i < book->total; i++) {
		pivot = book->entries[i];
		j = i - 1;

		while (j >= 0 && book->compare(book->entries[j].key, pivot.key) > 0) {
			memcpy(&book->entries[j + 1], &book->entries[j], sizeof(Entry));
			j = j - 1;
		}
		memcpy(&book->entries[j + 1], &pivot, sizeof(Entry));
	}
}
void reAllocEntries(SymbolTable *book) {
	book->entries = (Entry *) realloc(book->entries, 
						(book->size += INCREMENTAL_SIZE) * sizeof(Entry));
	if (book->entries == NULL) {
		printf("Memory reallocation not successed !\n");
		exit(1);
	}
}
SymbolTable createSymbolTable(
	Entry (*makeNode)(void *, void *),
	int (*compare)(void *, void *)
) {
	SymbolTable phoneBook;
	phoneBook.entries = (Entry *) malloc(sizeof(Entry) * INITIAL_SIZE);
	if (phoneBook.entries == NULL) {
		printf("Memory allocation not successed !\n");
		exit(1);
	}
	phoneBook.size = INITIAL_SIZE;
	phoneBook.total = 0;
	phoneBook.makeNode = makeNode;
	phoneBook.compare = compare;
	return phoneBook;
}
void dropSymbolTable(SymbolTable* tab) {
    if (tab->entries == NULL) {
        printf("Entries now is NULL - Nothing to drop.\n");
        return;
    }
	for (int i = 0; i < tab->total; i++) {
		free(tab->entries[i].key);
		free(tab->entries[i].value);
	}
	free(tab->entries);
    tab->entries = NULL;
	tab->size = 0;
	tab->total = 0;
    printf("Drop entries successed !\n");
}
Entry *getEntry(void *key, SymbolTable book, int l, int r) {
	if (l > r) return NULL;
	int arg = (l + r) / 2;
	int compare = book.compare(book.entries[arg].key, key);
	if (compare == 0) return &book.entries[arg];
	else if (compare > 0) return getEntry(key, book, l, arg - 1);
	else return getEntry(key, book, arg + 1, r);
}
void addEntry(void * key, void *value, SymbolTable *book) {
	Entry *where = getEntry(key, *book, 0, book->total - 1);
	if (where != NULL) {
		*where = book->makeNode(key, value);
	} else {
		if (++(book->total) > book->size)
			reAllocEntries(book);
		book->entries[book->total - 1] = book->makeNode(key, value);
	}
}
