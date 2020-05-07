/*This is first translate MOdel*/
/*this model over the assembly program at first time as check for legal write and make 
table symbol as the main commads*/
#include "dataStruct.h"
#include "declaration.h"
 
 
/*first trans: translate the program at first time */

int first_trans(FILE *f)
{
	
 	char str[MAX_LINE];
	char word[MAX_LABEL];
	char lbl[MAX_LINE];
	int flag_smbl;  /*flag for smbol */
	int inx_act;
	
	IC=0;   
	DC=0;
	fnum_line=0; 
	tbl_data=(ptblData)malloc(sizeof(tblData)); /*bulid tbl for DC data */
	if(!tbl_data)
	{
		printf("\n cannot have build a list");
		exit(0);
	}
	while(!feof(f) && fgets(str,MAX_LINE,f)!=NULL)
	{
		fnum_line++;
		flag_smbl=FALSE;
		if (str[0]==REMARK) continue;  /*ignore from remark line*/
		
		get_word(str,word); 
		if (isEmpty(word))
			 continue; /*ignore from line empty*/
	
		if ((flag_smbl=isSymbol(word))==TRUE)  /*check if is label*/
		{
			word[strlen(word)-1]=END_STRING;  /*delete charagter ':' at the end*/
			strcpy(lbl,word);   /*save label*/
			if(!correct_label(word,str))   /*check for correct label & no multiply*/
				continue;
			}
		
		if  (isDataSts(word)) /*check for .data or .string .struct statment*/
		{
			add2list(&head,lbl,DC,DATA); /*add label to node */
			fill_mem(word,str);
			continue;
		}
	
		/*check is statment is .extern*/
		if(isExternSts(word))
		{	
			get_word(str,word);
			addExternSymbol(word);
			continue;
		}
	
		/*check is statment is .entry*/
		if(isEntrySts(word)) continue;  /*ignore from entry statment in first translate*/
		
		if  (flag_smbl)
			add2list(&head,lbl,IC,CODE); /*add label to node */
		
		if((inx_act=get_action_code(word))!=NO_ACTION) /*get number action & check if is a correct Action */
			get_num_word(str,inx_act); /* calulate the number of word the command line take*/

		else
		{ 
			printf("Error in line %d: word %s un recognize .\n",fnum_line,word);
			err_cnt++;
		}
	}
	
	/*check if program not exit from size of memory*/
	if (IC+DC>MEMORY_SIZE)
	{ 
		printf("Error: Exit from range memory. maximum memory size is %d, memory program is %d\n",MEMORY_SIZE,IC+DC);
		err_cnt++;
	}
	
	if (err_cnt>0)
	{ 
		printf("\n\n**** Total Errors %d in first over.\n",err_cnt);
		return FALSE;
	}
	update_memory_address(head); /*update label adrress*/
	add2DCmem_tbl();	/*add DC table to memory word*/

	/*print_list(head);*/ /*print sybol list - for debugs*/
	/*print_DC_table();*/ /*print DC table - for debugs*/
	return TRUE;
}


/*correct_label:check if is correct label and threre is no multiply label*/
int correct_label(char *word,char *str)
{
	
	if(!isLegalLabel(word) || isSymbolExists(word)) /*check if is legal label and if the label not  already declared*/
	{	
		printf("Error in line %d: Illegal use of label %s.\n",fnum_line,word);
		err_cnt++;
		return FALSE;
	}	
	
	get_word(str,word); /*get the next word*/
	if (isEmpty(word))
	{
		printf("Error in line %d: Label %s without any statment.\n",fnum_line,word);
		err_cnt++;
		return FALSE;
	}
	
	return TRUE;

}

/*isDataSts - check if it is Data or String  or structe statment.
str- is a string to be check is Data or String guidnace statment*/
int isDataSts(char *str)
{
	if((strcmp(str,DATA_STS)==0) || (strcmp(str,STRING_STS)==0) || (strcmp(str,STRUCT_STS)==0))
		return TRUE;
	return FALSE;
}

/*isEntrySts - check if it is Entry statment.*/
int isEntrySts(char *str)
{
	if(strcmp(str,ENTRY_STS)==0 )
		return TRUE;
	return FALSE;
}


/*isExtrnSts - check if it is External statment.*/
int isExternSts(char *str)
{
	if(strcmp(str,EXTREN_STS)==0 )
		return TRUE;
	return FALSE;
}

/*fill_mem: fill memory with data, this function sent to other specific function to fill 
memory with data:threre are 3 kind of data:data strig struct*/
void fill_mem(char *word,char *str)
{
	
	if (strcmp(word,DATA_STS)==0)
	{
		add_data2mem(str);
		return;
	}
	if (strcmp(word,STRING_STS)==0)
	{
		add_string2mem(str);
		return;
	}
	
	/*the left choice is struct*/
	add_struct2mem(str);
}


