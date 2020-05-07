/*This file is consist the data structure for the assembler program*/
#include "const.h"

/*structure for opration code*/
struct OPACTION{

	char *txt;    /*name of action*/
	int code;	/*the op code of action */	
	int num_op; /* the number of operands*/
	Method source[NUM_METHOD]; /* source method of each function */
	Method dest[NUM_METHOD];	/* destanation method of each function */

};
 


/*structure for registers*/
struct REGISTERS{
	char *name; /*name of register*/
	int value; /*the vakue of each register */
};


/*structure for list symbols label*/
typedef struct SYMBOLTABLE{
	char txt[MAX_LABEL];
	int address; /*the IC address*/
	enum ECD kind_ad; /*indicate if adrress is code, data or external*/
	pSymbol next;

}symbol;
 
/*structure for registers*/
struct REG{
	char *name; /*name of register*/
	int value; /*the vakue of each register */
};




/*structure for the data memoty program */
typedef struct TABELDATA{
	
	int address; /*the address that data will set into*/
	int data;  /*number is complite 2,and asccii charager*/

}tblData;


/*structure of coammnd word*/
struct ACTION_WORD
{

	unsigned int era:2;    /*first two bits to ERA code */
	unsigned int dest:2; /* bits 2-3 for code of dest method */
	unsigned int source:2; /* bits 4-5 for code of source method */
	unsigned opcode:4;	/* bits 6-9 for code of opeation code */
	
	
}act_wrd;

/*structure for 2'nd & 3'rd 4'th word*/
struct CPU10BITWORD
{

	unsigned int era:2;
	unsigned int dest_reg:4;
	unsigned int source_reg:4;	
	
}cpu10wrd;
/*structure for external & entry table*/
typedef struct LABELTABLE{
	
	char name[MAX_LABEL]; /*label name*/
	int address;		/*the addrees of label*/
	
}tblLabel;

