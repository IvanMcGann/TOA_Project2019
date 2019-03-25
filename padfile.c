#include <stdio.h>
#include <stdint.h>

//Unions are similar to structs but allow elements to be stored at the same memory location
union msgblock{
  uint8_t e[64]; //64 element array of 8 bit integers = 512 byte message block
  uint32_t t[16]; //16 element array of 32 bit integers = 512 byte message block
  uint64_t s[8]; //8 element array of 64 bit integers = 512 bit message block
};


int main(int argc, char *argv[]) {
  
  //message block instance defined above defined union
  union msgblock M;
  //64 bit integer used below
  uint64_t nobytes;

  //f is name of the file pointer
  FILE* f;
  
   
  //file open command for the first arguement provided on the command line. Argv allows you do deal with cmd line arguments
  f = fopen(argv[1], "r"); 
  //stdarg.h helps cmd line arguments for later
 
  //not at end of the file f
  while(!feof(f)){//fread deals in 64 bytes from f; reads up to not more than; M.e stores the 64 read bytes in a message block
    nobytes = fread(M.e, 1, 64, f);
    printf("%llu\n", nobytes); // prints the 64 bytes read in long long unsigned integer.
  }
  //closes f 		  
  fclose(f); 
 
  //return statement 	 
  return 0;
}
