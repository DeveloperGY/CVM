#include "cpu.h"
#include "str.h"
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

genVector(int);
genVector(char);

void printError(const char *msg, int line)
{
	printf("[Line %d] - %s\n", line, msg);
	return;
}

int getIns(struct String *);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printError("Error: Invalid number of arguments!\n", __LINE__);
		return -1;
	}

	// File read

	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printError("Error: Invalid File!\n", __LINE__);
		return -1;
	}

	struct String* token = genString();
	vector_int *tokens = vector_init_int(100);

	if (token == NULL)
	{
		fclose(file);
		printError("Error: Failed to convert file to program, couldn't generate token!\n", __LINE__);
		return -1;
	}

	if (tokens == NULL)
	{
		fclose(file);
		vector_destroy_int(tokens);
		printError("Error: Failed to convert file to program, couldn't generate token!\n", __LINE__);
		return -1;
	}

	char c = fgetc(file);

	while (c != EOF)
	{
		if (c != ' ' && c != '\n' && c != '\t' && c != ',' && c != '\0')
		{
			append(token, c);
		}
		else
		{
			// if (strcmp(token->str, "") == 0)
			// 	continue;
			
			int ins = getIns(token);
			vector_push_int(tokens, ins);
			clearString(token);
		}

		c = fgetc(file);
	}

	fclose(file);

	// // to get the last token
	// vector_push_int(tokens, getIns(token));
	// destroyString(token);


	struct CPU *cpu = genCPU(tokens->size, 1024);

	if (cpu == NULL)
	{
		printError("Error: Failed to generate VCPU!\n", __LINE__);
		vector_destroy_int(tokens);
		return -1;
	}

	setCurrentCPU(cpu);

	int instructions[tokens->size];

	for (int i=0; i<tokens->size; i++)
	{
		instructions[i] = *vector_at_int(tokens, i);
	}

	if (!loadProgram(instructions, sizeof(instructions)/sizeof(int)))
	{
		printError("Error: Failed to load program!\n", __LINE__);
		vector_destroy_int(tokens);
		destroyCPU(cpu);
		return -1;
	}

	runVCPU();

	if (cpu != NULL)
		destroyCPU(cpu);

	if (tokens != NULL)
		vector_destroy_int(tokens);

	return 0;
}

int getIns(struct String *token)
{
	if (token->str[0] == '#')
	{
		char num[token->csize - 1];

		for (int i=1; i<token->csize; i++)
		{
			num[i-1] = token->str[i];
		}

		return atoi(num);
	}
	else
	{
		if (strcmp(token->str, "NOP") == 0)
		{
			return NOP;
		}
		else if (strcmp(token->str, "HLT") == 0)
		{
			return HLT;
		}
		else if (strcmp(token->str, "ADD") == 0)
		{
			return ADD;
		}
		else if (strcmp(token->str, "ADI") == 0)
		{
			return ADI;
		}
		else if (strcmp(token->str, "SUB") == 0)
		{
			return SUB;
		}
		else if (strcmp(token->str, "SBI") == 0)
		{
			return SBI;
		}
		else if (strcmp(token->str, "MLT") == 0)
		{
			return MLT;
		}
		else if (strcmp(token->str, "MTI") == 0)
		{
			return MTI;
		}
		else if (strcmp(token->str, "DIV") == 0)
		{
			return DIV;
		}
		else if (strcmp(token->str, "DVI") == 0)
		{
			return DVI;
		}
		else if (strcmp(token->str, "LOD") == 0)
		{
			return LOD;
		}
		else if (strcmp(token->str, "LDI") == 0)
		{
			return LDI;
		}
		else if (strcmp(token->str, "STR") == 0)
		{
			return STR;
		}
		else if (strcmp(token->str, "CPY") == 0)
		{
			return CPY;
		}
		else if (strcmp(token->str, "JMP") == 0)
		{
			return JMP;
		}
		else if (strcmp(token->str, "JNZ") == 0)
		{
			return JNZ;
		}
		else if (strcmp(token->str, "JEZ") == 0)
		{
			return JEZ;
		}
		else if (strcmp(token->str, "JGZ") == 0)
		{
			return JGZ;
		}
		else if (strcmp(token->str, "JLZ") == 0)
		{
			return JLZ;
		}
		else if (strcmp(token->str, "JPI") == 0)
		{
			return JPI;
		}
		else if (strcmp(token->str, "JNI") == 0)
		{
			return JNI;
		}
		else if (strcmp(token->str, "JEI") == 0)
		{
			return JEI;
		}
		else if (strcmp(token->str, "JGI") == 0)
		{
			return JGI;
		}
		else if (strcmp(token->str, "JLI") == 0)
		{
			return JLI;
		}
		else if (strcmp(token->str, "CMP") == 0)
		{
			return CMP;
		}
		else if (strcmp(token->str, "CPI") == 0)
		{
			return CPI;
		}
		else if (strcmp(token->str, "CMN") == 0)
		{
			return CMN;
		}
		else if (strcmp(token->str, "CNI") == 0)
		{
			return CNI;
		}
		else if (strcmp(token->str, "PNT") == 0)
		{
			return PNT;
		}
		else if (strcmp(token->str, "R_0") == 0)
		{
			return R_0;
		}
		else if (strcmp(token->str, "R_1") == 0)
		{
			return R_1;
		}
		else if (strcmp(token->str, "R_2") == 0)
		{
			return R_2;
		}
		else if (strcmp(token->str, "R_3") == 0)
		{
			return R_3;
		}
		else
		{
			return NOP;
		}
	}
}