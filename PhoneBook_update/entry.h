#ifndef DEF_entry
#define DEF_entry

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	void *key;
	void *value;
} Entry;

typedef struct {
	Entry *entries;
	int size, total;
	Entry (*makeNode)(void *, void *);
	int (*compare)(void *, void *);
} SymbolTable;

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

void memCpy(void *p1, const void *p2, size_t size);
void reAlloc(SymbolTable *book);
SymbolTable createSymbolTable(
	Entry (*makeNode)(void *, void *),
	int (*compare)(void *, void *)
);
void dropSymbolTable(SymbolTable* tab);
void addEntry(void * key, void *value, SymbolTable *book);
Entry *getEntry(void *key, SymbolTable book);

#endif


