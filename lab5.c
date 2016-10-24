#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

void parseDirectories(struct dirent current, char[] path){
  const char pathName;
  
  pathName = malloc(strlen(path));
  
  strcpy(pathName, path);
  strcat(pathName, current.d_name);
  
  printf("%s", pathName);
  
}

int main(int argc, char* argv[]){
 struct stat *buf;
 char *dir;
 DIR *directory;
 
  if(argc < 3){
    printf("ERROR Usage: %s DIR NUM\n", argv[0]);
    return 1;
  }
    
    buf = malloc(sizeof(stat));
    dir = malloc(sizeof(char));
    
    strcpy(dir, argv[1]);
    
      if(lstat(dir, buf) == 0){
	if(S_ISDIR(buf->st_mode)){
	  
	  directory = opendir(dir);
  
	  if(!directory){
	    printf("Error Open Directory ");
	    return 1;
	  }else{
	    
	   parseDirectories(directory, dir); 
	  }	    
	}
	else{
	  printf("ERROR Not a Directory"); 
	}
      }
      else{
	printf("ERROR Directory not found\n");
	return 1;
      }

  
  
 return 0; 
}