/**
 * Luong Duc Duong
 *
 *
 * C_advance
 * phoneBook.c
 */



#include "phoneBook.h"

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