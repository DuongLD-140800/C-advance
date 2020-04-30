
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "jval.h"

#define MAX_LENGTH_NAME 30

typedef struct
{
	char key[MAX_LENGTH_NAME];
	long val;	
} Data;


int getIntNumber(int max) {
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

Data getUserData() {
	Data tmp;
	printf(" - Enter name  : ");
	scanf("%s", tmp.key); getchar();

	printf(" - Enter phone : ");
	scanf("%ld", &tmp.val); getchar();
	return tmp;
}

JRB askKeyAndFind(JRB root) {
	char name[MAX_LENGTH_NAME] = "\0";
	printf("Enter name : ");
	scanf("%s", name); getchar();

	JRB where = jrb_find_str(root, name);
	if (where == NULL) {
		printf("\n[!] Cannot find with name you type in.\n");
		return where;
	}

	printf("Find this :\n\n");
	printf(" - Name         : %s\n", jval_s(where->key));
	printf(" - Phone number : %ld\n", jval_l(where->val));
	return where;
}

void addPhone(JRB root) {
	Data newPhone = getUserData();
	JRB where = jrb_find_str(root, newPhone.key);

	if (where != NULL)
		where->val = new_jval_l(newPhone.val);
	else
		jrb_insert_str(root, strdup(newPhone.key), new_jval_l(newPhone.val));
}

void deletePhone(JRB root) {
	JRB where = askKeyAndFind(root);

	if (where != NULL) {
		jrb_delete_node(where);
		printf("\nDelete phone successed!\n");
	}
}

void changePhone(JRB root) {
	JRB where = askKeyAndFind(root);
	
	if (where == NULL) return;

	long newNum = 0;
	printf("Enter new phone number : ");
	scanf("%ld", &newNum); getchar();

	where->val = new_jval_l(newNum);
}

void printMenu() {
	printf("\n MENU:\n\n");
	printf(" 1. Add phone.\n");
	printf(" 2. Delete phone.\n");
	printf(" 3. Change phone.\n");
	printf(" 4. Quit\n");	
}

int main(int argc, char const *argv[])
{
	JRB root = NULL;
	root = make_jrb();
	if (root == NULL) {
		perror("Cannot make_jrb! Error: ");
		exit(2);
	}

	MENU:
	printMenu();
	//4 option
	int choose = getIntNumber(4);

	switch (choose) {
		case 1:
			printf("\n");
			printf("How many phones do you want to add ?\n");
    		int number = getIntNumber(9999999);

			for (int i = 0; i < number; i++) {
				printf("\n* Phone %d:\n", i + 1);
				addPhone(root);
			}
			break;
		case 2:
			printf("\n");
			deletePhone(root);
			break;
		case 3:
			printf("\n");
			changePhone(root);
			break;
		default:
			printf("\n");
			jrb_free_tree(root);
			printf("Exit!\n");
			return 0;
	}
	goto MENU;
}