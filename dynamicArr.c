/*This is a model of Dymenic array node*/
#include "dataStruct.h"
#include "declaration.h"

/*add2DC_table:add data to DC table
n- is the data to add*/
void add2DC_tbl(int n)
{
	tbl_data=(ptblData)realloc(tbl_data,(DC+1)*sizeof(tblData));
	if(!tbl_data)
	{
		printf("\n cannot have build a list");
		exit(0);
	}
	/*number <0 make complete to 2*/
	if (n<0)
		tbl_data[DC].data=NUM_10BITS+n; /*convert to complete 2*/
	else
		tbl_data[DC].data=n;
	tbl_data[DC].address=DC;
	DC++;
	
}

/*add_DC_table2mem: add DC data table to memory tranlate code*/
void add2DCmem_tbl()
{
	int i;
	
	for (i=0;i<DC;i++)
		mem_code[IC++]=tbl_data[i].data;

}

/*print DC_table -for debugs*/
void print_DC_table()
{
	int i;
	for(i=0;i<DC;i++)
		printf("data:%d\taddress:%d\n",tbl_data[i].data,tbl_data[i].address);
		
}


/*add2lbl_table:add data to lable table for entry and extearnal data*/
void add2lbl_tbl(ptblLabel p,int *c,char *str)
{	
	p=(ptblLabel)realloc(p,((*c)+1)*sizeof(tblLabel));
	if(!p)
	{
		printf("\n cannot have build a list");
		exit(0);
	} 
	strcpy(p[*c].name,str);
	
	p[*c].address=get_address(head,str);
	(*c)++;

}
