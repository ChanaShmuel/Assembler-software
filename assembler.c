#include "dataStruct.h"
#include "declaration.h"
#include "global_var.h"
  
int main(int argc , char *argv[])
{
	
	FILE *fin;
	char name[MAX_FILE_NAME];
	
	if(argc==1)
	{
		printf("\nNot given a file to translate \n"); 
		exit(0);
	}

	while(--argc)
	{	
		/*built name file with .as */
		strcpy(name,argv[argc]); 
		strcat(name,SUFFIX_AS);
		printf("\nChecking file %s\n",name);
		/*open file to readd assemply program to translate*/
		if(!(fin=fopen(name,"r")))
		{
			fprintf(stderr,"can't open file %s for reading\n",name);
			continue;
		}
		

		err_cnt=0;
		if (first_trans(fin))  /*first translate*/
		{
			fseek(fin,0,SEEK_SET); /*return to begging of file*/
			if (second_trans(fin)) /*second translate*/
			{
				save_tbl2file(tbl_ent,ent_cnt,argv[argc],SUFFIX_ENT); /*write entry table to file .ent*/
				save_tbl2file(tbl_ext,ext_cnt,argv[argc],SUFFIX_EXT); /*write external table to file .ext*/
				save_mem_code2file(argv[argc],SUFFIX_OB); /*write program to file .ob*/
			}
		}
		fclose(fin);/*close file*/
		
		/*free memory*/
		free_list(&head);
		free(tbl_ent); 
		free(tbl_data);
		free(tbl_ext);
		
	}

	return 1;
	
}
