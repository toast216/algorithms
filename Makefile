LCS:LCS.c helper.o
	gcc LCS.c helper.o -o LCS -g 
common.o:helper.h helper.c
	gcc  -c helper.c
clean:
	rm -rf *.o LCS