/*add_data2mem: fill memory with data numbers*/
void add_data2mem(char *str)
{
	
	char word[MAX_LINE];
	int n;

	get_word(str,word);
	
	if(isEmpty(word))
	{
		printf("Error in line %d: Missing numbers \n",fnum_line);
		err_cnt++;
		return;
	}	

	while(!isEmpty(word))
	{ 
		n=convert_string2int(word);  /*convert string to integer*/
		
		/*check if number is in range*/
		if(n<MIN_NEG_NUM || n>MAX_POS_NUM)
		{
			printf("Error in line %d: number %d need to be in range(%d to %d)\n",fnum_line,n,MAX_POS_NUM,MIN_NEG_NUM);
			err_cnt++;
			return;
		}

		/*add number to dynamic table*/
		add2DC_tbl(n); 

		get_word(str,word);/*get athoner word*/
		if(isEmpty(word)) /*check for end of data*/
			return; 
		
		if(word[0]!=CH_COMMA) /*check for camma between numbers*/
		{
			printf("Error in line %d: Missing comma.\n",fnum_line);
			err_cnt++;
			return;
		}
		
		get_word(str,word);/*get athoner word*/
	}
}

/*add_string2mem: fill memory with string.*/
void add_string2mem(char *str)
{

	char word[MAX_LINE];
	int i=1;
	
	get_word(str,word);
	
	if(isEmpty(word))
	{
		printf("Error in line %d: Missing string \n",fnum_line);
		err_cnt++;
		return;
	}	
	
	/*check string begin with "*/
	if(word[0]!=CH_QUOTATION)
	{
		printf("Error in line %d: Missing begging of quotation marks \n",fnum_line);
		err_cnt++;
		return;
	}
	
	while(word[i]!=CH_QUOTATION && i<strlen(word))
	{
		add2DC_tbl(word[i]);
		i++;
	}

	/*check string end with " */
	if(word[i]!=CH_QUOTATION)
	{
		printf("Error in line %d: Missing end of quotation marks \n",fnum_line);
		err_cnt++;
		return;
	}

	/*check if is no charcter after" */
	if(word[i]!=CH_QUOTATION)
	
	/*check if there is no more prameters in line*/
	get_word(str,word);
	if(isEmpty(word))
	{
			printf("Error in line %d: There are character after quotation marks \n",fnum_line);
			err_cnt++;
			return;
	}
	
	add2DC_tbl(END_STRING); /*char \0 end of sting*/
}

/*add_struct2mem: fill memory with struct*/
void add_struct2mem(char *str)
{
	char word[MAX_LINE];
	int n;
	
	get_word(str,word);
	
	if(isEmpty(word))
	{
		printf("Error in line %d: Missing string \n",fnum_line);
		err_cnt++;
		return;
	}	
	n=convert_string2int(word);  /*convert string to integer*/
	add2DC_tbl(n); /*add number to dynamic table*/
	
	get_word(str,word);/*get athoner word*/
	if(isEmpty(word) || word[0]!=CH_COMMA) /*check for camma between numbers*/
	{
		printf("Error in line %d: Missing comma.\n",fnum_line);
		err_cnt++;
		return;
	}
		
	get_word(str,word);
	add_string2mem(word);/*second param is string*/
	
}
/*addExternSymbol-add extern dymbol to list after checking if is legal lbael
word - is thethe sybol add*/
void addExternSymbol(char *word)
{

	if (!isLegalLabel(word) || isSymbolExists(word))
	{
		printf("Error in line %d: Illegal use of label %s.\n",fnum_line,word);
		err_cnt++;
	}
	else
		add2list(&head,word,0,EXT); /*add external label to node */

}

/*isAction - check if it is Action code */
int isAction(char *str)
{
	int act;
	if ((act=get_action_code(str))==NO_ACTION)
		return FALSE;
	
	return act;
}

/*get_action code - get the number of action 
if is no action return NO_ACTION */
int get_action_code(char *str)
{
	int i=0;
	 
	while(op_action[i].txt)
	{
		if(strcmp(str,op_action[i].txt)==0)
			return i;
		i++;
	}

	return NO_ACTION;
}

/*get_num_word: calculate the number words to choosen action*/
void get_num_word(char *str,int i)
{
  	enum KIND_OPCODE n=op_action[i].num_op;/*get the number word for specific action. */
	unsigned int *pact=(unsigned int *) (&act_wrd);
	 
	/*making the first word*/
		
	*pact=0; /*reset the action word*/
	 
	act_wrd.era=ABSOLUTE;
	act_wrd.opcode=op_action[i].code;
	
	 
	if(n==NO_OP) /* action without operand*/
		complete2no_op(str,pact);
	else if(n==ONE_OP) /* action with 1 operand*/
		complete2one_op(str,i,pact);
	else if(n==TWO_OP) /* action with 2 operand*/
		complete2two_op(str,i,pact);


}

/*complete2no_op:compete word by check the action without operands*/
void complete2no_op(char *str,unsigned int *pact)
{
	char wrd[MAX_LABEL];
 
	act_wrd.dest=0; 
	act_wrd.source=0;
	mem_code[IC++]=*pact; /*increase IC*/
	get_word(str,wrd);
	if(!isEmpty(wrd))
	{
		printf("Error in line %d: not need any operand \n",fnum_line);
		err_cnt++;
	}
		
}

