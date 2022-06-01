#ifndef INS_H
#define INS_H

#include <stdio.h>
#include <stdlib.h>

enum INS
{
	NOP = 0, //                 No Operation
	HLT,     //                 Halt Program

	ADD,     //                Add Registers
	ADI,     //                Add Immediate
	SUB,     //           Subtract Registers
	SBI,     //           Subtract Immediate
	MLT,     //           Multiply Registers
	MTI,     //           Multiply Immediate
	DIV,     //             Divide Registers
	DVI,	 //             Divide Immediate

	LOD, 	 //                Load Register
	LDI,	 //               Load Immediate
	STR,     //               Store Register
	CPY, 	 //                Copy Register

	JMP,	 //          Jump to instruction
	JNZ,	 //             Jump if not Zero
	JEZ,	 //                 Jump if Zero
	JGZ, 	 //    Jump if greater than Zero
	JLZ, 	 //       Jump if less than Zero

	JPI,	 //       Jump to instruction IM
	JNI,	 //          Jump if not Zero IM
	JEI,	 //              Jump if Zero IM
	JGI, 	 // Jump if greater than Zero IM
	JLI, 	 //    Jump if less than Zero IM

	CMP, 	 // Compare Registers (subtract)
	CPI,     // Compare Immediate (subtract)
	CMN,     // Compare Registers (addition)
	CNI,     // Compare Immediate (addition)

	PNT,     //               Print Register

	R_0,     //                   Register 0
	R_1,     //                   Register 1
	R_2,     //                   Register 2
	R_3      //                   Register 3
};

struct INSArr
{
	enum INS *ins;
	long size;
	long ins_ptr;
};

struct INSArr *genINS(long);
void destroyINS(struct INSArr *);

char loadINS(struct INSArr *, int *, long);

#endif