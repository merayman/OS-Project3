#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void recursiveFunc(int checkpoint){
	if(checkpoint == 0){
		printf("%d %s\n",10," recursive call has been made check stack size \n"
				"Enter 1 to contiune 0 to return");
		int input;
		scanf("%d",&input);
		if(input == 0) return;
		else checkpoint = 10;
	}else{
		recursiveFunc(checkpoint -1);
	}
}

int main( ) {

   int size;
   int *memptr = NULL;
   pid_t pid = getpid();
 
   printf("pid= %d\n",pid);

   while(1){
	   printf( "Enter a value to allocate enter 0 to terminate -1 to recursive call: \n");
	   scanf("%d",&size);
	   if(size <= -1){
	   		int checkpoint = 10;
	   		recursiveFunc(checkpoint);
	   }
	   else if(size >0){
		   memptr = (int*) malloc(size);
		   printf( "%d byte memory allocated.\n",size);
		   //free(memptr);
		}
		else{
			if(memptr != NULL) free(memptr);
			break;
		}			
	}
   return 0;
}