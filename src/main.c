#include "cpu.h"
#include "str.h"
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

genVector(int);
genVector(char);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error: Invalid number of arguments!\n");
		return -1;
	}

	// File read

	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("Error: Invalid File!\n");
		return -1;
	}

	char c = fgetc(file);
	vector_char *programFile = vector_init_char(100);

	if (programFile == NULL)
	{
		fclose(file);
		printf("Error: Ran out of memory!\n");
		return -1;
	}

	while (c != EOF)
	{
		if (c != '\n' && c != '\t')
		{
			if (!vector_push_char(programFile, c))
			{
				vector_destroy_char(programFile);
				fclose(file);
				printf("Error: Ran out of Memory!\n");
				return -1;
			}
		}

		c = fgetc(file);
	}

	fclose(file);

	// File read end

	// Turn to instructions

	vector_int *program = vector_init_int(100);

	if (program == NULL)
	{
		vector_destroy_char(programFile);
		printf("Error: Failed to convert file into program, ran out of memory!\n");
		return -1;
	}

	struct String* token = genString();

	if (token == NULL)
	{
		vector_destroy_char(programFile);
		vector_destroy_int(program);
		printf("Error: Failed to convert file into program, ran out of memory!\n");
	}

	for (int i=0; i<program->size; i++)
	{
		if (*vector_at_char(program, (size_t)i) == ' ')
		{
			append(token, '\0');
			if (token->str == "NOP")
			{
				if (!vector_push_int(program, NOP))
				{
					vector_destroy_int(program);
					vector_destroy_char(programFile);
					destroyString(token);
					printf("Error: Failed to convert file into program, ran out of memory!\n");
					return -1;
				}
			}
			else if (token->str == "HLT")
			{
				if (!vector_push_int(program, HLT))
				{
					vector_destroy_int(program);
					vector_destroy_char(programFile);
					destroyString(token);
					printf("Error: Failed to convert file into program, ran out of memory!\n");
					return -1;
				}
			}
			else if (token->str == "ADD")
			{
				if (!vector_push_int(program, ADD))
				{
					vector_destroy_int(program);
					vector_destroy_char(programFile);
					destroyString(token);
					printf("Error: Failed to convert file into program, ran out of memory!\n");
					return -1;
				}
			}
			else if (token->str == "ADI")
			{
				if (!vector_push_int(program, ADI))
				{
					vector_destroy_int(program);
					vector_destroy_char(programFile);
					destroyString(token);
					printf("Error: Failed to convert file into program, ran out of memory!\n");
					return -1;
				}
			}
			else if (token->str == "SUB")
			{
				if (!vector_push_int(program, SUB))
				{
					vector_destroy_int(program);
					vector_destroy_char(programFile);
					destroyString(token);
					printf("Error: Failed to convert file into program, ran out of memory!\n");
					return -1;
				}
			}
			else if (token->str == "SBI")
			{
				if (!vector_push_int(program, SBI))
				{
					vector_destroy_int(program);
					vector_destroy_char(programFile);
					destroyString(token);
					printf("Error: Failed to convert file into program, ran out of memory!\n");
					return -1;
				}
			}
			clearString(token);
		}
	}

	vector_destroy_char(programFile);
	// instructions end

	struct CPU *cpu = genCPU(100, 1024);
	setCurrentCPU(cpu);

	int arr[] = {
		LDI, R_0, 0,
		LDI, R_1, 1,
		ADD, R_2, R_0, R_1,
		PNT, R_0,
		CPY, R_0, R_1,
		CPY, R_1, R_2,
		CPI, R_2, 5000,
		JLI, 6,
		PNT, R_0,
		PNT, R_1,
		HLT
	};

	if (!loadProgram(arr, sizeof(arr)/sizeof(int)))
	{
		printf("Error: Failed to load program!\n");
		destroyCPU(cpu);
		return -1;
	}

	runVCPU();

	destroyCPU(cpu);
	return 0;
}