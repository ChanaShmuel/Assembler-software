/*this file consist all the constant vars & includes*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include  <math.h>

void print_DC_table(); /*print DC table - for debugs*/

/*declation of function*/
/*****************************************************/
/******declartins of firstTranslate model ****** */
/*****************************************************/
/*this funtion go over the assembly file and translate it as first time
get parter file name to be translate 
build a symbol table for label
f- is pointer to file program that have to translate 
return true if no errors founds
*/
int first_trans(FILE *);

/*isDataSts - check if it is Data or String  or structe statment.
str- is a string to be check is Data or String statment*/
int isDataSts(char *str);

/*correct_label:check if is correct label and threre is no multiply label
word - is th label is check
str is the read line from file*/
int correct_label(char *word,char *str);

/*isEntrySts - check if it is Entry statment.
str- is a string to be check is Entry statment*/
int isEntrySts(char *str);
/*isExtrenSts - check if it is External statment.
str- is a string to be check is External statment*/
int isExternSts(char *str);
/*addExternSymbol-add extern dymbol to list after checking if is legal lbael
word - is thethe sybol add*/
void addExternSymbol(char *word);

/*fill_mem: fill memory with data, this function sent to other specific function to fill 
memory with data:threre are 3 kind of data:data strig struct
word is the kind of data to fill mem)
str- is the left line read from file*/
void fill_mem(char *word,char *str);

/*add_data2mem: fill memory with data numbers
str- is the string to fill in mem.*/
void add_data2mem(char *str);

/*add_string2mem: fill memory with string
str- is the string to fill in mem.*/
void add_string2mem(char *str);

/*add_struct2mem: fill memory with struct
str- is the string to fill in mem.*/
void add_struct2mem(char *str);

/*isAction - check if it is Action code, there is 16 Action word.
str- is a string to be check is Action
return True if is action found */
int isAction(char *str);

/*get_action code - get the number of action 
if is no action return NO_ACTION 
str - is the action string
return integer indicate the place of Action is table*/
int get_action_code(char *str);

/*get_num_word: calculate the number words to choosen action
& check if it's paramentrs are correct & make the first word
str is the string read from file
i- is index of the action in table op_code*/
void get_num_word(char *,int i);

/*complete2no_op:compete word by check the action without operands
str-as the action be check
pact is pointer to the build word*/
void complete2no_op(char *str,unsigned int *pact);

/*complete2one_op:compete word by check the action with 1 operands
str-as the action be check
pact is pointer to the build word
i- is index of the action in table op_code*/
void complete2one_op(char *str,int i,unsigned int *pact);

/*complete2two_op:compete word by check the action with 2 operands
str-as the action be check
pact is pointer to the build word
i- is index of the action in table op_code*/
void complete2two_op(char *str,int i,unsigned int *pact);

/*check_dest:cheking for legal dest operand, return true is legal & return the method of it.
word- is dest operand
metod is return value indicate the type of  method
return true is is legal use of dest operand*/
int check_dest(char *word,int index,Method *method);

/*check_source:cheking for legal source operand, return true is legal & return the method of it.
word- is source operand
metod is return value indicate the type of  method
return true is is legal use of dest operand*/
int check_source(char *word,int index,Method *method);


/*check_method: checking the method of destatin operand
method is number indicate the type metod
str is operand to be check 
return true if check success*/
int check_method(Method method,char * str);

/*****************************************************/
/******declartins of SecondTranslate model ****** */
/*****************************************************/
/*this funtion go over the assembly file and translate it at second time
get parter file name to be translate 
build a all tranlate program make ext table entry table and memory code table
f- is pointer to file program that have to translate 
return true if no errors founds
*/
int second_trans(FILE *);

/*declare_dynamic_tbl:declare dynamic tbl for extern & extern labels*/
void declare_dynamic_tbl();

/*build_other_word: make the second & third &fourth word for action
inx- the index to relative action in table op_action*/
void build_next_words(char * str,int inx);

/*build_word2one_op:build the code word for action with 1 operand
str is the operand
inx-is the index of action*/
void build_word2one_op(char *str,int inx);

/*build_word2two_op:build the code word for action with 2 operand
str is the operand
inx-is the index of action*/
void build_word2two_op(char *str, int inx);

/* fill_next_word:translate other next words
inx- is index of action in op_action table 
method -is the method of operand
value- in a vlaue of register for dest and source */
void fill_next_word(char *str,int inx,Method method,int *value);

