#ifndef STR_H
#define STR_H

#include <stdlib.h>

struct String
{
	long size;
	long csize;
	char *str;
};

struct String *genString();
struct String *initString(char *, long);
void destroyString(struct String *);


char append(struct String *, char);
void clearString(struct String *);

#endif