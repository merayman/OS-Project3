#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int recursiveFunc(int n){
	int intt[1000];
	printf("Stack at %p\n", (void*)(&intt));
	if(n>0)
		recursiveFunc(n-1);
	else
		return;
	
}
int main() {
   int size;
   int *memptr = NULL;
   pid_t pid = getpid();
 
   printf("pid= %d\n",pid);

   while(1){
	   printf( "Enter a value to allocate, enter 0 to terminate, -1 to recursive call: \n");
	   scanf("%d",&size);
	   if(size <= -1){
	   		int checkpoint = 100;
	   		recursiveFunc(checkpoint);
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