/* make_direct_word:make direct word for surce and dest operand
str is the operand need to make a code
insert the codeing to memory array*/
void make_direct_word(char* str);

/*make_list_access_word:make 2 words for list access method for both source or dest operand
str-is the operand need to be codeing*/
void make_list_access_word(char * str);

/*add2ent_tbl:add label to entry array for making at end entry file
str is the label to add*/
void add2ent_tbl(char *str);

/*****************************************************/
/******function for support function model******/
/*****************************************************/
/*get first word from string and return the string without this word
str is string have to take the first word the first word delete from string
word is the return the first word*/
void get_word(char *str,char* word);
 

/* isSymbol: check if is label, label end by :(COLON)
str- is the word checking */
int isSymbol(char *str);



int isLegalLabel(char *str);
int isCorrectLabel(char *str);
/*convert_string2int:convert string to integer num and check if is integer
str-is the string that nedd to convert
return int number*/
int convert_string2int(char*str);

int isSymbolExists(char *str);

/*isRegister - check if is Register name.
str- is a string to be check if is Register.*/
int isRegister(char *str);

/*get_register_num:get the register number
str-is the rgister is number wanted
return int - the code of register*/
int get_register_num(char *str);

/*isLegalNumner: check if number is legal integer number.
str- is a string need to check if is legal number 
return true if is legal number*/
int isLegalNumber(char *str);

/*isLegelListAccess:check for legal use of list access
str- is the name list access is need to check
return true if is legal*/
int isLegalListAccess(char *str);

/*isEmpty:check if string is empty
str-is check string
return true if is empty*/
int isEmpty(char * s);

/*****************************************************/
/* ****function for list node model***** */
/*****************************************************/
/*add2list: add data to list node in begging
phead- is a pointer to the head of list
str is symbol  to add
int ic the IC address when label declare
ecd is enum type isdicate if address is external ,code or data
*/
void add2list(pSymbol * phead,char *str,int ic,enum ECD ecd);
/*isExists: check if symbol exsist in list
p pointer to list
name- string as to be check
return true is label exsists
*/
int isExists(pSymbol p,char *name);
void print_list(pSymbol head);

/*update_address: update the address of label DATA to ended location
head is poiter to head of list*/
void update_memory_address(pSymbol head);

/*get_address: get the addrres of label
head is pointer to head of list
str is a label her address wanted
return the address of label*/
unsigned int get_address(pSymbol head ,char *str);

/*get_kind_ad: get kind of addrees method(data, code, external)
head- is pointer to head of list
str is string label is kind addreesing method iswanted
return the kind address of label*/
unsigned int get_kind_ad(pSymbol head ,char *str);

/*free_list: free memory 
head is poiter to head of list*/
void free_list(pSymbol * phead);

/*****************************************************/
/* ****function for dynamicArray node model***** */
/*****************************************************/

/*add2DC_table:add data to DC table
n- is the data to add*/
void add2DC_tbl(int n);

/*add_DC_table2mem: add DC data table to memory tranlate code*/
void add2DCmem_tbl();

/*add2lbl_table:add data to lable table for entry and extearnal data
p- is the pointer to table(entry or external
c- is counter of external or entry array
str is string to add to list array*/
void add2lbl_tbl(ptblLabel p,int *c,char *str);

/*****************************************************/
/* ****function for File Functons node model***** */
/*****************************************************/
/*save_tbl2file: write table details to file
plbl-is poiter to struct label table 
last-is the last index in dymanic array
name- is string name file
suffix is the suffix of name file*/
void save_tbl2file(ptblLabel plbl,int last,char *name,char *suffix);

/*save_mem_code2file: write assembly code to file .ob
name: is name file to write
suffix: is the suffix of file -ob*/
void save_mem_code2file(char *name,char *suffix);


/*convert2base32:convert number to base 32
num is integer  to be convert
str is the return result*/
void convert2base32(int num, char *str);

/*****************************************************/
/*****************************************************/
/*declaration for extern vars*/
extern int DC,IC;
extern int err_cnt;
extern int fnum_line;
/*extern char StrangeCode[];*/
extern int ext_cnt; 
extern int ent_cnt; 
extern pSymbol head;
extern OpAction op_action[];
extern Reg reg[];
extern int mem_code[];
extern ptblData tbl_data; 
extern ptblLabel tbl_ext; 
extern ptblLabel tbl_ent; 
extern pcpuWord cpu_wrd;