/*complete2one_op:compete word by check the action with 1 operands*/
void complete2one_op(char *str,int i,unsigned int *pact)
{
	char wrd[MAX_LABEL];
	char tmp[MAX_LABEL];
	Method method;
 
	get_word(str,wrd);
	if(isEmpty(wrd))
	{
		printf("Error in line %d: Missing operand/\n",fnum_line);
		err_cnt++;
		return;
	}
	
	
	get_word(str,tmp);
	if(!isEmpty(tmp))
	{
		printf("Error in line %d: Too many operands.\n",fnum_line);
		err_cnt++;
		return;
	}

	if(check_dest(wrd,i,&method))
	{
		act_wrd.source=0;
		act_wrd.dest=(unsigned int)method;
		mem_code[IC]=*pact;
		if (method==LIST_ACCESS)
			IC+=3; /*if fot LIST ACCESS there 3 word*/
		else
			IC+=2;
	}

}

/*complete2two_op:compete word by check the action with 2 operands*/
void complete2two_op(char *str,int i,unsigned int *pact)
{
	char wrd1[MAX_LINE]	;
	char wrd2[MAX_LINE]	;
	char tmp[MAX_LINE]	;
	Method method1,method2;
	 
	/*check first operans*/
	get_word(str,wrd1);
	if(isEmpty(wrd1))
	{
		printf("Error in line %d: Missing Oparand.\n",fnum_line);
		err_cnt++;
		return;
	}		

	/*check for seprt by comma*/
	get_word(str,wrd2);
	if(wrd2[0]!=CH_COMMA)	
	{
		printf("Erorr in line %d: Missing COMMA.\n",fnum_line);
		err_cnt++;
		return;
	}

	/*check second operans*/	
	get_word(str,wrd2);
	if(isEmpty(wrd2))	
	{
		printf("Error in line %d: Missing Second Oparand.\n",fnum_line);
		err_cnt++;
		return;
	}

	/*check for mul COMMA*/
	if(wrd2[0]==CH_COMMA)	
	{
		printf("Error in line %d: Multiply Comma.\n",fnum_line);
		err_cnt++;
		return;
	}

	/*check for no more parameter*/	
	get_word(str,tmp);
	if(!isEmpty(tmp))
	{
		printf("Error in line %d: Too many operand\n",fnum_line);
		err_cnt++;
		return;
	}
	
	/*checking to correct source operand*/	
	if(!check_source(wrd1,i,&method1))
	{
		printf("Error in line %d: Illegal Source Oparand %s.\n",fnum_line,str);
		err_cnt++;
		return;
	}
 
	/*checking to correct destination operand*/	
	if(!check_dest(wrd2,i,&method2))
	{
		printf("Error in line %d: Illegal Destitation Oparand %s.\n",fnum_line,str);
		err_cnt++;
		return;
	}

	/*make first word of command*/
	act_wrd.source=(unsigned int)method1;
	act_wrd.dest=(unsigned int)method2;
	mem_code[IC]=*pact
;
	IC++;
	if (method1==LIST_ACCESS)
			IC+=2; /*if fot LIST ACCESS there more 2  word*/
		else
			IC+=1;
	if (method2==LIST_ACCESS)
			IC+=2; /*if fot LIST ACCESS there more 2  word*/
		else
			IC+=1;

	if (method1==DIRECT_REG && method2==DIRECT_REG)
		IC--; /*if source & dest operand are register there combine */

}


/*check_dest:cheking for legal dest operand, return true is legal & return the method of it*/
int check_dest(char *word,int index,Method *method)
{
	int i;
	char str[MAX_LINE];
	
	i=0;
	while(i<NUM_METHOD && op_action[index].dest[i]!=NON_OPERAND)
	{
		strcpy(str,word);
		if(check_method(op_action[index].dest[i],str))
		{
			*method=op_action[index].dest[i];
			return TRUE;
		}
		i++;
	
	}
	return FALSE;
}


/*check_source:cheking for legal source operand, return true is legal & return the method of it*/
int check_source(char *word,int index,Method *method)
{
	int i;
	char str[MAX_LINE];
	
	

	i=0;
	while(i<NUM_METHOD && op_action[index].source[i]!=NON_OPERAND)
	{	
		strcpy(str,word);
		if(check_method(op_action[index].source[i],str))
		{
			*method=op_action[index].source[i]; /*get the type of addressing metod*/
			return TRUE;
		}
		i++;
	}
	return FALSE;
}

/*check_method: checking the method of source or destatin operand*/
int check_method(Method method,char * str)
{
	
  
	
	if(method==IMMEDIATE)/*check if is immediate addressing metod*/
	 return isLegalNumber(str);
		
	
	if(method==DIRECT) /*check if is direct addressing metod*/
		 return isCorrectLabel(str);/*check if is correct label */
				
		
	if(method==LIST_ACCESS) /*check if is correct list access metod*/
		return isLegalListAccess(str);
		
		
	if(method==DIRECT_REG) /*check if is correct register addressing metod*/
		return isRegister(str);
			

	

	return FALSE;

}
