// Luong Duc Duong
//
// C_advance/JRB/testFunc
// main.c

#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"
#include "jval.h"

void insertTree(JRB root, int num) {
	
	Jval data;

	data = new_jval_i(num);
	jrb_insert_int(root, data.i, data);
}

void displayTree(JRB root) {
	JRB ptr;
	jrb_traverse(ptr, root) {
		printf("%d - ", jval_i(ptr->val));
	}
}

void destroyTree(JRB root) {
	jrb_free_tree(root);
	printf("* Destroy tree successed !\n");
}

void printMenu() {
	printf("\nMENU: \n");
	printf(" 1. Insert number to tree.\n");
	printf(" 2. Display tree.\n");
	printf(" 3. Destroy tree.\n");
	printf(" 4. Quit.\n\n");
}

int getIntNumber(int min, int max) {
    int choose = 0;
    printf(" - Enter number : ");
    do {
        scanf("%d", &choose); getchar();
        if (choose < 1 || choose > max) {
            printf("(!) Your choose must bigger than %d\n", min - 1);
            printf("    and smaller than %d\n\n", max + 1);
            printf(" - Re Enter number : ");
        }
    } while (max < choose || choose < 1);
    return choose;
}

int main(int argc, char const *argv[])
{
	JRB root = NULL;
	root = make_jrb();
	if (root == NULL) {
		printf("Make jrb failed!\n");
		return 1;
	}

	MENU:
	printMenu();
	//4 option
	int choose = getIntNumber(1, 4);

	switch (choose) {
		case 1:
			printf("\n");
            int num = 0;
            printf("Enter number to insert tree: ");
            scanf("%d", &num); getchar();
			insertTree(root, num);
			break;
		case 2:
			printf("\n");
			printf("Display tree: \n\n");
			displayTree(root);
			break;
		case 3:
			printf("\n");
			destroyTree(root);
			break;
		default:
			printf("\n");
			return 0;
	}

	goto MENU;
}
