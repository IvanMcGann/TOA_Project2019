#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
  
  //f is name of the file
  FILE* f;
  
  //c character is used to read file
  char c;
  
  //file open command for the first arguement provided on the command line
  f = fopen(argv[1], "r"); 
  //stdarg.h helps cmd line arguements for later
 
  //prints out the first, single character (c) read from pointer in from the file f
  printf("%c\n", fread(&c, 1, 1, f);
  
  //closes f pointed at 		  
  fclose(f); 

  //return statement 	 

  return 0;
}
