/*This is second translate MOdel*/
/*this model over the assembly program at second time as check for legal write and make 
.ob file .ent entry file and .ext table of data extearnal file*/
#include "dataStruct.h"
#include "declaration.h"
 

 
/*second trans: translate the program at first time */
int second_trans(FILE *f)
{
	
 	char str[MAX_LINE];
	char word[MAX_LABEL];
	
	int flag_smbl;  /*flag for smbol */
	int inx_act;
	
	IC=0;   
	fnum_line=0; 
	
	declare_dynamic_tbl();
	
	printf("\nSecond translate\n");
	while(!feof(f) && fgets(str,MAX_LINE,f)!=NULL)
	{
		fnum_line++;
		flag_smbl=FALSE;
		if (str[0]==REMARK) continue;  /*ignore from remark line*/
		
		get_word(str,word); 
		if (isEmpty(word))
			continue;  /*ignore from line empty*/
	
		if ((flag_smbl=isSymbol(word))==TRUE)  /*check if is label*/
			get_word(str,word); 
		
		/*check for .data or .string .struct .extern  statment*/
		if  (isDataSts(word) || isExternSts(word)) 
			continue;
	
		/*check is statment is .entry*/
		if(isEntrySts(word)) 
		{	
			get_word(str,word); /*get label of entry*/
			add2ent_tbl(word);
			continue;  
		}
		
		if((inx_act=get_action_code(word))!=NO_ACTION)
			build_next_words(str,inx_act);
		 	
		
	}
	
	if (err_cnt>0)
	{ 
		printf("\n\n**** Total Errors %d in Second over.\n",err_cnt);
		return FALSE;
	}
		
	
	return TRUE;
}

/*declare_dynamic_tbl:declare dynamic tbl for extern & extern labels*/
void declare_dynamic_tbl()
{
	tbl_ext=(ptblLabel)malloc(sizeof(tblLabel)); /*build dynamic array for external address*/
	if(!tbl_ext)
	{
		printf("\n cannot have build a list");
		exit(0);
	}
	tbl_ent=(ptblLabel)malloc(sizeof(tblLabel));/*build dynamic array for entry address*/
	if(!tbl_ent)
	{
		printf("\n cannot have build a list");
		exit(0);
	}
	ext_cnt=0; /*init external counter to 0 for external table*/
	ent_cnt=0;/*init entry counter to 0 for eentry table*/

}

/*add2ent_tbl:add label to entry array for making at end entry file
str is the label to add*/
void add2ent_tbl(char *str)
{
	
	/*check if is label for entry statment*/
	if(isEmpty(str))
	{	
		printf("Error in line %d: .entry has no label .\n",fnum_line);
		err_cnt++;
		return;		
	}

	/*check if is label allready declared*/
	if (!isExists(head,str))
	{	
		printf("Error at line %d: label %s is not declared.\n",fnum_line,str);
		err_cnt++;
		return;		
	}
			
	/*add new value in list to entry table*/
	add2lbl_tbl(tbl_ent,&ent_cnt,str);
			
}


/*build_other_word: make the second & third &fourth word for action*/
void build_next_words(char * str,int inx)
{
	IC++;  /*first word already translate in first translation*/
	
	/*action with no operand(stop/rst) - not need any more translation*/
	if (op_action[inx].num_op==NO_OP)
		return;
		
	/*caction with 1 operand*/
	if (op_action[inx].num_op==ONE_OP)
		build_word2one_op(str,inx);	
		

	/*caction with 2 operand*/
	if (op_action[inx].num_op==TWO_OP)
		build_word2two_op(str,inx);	 
	
}

/*build_word2one_op:build the code word for action with 1 operand*/
void build_word2one_op(char *str,int inx)
{
	Method method;
	int num;
	char wrd[MAX_LINE];
	unsigned int *pwrd=(unsigned int *) (&cpu_wrd);
	
	*pwrd=0;
	
	get_word(str,wrd);
	check_dest(wrd,inx,&method);/*find the metod of operand*/
	fill_next_word(wrd,inx,method,&num);/*make the word*/
	if (method==DIRECT_REG) /*code for DIRECT_REG build here*/
	{
		cpu_wrd.dest_reg=(unsigned int)num;
		mem_code[IC++]=*pwrd;/*save the code in table array*/
	}
}

