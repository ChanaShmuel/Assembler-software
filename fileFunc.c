/*****this is File Functons node model***** 
all functions are relative with write o file are here*/
#include "dataStruct.h"
#include "declaration.h"

/*save_tbl2file: write table details to file*/
void save_tbl2file(ptblLabel plbl,int last,char *name,char *suffix)
{
	FILE *fout;
	int i;
	char fname[MAX_FILE_NAME];
	char str[BASE32_CODE];

	/*combine the name file with suffix*/
	strcpy(fname,name);
	strcat(fname,suffix);
		
	printf("make file %s....\n",fname);
	/*open file for writing*/
	if(!(fout=fopen(fname,"w")))
	{
		fprintf(stderr,"can't open file %s for write.\n",fname);
		return;
	}
	
	/*write to file*/
	for (i=0;i<last;i++)
	{
		convert2base32(plbl[i].address,str); /*convert to special base 32 code*/
		fprintf(fout,"%s  %s\n",plbl[i].name, str); 
	}


	fclose (fout); 
	
}

/*save_mem_code2file: write assembly code to file .ob
name: is name file to write
suffix: is the suffix of file -ob*/
void save_mem_code2file(char *name,char *suffix)
{
	FILE *fout;
	int i;
	char fname[MAX_FILE_NAME];
	char str[BASE32_CODE];
	char str1[BASE32_CODE];


	/*combine the name file with suffix*/
	strcpy(fname,name);
	strcat(fname,suffix);
	
	printf("make file %s ....\n",fname);
	/*open file for writing*/
	if(!(fout=fopen(fname,"w")))
	{
		fprintf(stderr,"can't open file %s for write.\n",fname);
		return;
	}

	/*write IC & DC to file*/
	convert2base32(IC,str);
	convert2base32(DC,str1);
	fprintf (fout,"\t%s\t%s\n",str,str1);
		
	
	/*write all assemly code to file address & code*/
	for (i=0;i<IC;i++)
	{ /*printf("\n i=%d  code=%d",i,mem_code[i]);*/
		convert2base32(i+START_ADDRESS,str); /*convert addressto special base 32 code*/
		convert2base32(mem_code[i],str1);/*convert data to special base 32 code*/
		fprintf (fout,"%s  %s\n",str,str1);
	}
	
	/*write Data at the end of program*/
	for (i=IC;i<IC+DC;i++)
	{	
		convert2base32(i+START_ADDRESS,str); /*convert addressto special base 32 code*/
		convert2base32(mem_code[i],str1); /*convert data to special base 32 code*/
		fprintf (fout,"%s  %s\n",str,str1);
	}
	
	fclose (fout);
}

/*convert2base32:convert number to base 32*/
void convert2base32(int num, char *str)
{	
	int i=0;
	int n;
	
	n=num/BASE32;
	
	str[i++]=StrangeCode[n];
	str[i]=StrangeCode[num%BASE32];

	
	str[BASE32_CODE-1]=END_STRING;  /*end of string*/
	
}
