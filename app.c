#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int recursiveFunc(int n){
	if (n == 0 || n == 1){
		int a = 0;
		return n;
	}
	else{
		int result = recursiveFunc(n-1) + recursiveFunc(n-2);
		if(result > 6700){
			printf("%s\n","check the stack size then enter 0 to return");
			int a = 0;
			scanf("%d",&a);
		}
	}
}
int main() {
   int size;
   int *memptr = NULL;
   pid_t pid = getpid();
 
   printf("pid= %d\n",pid);

   while(1){
	   printf( "Enter a value to allocate enter 0 to terminate -1 to recursive call: \n");
	   scanf("%d",&size);
	   if(size <= -1){
	   		int checkpoint = 20;
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
