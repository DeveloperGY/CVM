#include "str.h"

struct String *genString()
{
	struct String *str = (struct String *)calloc(1, sizeof(struct String));

	if (str == NULL)
	{
		return NULL;
	}

	str->size = 0;
	str->csize = 1;

	str->str = (char *)calloc(1, sizeof(char));

	if (str->str == NULL)
	{
		free(str);
		return NULL;
	}

	str->str[0] = '\0';

	return str;
}

struct String *initString(char *cstr, long size)
{
	struct String *str = (struct String *)calloc(1, sizeof(struct String));

	if (str == NULL)
	{
		return NULL;
	}

	str->size = size - 1;
	str->csize = size;

	str->str = (char *)calloc(size, sizeof(char));

	if (str->str == NULL)
	{
		free(str);
		return NULL;
	}

	for (int i=0; i<size; i++)
	{
		str->str[i] = cstr[i];
	}

	return str;
}

void destroyString(struct String *str)
{
	free(str->str);
	free(str);
	return;
}

char append(struct String *str, char c)
{
	char *string = (char *)realloc(str->str, (str->csize+1) * sizeof(char));

	if (string == NULL)
	{
		return 0;
	}

	str->str = string;
	str->csize++;
	str->size++;

	str->str[str->size - 1] = c;
	str->str[str->csize - 1] = '\0';

	return 1;
}

void clearString(struct String *str)
{
	str->size = 0;
	str->csize = 1;

	free(str->str);

	str->str = (char *)calloc(1, sizeof(char));
	str->str[0] = '\0';
	return;
}