#define INITIAL_SIZE 10 
#define INCREMENTAL_SIZE 5
//Chao cac ban
typedef struct { 
	char name[80]; 
	long number;
} PhoneEntry;
typedef struct { 
	PhoneEntry * entries; 
	int total;
	int size;
} PhoneBook;

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook *book);
void addPhoneNumber(char *name, long number, PhoneBook *book);
PhoneEntry* getPhoneNumber(char *name, PhoneBook book);

PhoneEntry getUserData() {
	PhoneEntry user;
	printf(" - Enter name : ");
	scanf("%79[^\n]s", user.name); getchar();
	printf(" - Enter phone : ");
	scanf("%ld", &user.number); getchar();
	return user;
}
PhoneBook createPhoneBook() {
	PhoneBook new;
	new.total = 0;
	new.size = INITIAL_SIZE;
	new.entries = (PhoneEntry *) malloc(new.size * sizeof(PhoneEntry));
	if (new.entries == NULL) {
		printf("Memory allocation not successed !\n");
		exit(1);
	}
	return new;
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
						realloc(book->entries,(book->size += INCREMENTAL_SIZE) * sizeof(PhoneEntry));
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