/*build_word2two_op:build the code word for action with 2 operand*/
void build_word2two_op(char *str, int inx)
{
	Method method_s,method_d;
	unsigned int *pact=(unsigned int *) (&act_wrd);
	unsigned int *pwrd=(unsigned int *) (&cpu_wrd);
	char wrd_s[MAX_LINE];
	char wrd_d[MAX_LINE];
	int value_s,value_d;

	*pact=0;
	*pwrd=0;
	
	get_word(str,wrd_s);
	get_word(str,wrd_d);/*is COMMA*/
	get_word(str,wrd_d);/*ignore COMMA*/
	check_source(wrd_s,inx,&method_s); /*get the method of source operand*/
	check_dest(wrd_d,inx,&method_d);  /*get the method of dest operand */
	
	fill_next_word(wrd_s,inx,method_s,&value_s); /*get translation for source register*/
	if (method_s==DIRECT_REG) /*code for DIRECT_REG build here*/
	{
		cpu_wrd.source_reg=(unsigned int)value_s;
		mem_code[IC++]=*pwrd;/*save the code in table array*/
	}
	fill_next_word(wrd_d,inx,method_d,&value_d); /*get translation for dest register*/	
	if (method_d==DIRECT_REG) 
	{		
				
		if (method_s==DIRECT_REG)
			 IC--; /*if both operand are register there is only 1 onother word*/
		cpu_wrd.dest_reg=(unsigned int)value_d;
		mem_code[IC++]=*pwrd; /*save the word in array*/
	}
	
	
	
}

/* fill_next_word:translate other next words*/
void fill_next_word(char *str,int inx,Method method,int *value)
{	
	int n;
	unsigned int *pwrd=(unsigned int *)(&cpu_wrd);

	switch(method)
	{
		case IMMEDIATE:	/*Immediate method*/
						str=str+1; /*del # from number sting*/		
						n=convert_string2int(str);
						if(n<0)
							*pwrd=(unsigned int)(((NUM_OP_8BITS+n)<<2)+ABSOLUTE); /*complete to 2*/
						else
							*pwrd=(unsigned int)((n<2)+ABSOLUTE);
						mem_code[IC++]=*pwrd;/*save the code in table array*/
						break;
		
		case DIRECT: /*Direct method*/	
						make_direct_word(str);				
						 break;
		
		case LIST_ACCESS:/*list access method*/
						make_list_access_word(str);
						break;
		
		case DIRECT_REG:/*register method*/										
					cpu_wrd.era=ABSOLUTE;
					*value=get_register_num(str); 
					break;
		
		case NON_OPERAND:
					break;
		
	}


}

/* make_direct_word:make direct word for surce and dest operand*/
void make_direct_word(char* str)
{
	unsigned int *pwrd=(unsigned int *)(&cpu_wrd);
	int num;

	*pwrd=0;	
	if (!isExists(head,str)) /*check if label exists*/
	{	
		printf("Error in line %d: label %s is not found.\n",fnum_line,str);
		err_cnt++;
		return;		
	}
					
	/*check if label is external*/
	
	num=get_kind_ad(head,str);
	
	*pwrd=(get_address(head,str)<<2)+num;
	mem_code[IC++]=*pwrd;/*save the code in table array*/
 	if (num==EXTERNAL) /*add new value in list to external table*/
 	{	
		tbl_ext=(ptblLabel)realloc(tbl_ext,(ext_cnt+1)*sizeof(tblLabel));
		if(!tbl_ext)
		{
			printf("\n cannot have build a list");
			exit(0);
		} 
		strcpy(tbl_ext[ext_cnt].name,str);
		tbl_ext[ext_cnt++].address=IC+START_ADDRESS-1;
		
	}

	
}

/*make_list_access_word:make 2 words for list access method for both source or dest operand
str-is the operand need to be codeing*/
void make_list_access_word(char * str)
{
	int era;
	int n;
	unsigned int *pwrd=(unsigned int *)(&cpu_wrd);
	char wrd[MAX_LINE];
	char *tmp;

	tmp= strchr(str,CH_POINT);
	strcpy(wrd,tmp+1);
	n=strlen(str)-strlen(wrd)-1;
	str[n]=END_STRING;/*del charcter from '.'`*/
	make_direct_word(str);
	n=convert_string2int(wrd);
	era=ABSOLUTE;
	*pwrd=(n<<2)+era;
	mem_code[IC++]=*pwrd;/*save the code in table array*/

}

