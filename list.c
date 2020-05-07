/*This is a model of list node*/
#include "dataStruct.h"
#include "declaration.h"


/*add2list: add data to node at the first list*/
void add2list(pSymbol * phead,char *str,int ic,enum ECD ecd)
{
	pSymbol p;
	p=(pSymbol)malloc(sizeof(symbol));
	strcpy(p->txt,str);
	if (ecd==EXT)
		p->address=ic;  /*for erternal address, value address cooming with 0*/
	else
		p->address=ic+START_ADDRESS; /*add offset to address*/
	
	p->kind_ad=ecd; 
	
	/*add a node to empty list*/
	if(phead==NULL)
	{	
		p->next=NULL;
		*phead=p;
	}
	else /*add a node to list*/
	{
		p->next=*phead;
		*phead=p;
	}
	
}



/*isExists: check if label exsist in list*/
int isExists(pSymbol p,char *name)
{
	while(p)
	{
		if(strcmp(p->txt,name)==0)
			return TRUE;
		p=p->next;
	}
	return FALSE;
}


/*update_address: update the address of label DATA to ended location*/
void update_memory_address(pSymbol head)
{
	while(head)
	{	/*update the address of type data to exact location*/
		if(head->kind_ad==DATA)
			head->address=head->address+IC;
		head=head->next;
	}	
}

/*free_list: free memory*/
void free_list(pSymbol * phead)
{
	pSymbol p;
	while(*phead)
	{	
		p=*phead;
		*phead=(*phead)->next;
		free(p);
	
	}
}

/*get_kind_ad: get kind of addrees method(data, code, external)
head- is pointer to head of list
str is string label is kind addreesing method iswanted
return the kind address of label*/
unsigned int get_kind_ad(pSymbol head ,char *str)
{

	while(head && strcmp(head->txt,str)!=0)
		head=head->next;
	
	if(head->kind_ad==EXT) 
		return (unsigned int )EXTERNAL;
	else
		return (unsigned int )RELOCATE;

}

/*get_address: get the addrres of label*/
unsigned int get_address(pSymbol head ,char *str)
{

	while(head && strcmp(head->txt,str)!=0)
		head=head->next;

	return (unsigned int)head->address;

}

/*print_list: print all list - this function need for debugs*/
void print_list(pSymbol head)
{
	puts("the memory lable");
	while(head)
	{
		printf("label:%s\taddress:%d\tkind:%d\n",head->txt,head->address,head->kind_ad);
		head=head->next;
	}	
}


