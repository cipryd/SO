#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>

int main(int argc, char** argv){
 
  pid_t pid;
  pid_t pid2;
  pid_t pid3;
  
  int pfd[2];
  int pfd2[2];
  
  int fd;
  
  char buf;
  
  int count_fiu_1 = 0;
  int count_fiu_2 = 0;
  
  int i;
  int wc;
  
  pid_t w;
  int status;
  
  if(argc != 2){
   printf("Usage: %s file\n", argv[0]);
    exit(1);
  }
  
  if(pipe(pfd) < 0){
    printf("Eroare creare pipe\n");
    exit(1);
  }
  
  if(pipe(pfd2) < 0){
    printf("Eroare creare pipe\n");
    exit(1);
  }
	
  if( (pid = fork()) < 0){
    printf("Eroare la fork\n");
    exit(1); 
  }
  
  if(pid == 0){		//fiu 1
   close(pfd[1]);
   close(pfd2[0]);
   close(pfd2[1]);
   
   while( read(pfd[0], &buf, 1) == 1){
     count_fiu_1++;
   }
   
   close(pfd[0]);
   exit(count_fiu_1); 
  }
  else{			 //parinte
  
	if( (pid2 = fork()) < 0){
	printf("Eroare la fork\n");
	exit(1); 
	}
	
	if(pid2 == 0){		//fiu 2
	
	  close(pfd[1]);
	  close(pfd[0]);
	  close(pfd2[1]);
	    	
	  while( read(pfd2[0], &buf, 1) == 1){
	    //printf("%c \n", buf);
	    count_fiu_2++;
	  }
	  
	  close(pfd2[0]);
	
	
	exit(count_fiu_2); 
	}
	else{			//parinte
	  
	      if( (pid3 = fork()) < 0){
		printf("Eroare la fork\n");
		exit(1); 
	      }
	
	      if(pid3 == 0){		//fiu 3
	      
		close(pfd[1]);
		close(pfd2[0]);
		close(pfd2[1]);
		close(pfd[0]);	
		
		wc = execlp("wc", "wc", "-w", argv[1], NULL);
		
		
		exit(0); 
	      }
	      			//parinte
		  
		  close(pfd[0]);
		  close(pfd2[0]);
  
	      	fd = open(argv[1], O_RDONLY);
  
		if(fd < 0){
		printf("Error: opening file: %s\n", argv[1]); 
		  exit(1);
		}
  
		while( read(fd, &buf, 1) == 1){
		  
		      
		      
		      if(isalpha(buf)){
		  
			write(pfd[1], &buf, 1);
			
			if(islower(buf)){
			  write(pfd2[1], &buf, 1);
			}
			
		      }
	      }
  
      close(pfd[1]);
      close(pfd2[1]);
	
	close(fd);
	}     
  }
  
  for(i = 0; i < 3; i++){
    
    
    w = wait(&status);
	      
    
    if (w == -1) {
	    perror("wait");
	    exit(EXIT_FAILURE);
	}

	if (WIFEXITED(status)) {
	    printf("pid:%d exited, status=%d\n",w , WEXITSTATUS(status));
	} else if (WIFSIGNALED(status)) {
	    printf("killed by signal %d\n", WTERMSIG(status));
	} else if (WIFSTOPPED(status)) {
	    printf("stopped by signal %d\n", WSTOPSIG(status));
	} else if (WIFCONTINUED(status)) {
	    printf("continued\n");
	}

  }
  
  return 0;
}