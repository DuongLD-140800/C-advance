/**
 * Luong Duc Duong
 *
 *
 * C_advance
 * phoneBook.h
 * 
 */


#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

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


int getIntNumber(int max);
Data getUserData(void);
JRB findPhone(JRB root, char *key);
JRB askKeyAndFind(JRB root);
void addPhone(JRB root);
void deletePhone(JRB root);
void changePhone(JRB root);




#endif /* phoneBook.h */




