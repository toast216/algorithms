#include <omp.h> 
#include <stdio.h>
#include "common.h"


int **weights;
int N,M;

void set_value(int row,int col,int value);
int get_value(int row,int col);
int average_chunk;
int max_threads;

int main(int argc, char **argv)
{

        if(argc<3) 
	{
                printf("Usage:progname filename1 filename2 num_threads\n"); 
                exit(1);
        }

        max_threads = atoi(argv[3]);
        char *string1 = read_data(argv[1]);
        char *string2 = read_data(argv[2]);

        omp_set_num_threads(max_threads);
        N= strlen(string1)+1;
        M= strlen(string2)+1;

        weights = (int **) malloc(M*sizeof(int *));
        int i=0,j=0;
        for(i=0;i<M;i++){
                weights[i] = (int *)malloc(N*sizeof(int));
                for(j=0;j<N;j++){
                        weights[i][j]= 0;
                }
        }
        
        average_chunk = (N/max_threads)+1 ;
        
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	#pragma omp parallel  shared(weights,string1,string2,average_chunk) 
	{
        	int i=0,j=0;
        	for(i=1;i<M;i++)
		{
			#pragma omp parallel for schedule(dynamic,average_chunk) shared(weights,string1,string2,average_chunk) num_threads(max_threads)
                	for(j=1;j<N;j++)
			{
	                        if(string2[i-1]==string1[j-1])
				{
                                set_value(i,j,get_value(i-1,j-1)+1);
                        }
			else
			{
                                set_value(i,j,max(get_value(i-1,j),get_value(i,j-1)));
                        }
                }
        }
}

        printf("The final weight = %d\n",weights[M-1][N-1]);
	gettimeofday(&t2,NULL);
        int total_seconds = (t2.tv_sec - t1.tv_sec)*1000000 +
                            (t2.tv_usec - t1.tv_usec);

        printf("total time taken to calculate matrix = %f\n",total_seconds/1000000.0);
        output_lcs(weights,string1,string2);
        free(weights);
        free(string1);
        free(string2);
}


int get_value(int row,int col)
{
        int value = -1;
        value = weights[row][col];
        return value;
}

void set_value(int row,int col,int value)
{
        weights[row][col] = value;
}
