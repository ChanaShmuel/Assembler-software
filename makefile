assembler :  assembler.o firstTranslate.o secondTranslate.o supportFunc.o list.o dynamicArr.o fileFunc.o
	gcc -g -ansi -Wall -pedantic assembler.o firstTranslate.o secondTranslate.o supportFunc.o list.o dynamicArr.o fileFunc.o -o assembler

assembler.o :assembler.c global_var.h const.h dataStruct.h declaration.h
	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.o

firstTranslate.o :firstTranslate.c global_var.h  dataStruct.h  const.h 
	gcc -c -ansi -Wall -pedantic firstTranslate.c -o firstTranslate.o

secondTranslate.o :secondTranslate.c global_var.h  dataStruct.h  const.h 
	gcc -c -ansi -Wall -pedantic secondTranslate.c -o secondTranslate.o

supportFunc.o :supportFunc.c const.h  declaration.h dataStruct.h 
	gcc -c -ansi -Wall -pedantic supportFunc.c -o supportFunc.o

list.o :list.c const.h  declaration.h dataStruct.h 
	gcc -c -ansi -Wall -pedantic list.c -o list.o

dynamicArr.o :dynamicArr.c const.h  declaration.h dataStruct.h 
	gcc -c -ansi -Wall -pedantic dynamicArr.c -o dynamicArr.o

fileFunc.o :fileFunc.c const.h  declaration.h dataStruct.h 
	gcc -c -ansi -Wall -pedantic fileFunc.c -o fileFunc.o


