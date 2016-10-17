#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


/*

./lab4 file path

make a new file in the given path that contains only even nr

*/


int main(int argc, char *argv[]){
  
  
  if(argc < 3){
	const char msg[] = "Eroare argumente\n";
	write(STDERR_FILENO, msg, sizeof(msg));  
	return 1;
  }else{
    int input = open(argv[1], O_RDONLY);
    
    if(input == -1){
      const char msg[] = "Eroare deschidere fisier\n";
      write(STDERR_FILENO, msg, sizeof(msg));  
      return 1;
    }
    
    
    char file_dir[125] = "";
    
    strcat(file_dir, argv[2]);
    strcat(file_dir, "/");
    strcat(file_dir, argv[1]);
    
    int file = open(file_dir, O_RDONLY | O_WRONLY | O_CREAT | O_TRUNC);
    
    if(file == -1){
      const char msg[] = "Eroare creare fisier\n";
      write(STDERR_FILENO, msg, sizeof(msg));  
      return 1;
    }
    
    char *buffer = malloc(sizeof(char));
    int read_return;
    
    while((read_return = read(input, buffer, 1)) != 0){
      if(read_return == -1){
	const char msg[] = "Eroare citire din fisier\n";
	write(STDERR_FILENO, msg, sizeof(msg));  
      }
      
      if(isdigit(buffer))			//???
	;
    }
  }
  /*
  unlink("./link1")
  symlink(path, "./link1)
  stat/fstat/lstat
  
  struct stat buf 
  if(lstat("./link1", &buf) < 0)
    
    buf.st_size
  */
  return 0;
}
