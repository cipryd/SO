#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char car = '*';
double an_plus_1 = 0;

void handle_alarm(int signum){
  if(kill(getppid(), SIGUSR1) < 0 ){
    printf("Error kill");
  
    exit(1);
  }
}

void child_function(int a0, int r, int N){
  
  int an = a0;
  const double ratio = 1 / (double) r;
  int i;
  
  struct sigaction action_alarm;
  
  action_alarm.sa_handler = handle_alarm;
  action_alarm.sa_flags = 0;
  
  sigaction(SIGALRM, &action_alarm, NULL);
  
  alarm(1);
  
  for(i = 1; i <= N; i++){
    an_plus_1 += an + ratio;
    an = an_plus_1;
  }
  
  printf("a[%d] = %f\n", N, an_plus_1);

  exit(14);
}

void print_parent(int signum){
    car = '+';
}

void end_parent(int signum){
  pid_t w;
  int status;
  
  
	  w = wait(&status);
	  if (w == -1) {
	      perror("waitpid");
	      exit(EXIT_FAILURE);
	  }

	  if (WIFEXITED(status)) {
	      printf("child pid %d exited, status=%d\n", w, WEXITSTATUS(status));
	  }
      
      
  exit(0);
}

void father(){
  struct sigaction action, end;
  
  action.sa_handler = print_parent;
  action.sa_flags = 0;
  
  end.sa_handler = end_parent;
  end.sa_flags = 0;
  
  sigaction(SIGUSR1, &action, NULL);
  sigaction(SIGCHLD, &end, NULL); 
  
}

int main(int argc, char** argv){
 
  
  pid_t pid;
  
  int a0;
  int r;
  int N;
  
  
  
  if(argc != 4){
    printf("Usage: %s a0 r N\n", argv[0]);
    exit(1);
  }
  
  if((pid = fork()) < 0 ){
   printf("Error creating child process\n");
   exit(1);
  }
  
  if(pid == 0){
   
    a0 = atoi(argv[1]);
    r = atoi(argv[2]);
    N = atoi(argv[3]);
    
    child_function(a0, r, N);
  }
  else{
    father();
    
    while(1){
      printf("%c", car);
    }
  }
  
  
  return 0;
  
}