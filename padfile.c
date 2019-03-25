#include <stdio.h>
#include <stdint.h>

//Unions are similar to structs but allow elements to be stored at the same memory location
union msgblock{
  uint8_t e[64]; //64 element array of 8 bit integers = 512 byte message block
  uint32_t t[16]; //16 element array of 32 bit integers = 512 byte message block
  uint64_t s[8]; //8 element array of 64 bit integers = 512 bit message block
};


int main(int argc, char *argv[]) {
  
  //f is name of the file
  FILE* f;
  
  //c character is used to read file
  char c;
  
  //file open command for the first arguement provided on the command line. Argv allows you do deal with cmd line arguments
  f = fopen(argv[1], "r"); 
  //stdarg.h helps cmd line arguments for later
 
  //prints out the first, single character (c) read from pointer in from the file f. fread deals in bytes, One byte - One time
  printf("%c\n", fread(&c, 1, 1, f);
  
  //closes f pointed at 		  
  fclose(f); 

  //return statement 	 

  return 0;
}
