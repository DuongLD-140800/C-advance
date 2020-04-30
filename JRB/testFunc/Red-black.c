#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Lib for red black tree
#include "jrb.h"


void printPhoneBook(JRB PhoneBook,FILE* fptr){
    if(PhoneBook == NULL) return;
    printPhoneBook(PhoneBook->blink,fptr);
    fprintf(fptr,"%s\t%ld\n",PhoneBook->val.s,PhoneBook->key.l);
    printPhoneBook(PhoneBook->flink,fptr);
}

int main(int argc, char const *argv[])
{
    JRB Phonebook = make_jrb();
    printf("Here's your phonebook\n");
    int choice;
    char Name[30];
    long number;
    JRB tmp;
    int found = 0;
    FILE* fptr = fopen("PhoneBook","w+");
    while (1)
    {
        printf("**********MENU***********\n");
        printf("1. Add number & Name\n2. Find number\n3. Modify\n4. Print File\n5. Out\n");
        printf("Option: "); scanf("%d",&choice);
        switch (choice)
        {
        case 1:{
            printf("Number: "); scanf("%ld",&number);
            printf("Name: "); scanf("%s", Name);
            tmp = jrb_find_int(Phonebook,number);
            if (tmp != NULL) {
                printf("Existed, You might want to modify\n");
            }
            else
            {
                Jval name = new_jval_s(Name);
                jrb_insert_int(Phonebook,number,name);
            }
            break;
        }
        case 2:{
            printf("Number to look for: "); scanf("%ld",&number);
            tmp = jrb_find_gte_int(Phonebook, number, &found);
            if(found >= 0){
                printf("FOUND!\n%s\n%ld\n",tmp->val.s, number);
            }
            else printf("Not Found, U might want to Insert\n");
            break;
        }
        case 3:{
            printf("Number: "); scanf("%ld", &number);
            tmp = jrb_find_gte_int(Phonebook, number, &found);
            if (tmp != NULL)
            {
                printf("Name in book: %s\n", tmp->val.s);
                printf("Name to modify: "); scanf("%s", Name);
                strcpy(tmp->val.s,Name);
            }
            else printf("Not found, can not modified\n");
            break;
        }
        case 4: {
            printPhoneBook(Phonebook,fptr);
            break;
        }
        case 5: {
            jrb_free_tree(Phonebook);
            return 0;
        }
    }
}
    fclose(fptr);
    return 0;
}
