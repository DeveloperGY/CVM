#include "cpu.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

struct IntVector
{
	int *arr;
	long size;
};

struct IntVector *genIntVector()
{
	struct IntVector *vec = (struct IntVector *)calloc(1, sizeof(struct IntVector));

	if (vec == NULL)
	{
		return NULL;
	}

	vec->size = 0;
	vec->arr = NULL;

	return vec;
}

void destroyIntVector(struct IntVector *vec)
{
	free(vec->arr);
	free(vec);
	return;
}

void appendInt(struct IntVector *vec, int val)
{
	int *arr = (int *)realloc(vec->arr, (vec->size + 1) * sizeof(int));

	if (arr == NULL)
	{
		return;
	}

	vec->arr = arr;
	vec->size++;

	vec->arr[vec->size-1] = val;

	return;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error: Invalid number of arguments!\n");
		return -1;
	}

	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("Error: Failed to open file!\n");
		return -1;
	}

	char c;
	struct String *str = genString();

	c = fgetc(file);

	while (c != EOF)
	{
		if (!append(str, c))
		{
			printf ("Error: Ran out of PROGROM!\n");
		}

		c = fgetc(file);
	}

	fclose(file);

	struct String *ins = genString();
	struct IntVector *vec = genIntVector();

	printf("String Size: %ld\n", str->size);

	for (long i=0; i<str->size; i++)
	{
		if (str->str[i] == ' ' || str->str[i] == '\n' || str->str[i] == '\t')
		{
			if(ins->size == 0)
			{
				append(ins, str->str[i]);
				continue;
			}
			
			if (ins->str[0] == '#')
			{
				char ins_str[ins->csize];

				for (long i=1; i<ins->size; i++)
				{
					ins_str[i-1] = ins->str[i];
				}

				ins_str[ins->csize-1] = '\0';

				appendInt(vec, atoi((const char *)ins_str));
			}
			else
			{
				if (ins->str == "NOP")
				{
					appendInt(vec, NOP);
				}
				else if(ins->str == "HLT")
				{
					appendInt(vec, HLT);
				}
				else if(ins->str == "ADD")
				{
					appendInt(vec, ADD);
				}
				else if(ins->str == "ADI")
				{
					appendInt(vec, ADI);
				}
				else if(ins->str == "SUB")
				{
					appendInt(vec, SUB);
				}
				else if(ins->str == "SBI")
				{
					appendInt(vec, SBI);
				}
				else if(ins->str == "MLT")
				{
					appendInt(vec, MLT);
				}
				else if(ins->str == "MTI")
				{
					appendInt(vec, MTI);
				}
				else if(ins->str == "DIV")
				{
					appendInt(vec, DIV);
				}
				else if(ins->str == "DVI")
				{
					appendInt(vec, DVI);
				}
				else if(ins->str == "LOD")
				{
					appendInt(vec, LOD);
				}
				else if(ins->str == "LDI")
				{
					appendInt(vec, LDI);
				}
				else if(ins->str == "STR")
				{
					appendInt(vec, STR);
				}
				else if(ins->str == "CPY")
				{
					appendInt(vec, CPY);
				}
				else if(ins->str == "JMP")
				{
					appendInt(vec, JMP);
				}
				else if(ins->str == "JNZ")
				{
					appendInt(vec, JNZ);
				}
				else if(ins->str == "JEZ")
				{
					appendInt(vec, JEZ);
				}
				else if(ins->str == "JGZ")
				{
					appendInt(vec, JGZ);
				}
				else if(ins->str == "JLZ")
				{
					appendInt(vec, JLZ);
				}
				else if(ins->str == "JPI")
				{
					appendInt(vec, JPI);
				}
				else if(ins->str == "JNI")
				{
					appendInt(vec, JNI);
				}
				else if(ins->str == "JEI")
				{
					appendInt(vec, JEI);
				}
				else if(ins->str == "JGI")
				{
					appendInt(vec, JGI);
				}
				else if(ins->str == "JLI")
				{
					appendInt(vec, JLI);
				}
				else if(ins->str == "CMP")
				{
					appendInt(vec, CMP);
				}
				else if(ins->str == "CPI")
				{
					appendInt(vec, CPI);
				}
				else if(ins->str == "CMN")
				{
					appendInt(vec, CMN);
				}
				else if(ins->str == "CNI")
				{
					appendInt(vec, CNI);
				}
				else if(ins->str == "PNT")
				{
					appendInt(vec, PNT);
				}
				else if(ins->str == "R_0")
				{
					appendInt(vec, R_0);
				}
				else if(ins->str == "R_1")
				{
					appendInt(vec, R_1);
				}
				else if(ins->str == "R_2")
				{
					appendInt(vec, R_2);
				}
				else if(ins->str == "R_3")
				{
					appendInt(vec, R_3);
				}
				else
				{
					appendInt(vec, NOP);
				}
			}

			clearString(ins);
			continue;
		}

		append(ins, str->str[i]);
	}

	destroyString(ins);

	destroyString(str);

	struct CPU *cpu = genCPU(vec->size, 1024);
	setCurrentCPU(cpu);

	// int arr[] = {
	// 	LDI, R_0, 0,
	// 	LDI, R_1, 1,
	// 	ADD, R_2, R_0, R_1,
	// 	PNT, R_0,
	// 	CPY, R_0, R_1,
	// 	CPY, R_1, R_2,
	// 	CPI, R_2, 5000,
	// 	JLI, 6,
	// 	PNT, R_0,
	// 	PNT, R_1,
	// 	HLT
	// };

	printf("Size: %d\n", vec->size);

	if (!loadProgram(vec->arr, vec->size))
	{
		printf("Error: Failed to load program!\n");
		destroyIntVector(vec);
		destroyCPU(cpu);
		return -1;
	}

	printf("%d, %d\n", LDI, cpu->ins->ins[0]);

	destroyIntVector(vec);

	runVCPU();

	destroyCPU(cpu);
	return 0;
}