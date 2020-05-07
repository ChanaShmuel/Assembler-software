/*this file consist all the constant vars & includes*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include  <math.h>


/*const array for starnge base 32 code*/
#define StrangeCode "!@#$%^&*<>abcdefghijklmnopqrstuv" 

#define MAX_LINE 81	/*max character in line file include \n*/
#define MAX_LABEL 31  /*include character ':', char '\0' not include in strlen() */
#define MAX_FILE_NAME 30  /*the max name of file, include the suffix file*/
#define BASE32_CODE 3 /*number of character of word in special base 32 include '\0'*/
#define BASE32 32

#define NUM_METHOD 4  /*kind of method*/
#define START_ADDRESS 100
#define MEMORY_SIZE 255
#define BIG_ENOUGH_MEMORY_SIZE 100
#define NO_ACTION -99

/*declaration for special characters*/
#define REMARK ';'
#define END_STRING '\0'
#define CH_COMMA ','
#define CH_QUOTATION '\"'
#define CH_COLON ':'
#define CH_INIT_NUM '#'
#define CH_POINT '.'
#define CH_PLUS '+'
#define CH_MINUS '-'

/*declaretion for  statement*/
#define STRING_STS ".string"   
#define DATA_STS ".data"
#define STRUCT_STS ".struct"	
#define ENTRY_STS ".entry"
#define EXTREN_STS ".extern"


#define NUM_OP_8BITS 256  /*  2^8 */
#define MAX_OP_POS_NUM 127  /* 2^7-1 */
#define MIN_OP_NEG_NUM -128 /*  2^7 */
#define NUM_10BITS 1024  /*  2^10 */
#define MAX_POS_NUM 511  /* 2^9-1 */
#define MIN_NEG_NUM -512 /*  2^9 */


/*suffix for name files*/
#define SUFFIX_AS ".as" /*for assembly file*/
#define SUFFIX_EXT ".ext" /*for external file*/
#define SUFFIX_ENT ".ent" /*for external file*/
#define SUFFIX_OB ".ob"   /*for object file*/

enum KIND_OPCODE {NO_OP=0,ONE_OP,TWO_OP};
enum METHOD {NON_OPERAND=-1,IMMEDIATE=0,DIRECT,LIST_ACCESS,DIRECT_REG};
enum ERA {ABSOLUTE=0,EXTERNAL,RELOCATE};
enum ECD {EXT=0,CODE,DATA};
enum Boolean {FALSE=0,TRUE};

typedef struct SYMBOLTABLE *pSymbol;
typedef struct OPACTION OpAction;
typedef struct TABELDATA *ptblData;
typedef enum METHOD Method; 
typedef struct REGISTERS Reg;
typedef struct LABELTABLE *ptblLabel;
typedef struct CPU10BITWORD pcpuWord;




