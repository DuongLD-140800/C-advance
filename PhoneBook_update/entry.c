#include "entry.h"

void memCpy(void *p1, const void *p2, int size) {
	char *first = (char *) (p2);
	char *last = (char *)(p2) + size;
	char *tmp = (char *)(p1);
	while(first != last) *tmp++ = *first++;
}
void reAlloc(SymbolTable *book) {
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
	for (int i = 0; i < tab->total; i++) {
		free(tab->entries[i].key);
		free(tab->entries[i].value);
	}
	free(tab->entries);
	tab->size = 0;
	tab->total = 0;
}
Entry *getEntry(void *key, SymbolTable book) {
	for (int i = 0; i < book.total; i++) {
		if (book.compare(book.entries[i].key, key) == 0)
			return (book.entries + i * sizeof(Entry));
	}
	return NULL;
}
void addEntry(void * key, void *value, SymbolTable *book) {
	Entry *where = getEntry(key, *book);
	if (where != NULL) {
		*where = book->makeNode(key, value);
	} else {
		if (++(book->total) > book->size)
			reAlloc(book);
		book->entries[book->total - 1] = book->makeNode(key, value);
	}
}