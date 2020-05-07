/*this file consist all global vars and struct*/



/*global vars*/
int IC,DC; /*counters of Instructions & Data*/ 
int err_cnt; /*counter for numbers errors*/
int fnum_line; /*the number line is readen from file*/
int mem_code[BIG_ENOUGH_MEMORY_SIZE]; /*array for translated assmbler code is more big then the memory to privante overflow*/
int ext_cnt; /*external counter for external table*/
int ent_cnt; /*enternal counter for enternal table*/

/*global struct*/ 
ptblData tbl_data;  /* dymanic array of Data DC */
ptblLabel tbl_ext; /*dynamic array for  extern table*/
ptblLabel tbl_ent; /*dynamic array for entery table*/
pcpuWord cpu_wrd; /*cpu 10 bits word for 2'cd 3'rd 4'th words*/

/*const struct of all optional command & thier options */
OpAction op_action[]= {
			{"mov",0,TWO_OP,{IMMEDIATE,LIST_ACCESS,DIRECT_REG,DIRECT},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"cmp",1,TWO_OP,{IMMEDIATE,LIST_ACCESS,DIRECT_REG,DIRECT},{IMMEDIATE,LIST_ACCESS,DIRECT_REG,DIRECT}},
			{"add",2,TWO_OP,{IMMEDIATE,LIST_ACCESS,DIRECT_REG,DIRECT},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"sub",3,TWO_OP,{IMMEDIATE,LIST_ACCESS,DIRECT_REG,DIRECT},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"not",4,ONE_OP,{NON_OPERAND},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"clr",5,ONE_OP,{NON_OPERAND},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"lea",6,TWO_OP,{DIRECT,LIST_ACCESS,NON_OPERAND},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"inc",7,ONE_OP,{NON_OPERAND},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"dec",8,ONE_OP,{NON_OPERAND},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"jmp",9,ONE_OP,{NON_OPERAND},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"bne",10,ONE_OP,{NON_OPERAND},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"red",11,ONE_OP,{NON_OPERAND},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"prn",12,ONE_OP,{NON_OPERAND},{IMMEDIATE,LIST_ACCESS,DIRECT_REG,DIRECT}},
			{"jsr",13,ONE_OP,{NON_OPERAND},{LIST_ACCESS,DIRECT_REG,DIRECT,NON_OPERAND}},
			{"rts",14,NO_OP,{NON_OPERAND},{NON_OPERAND}},
			{"stop",15,NO_OP,{NON_OPERAND},{NON_OPERAND}},
			{NULL}

		
};

/*const struct of register name & threrv code */
Reg reg[]= {
		{"r0",0},
		{"r1",1},
		{"r2",2},
		{"r3",3},
		{"r4",4},
		{"r5",5},
		{"r6",6},
		{"r7",7},
		{NULL}
	
};



pSymbol head=NULL;  /*pointer to head of list of symbol table*/






