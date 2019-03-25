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

  //tracks the amount of bits append to end of message block. 
  uint64_t nobits = 0;
  
  //current no of bytes read
  uint64_t nobytes; //64 bit integer used below
  
  //f is name of the file pointer
  FILE* f;
  
   
  //file open command for the first arguement provided on the command line. Argv allows you do deal with cmd line arguments
  f = fopen(argv[1], "r"); 
  //stdarg.h helps cmd line arguments for later
 
  //not at end of the file f
  while(!feof(f)){//fread deals in 64 bytes from f; reads up to not more than; M.e stores the 64 read bytes in a message block
    nobytes = fread(M.e, 1, 64, f);
    //64 - 8 check if read block is less than 55 bytes. If it is it enters this statement
    if (nobytes < 56){
      printf("I've found a block with less than 55 bytes!\n"); // prints statement to warn if it is
      //0x80 is seven zeros followed by a one on the left. Put in at the end. 
      M.e[nobytes] = 0x80;   
      while (nobytes < 56){
        nobytes = nobytes + 1;// add one to no bytes
        M.e[nobytes] = 0x00; //set all bytes to zero, between end of message up to last 8 bytes that need to be appended
      }
      // message block is array of 8, 64 bit integers, last bit element as nobits
      // works in modern c standards
	M.s[7] = nobits;

    } 
  }
    
  //closes f 		  
  fclose(f); 

  //this displays all elements of M as 64 bytes in hex
  for (int i = 0; i < 64; i++)
  printf("%x ", M.e[i]);
  printf("\n");

 
  //return statement 	 
  return 0;
}
