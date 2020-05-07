/*This file cinsist support function*/
#include "dataStruct.h"
#include "declaration.h"
 

/*first trans: translate the program at first time */
void get_word(char *str,char* word)
{
	int i=-1,j=0;
	int flag=FALSE;
	char tmp[MAX_LINE];
	
	word[0]=END_STRING;
	if (str==NULL)
		return ;
	
	
	/*find the start char*/
	while(!flag && str[++i]!=END_STRING )
	{
		if (!isspace(str[i]))
			flag=TRUE;
 		
	}

	/*if there is no word or comma in line*/
	if (flag==FALSE)
		return;
	

	i--;
	for (j=0;(!isspace(str[++i]) && str[i]!=CH_COMMA);j++)
		word[j]=str[i];
	
	if (j==0 && str[i]==CH_COMMA)
		{strcpy(word,",");i++;}
	else 
		word[j]=END_STRING;
	
	
	/*the revome word from string*/
	strcpy(tmp,str+i);
	strcpy(str,tmp);
 
/*	printf("exit get_word:word=%s, str=%s",word,str);*/
	

}

/* isSymbol: check if is label- label have to end by :*/
int isSymbol(char *str)
{
	if(str[strlen(str)-1]==CH_COLON) /*check if the last charagter is ':' */
		return TRUE;
	return FALSE;

}


int isLegalLabel(char *str)
{
	

	if(!isCorrectLabel(str)) /*check if is correct label */
		return FALSE;
	
	
	if (isAction(str))	
	{	
		printf("Error at line %d: Illegal label %s, label can't be a Action name.\n",fnum_line,str);
		err_cnt++;
		return FALSE;
	}

	if (isRegister(str))  /*check if label is register name*/
	{	
		printf("Error at line %d: Illegal label %s, label is name saved to Register.\n",fnum_line,str);
		err_cnt++;
		return FALSE;
	}

	return TRUE;

}


int isCorrectLabel(char *str)
{
	int i;

	if(strlen(str)>MAX_LABEL)  /*check if label over the max*/
	{	
		printf("Error at line %d: label too long, the maximun label is %d.\n",fnum_line,MAX_LABEL-1);
		err_cnt++;
		return FALSE;
	}

	if(!isalpha(str[0]))		/*check if the first character is not alpha betic*/
	{	
		printf("Error at line %d: Illegal label %s, label must begin with alpha betic character.\n",fnum_line,str);
		err_cnt++;
		return FALSE;
	}
	
	for(i=1;i<strlen(str);i++) /*check if label include only numric and alpha betic*/
		if(!isalnum(str[i]))
		{	
			printf("Error at line %d: Illegal label %s, label can only include numric and alpha betic character.\n",fnum_line,str);
			err_cnt++;
			return FALSE;
		}
	return TRUE;
}


int isSymbolExists(char *str)
{
	if (isExists(head,str))
	{
		printf("Error at line %d: label %s already declared.\n",fnum_line,str);
		err_cnt++;
		return TRUE;
	}
	return FALSE;
}





/*isRegister - check if is Register.*/
int isRegister(char *str)
{
	if(get_register_num(str)!=NO_ACTION)
		return TRUE;
	
	return FALSE;
	
}
/*get_register_num:get the register number*/
int get_register_num(char *str)
{
	int i=0; 
	
	while(reg[i].name)
	{
		if(strcmp(str,reg[i].name)==0)
			return i;
		
		i++;
	}
	return NO_ACTION;
}
/*isLegalNumner: check if number is legal integer number*/
int isLegalNumber(char *str)
{
	int n;
	
	/*number begin with #*/
	if(str[0]!=CH_INIT_NUM)
		return FALSE;
			
	/*remove (#) from string*/
	str=str+1;
	n=convert_string2int(str);
	
	if(n<MIN_OP_NEG_NUM  || n>MAX_OP_POS_NUM) /*check if number is in limit*/
	{
		printf("Error at line %d: %d number is not in limit \n",fnum_line,n);
		err_cnt++;
		return FALSE;
	}
	
	return TRUE;

}

/*convert_string2int:convert string to integer num and check if is integer*/
int convert_string2int(char*str)
{
	int i;

	for(i=0;i<strlen(str);i++) /*check if label include only numric and alpha betic*/
		if(!isdigit(str[i]) && str[0]!=CH_MINUS && str[0]!=CH_PLUS)
		{
			printf("Error in line %d:ilegal number %s, number need's to be integer.\n",fnum_line,str);
			err_cnt++;
			return FALSE;
		}
		
	
	return atoi(str);

}


/*isLegelListAccess:check for legal use of list access*/
int isLegalListAccess(char *str)
{
	int i;
	char *tmp; 
	char wrd[MAX_LINE];
	int n;
    
	/*List Access must have '.' */
 	tmp= strchr(str,CH_POINT);
	if (tmp==NULL)
		return FALSE;
	strcpy(wrd,tmp+1);

	n=strlen(str)-strlen(wrd);
	str[n-1]=END_STRING;/*del charcter from '.'`*/
	
	if (!isLegalLabel(str))
		return FALSE;
	
	for(i=0;i<strlen(wrd);i++) /*check if label include only numric*/
		if(!isdigit(wrd[i]))
		{
			printf("Error in line %d:Wrong use of strct command %s.\n",fnum_line,wrd);
			err_cnt++;
			return FALSE;
		}
		
	return TRUE;
}


/*isEmpty:check if string is empty*/
int isEmpty(char * s)
{
	if(s[0]==END_STRING)
		return TRUE;
 	return FALSE;
}
