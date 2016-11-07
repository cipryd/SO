#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv){
  int i;
  int j;
  int pid;
  int n;
  int status;
  int w;
  
  if(argc < 4){
      printf("Usage: %s <file> <nr1> ...", argv[0]);
      exit(1);
  }
   
  for(i = 2; i < argc; i++){
      if((pid = fork()) < 0){
	perror("Eroare fork()");
	exit(1);
      }
      
      if(pid == 0){
	n = atoi(argv[i]);
	
	for(j = 1; j <= n; j++)
	  printf("%d: %d\n", getpid(), j);
	  
	exit(0);
      }
  }
  
  if((pid = fork()) < 0){
	perror("Eroare fork()");
	exit(1);
      }
      
      if(pid == 0){
	execlp("grep", "grep", "if", argv[1], NULL);
	printf("Error execlp\n");
	exit(1);
      }
      


  for(i = 1; i < argc; i++){
   do {
	  w = wait(&status);
	  if (w == -1) {
	      perror("waitpid");
	      exit(EXIT_FAILURE);
	  }

	  if (WIFEXITED(status)) {
	      printf("exited, status=%d\n", WEXITSTATUS(status));
	  } else if (WIFSIGNALED(status)) {
	      printf("killed by signal %d\n", WTERMSIG(status));
	  } else if (WIFSTOPPED(status)) {
	      printf("stopped by signal %d\n", WSTOPSIG(status));
	  } else if (WIFCONTINUED(status)) {
	      printf("continued\n");
	  }
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
	       
  
   
   
  
  return 0;
}