#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main( ) {

   int size;
   int *memptr = NULL;
   pid_t pid = getpid();
 
   printf("pid= %d\n",pid);

   while(1){
	   printf( "Enter a value to allocate enter <=0 to terminate: \n");
	   scanf("%d",&size);
	   if(size >0){
		   if(memptr != NULL) free(memptr);
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