#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int recursiveFunc(int n){
	int intt[1000];
	printf("Stack at %p\n", (void*)(&intt));
	if(n>0)
		recursiveFunc(n-1);
	else{
		int stack_iteration;
		printf( "Enter number of recursive call greater than 0, to exit enter number less than 0! \n");
		scanf("%d",&stack_iteration);
		//int checkpoint = 100;
		if(stack_iteration > 0)
			recursiveFunc(stack_iteration);
		if(stack_iteration <= 0)
			return;
	}
}
int main() {
   int size;
   int *memptr = NULL;
   pid_t pid = getpid();
   int stack_iteration;
 
   printf("pid= %d\n",pid);

   while(1){
	   printf( "Enter a value to allocate, enter 0 to terminate, -1 to recursive call: \n");
	   scanf("%d",&size);
	   if(size <= -1){
		   printf( "Enter number of recursive call greater than 0! \n");
		   scanf("%d",&stack_iteration);
	   	   //int checkpoint = 100;
	   	   recursiveFunc(stack_iteration);
	   }
	   else if(size >0){
		   memptr = (int*) malloc(size);
		   printf( "%d byte memory allocated.\n",size);
		}
		else{
			if(memptr != NULL) free(memptr);
			break;
		}			
	}
   return 0;
}
