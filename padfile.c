#include <stdio.h>
#include <stdint.h>

// Unions are similar to structs but allow elements to be stored at the same memory location
  union msgblock{
   uint8_t e[64]; //64 element array of 8 bit integers = 512 byte message block
   uint32_t t[16]; //16 element array of 32 bit integers = 512 byte message block
   uint64_t s[8]; //8 element array of 64 bit integers = 512 bit message block
  };

  //similar to a short integer, used to flag the current status of the message
  enum status {READ, PAD0, PAD1, FINISH};

  int main(int argc, char *argv[]) {
  
   // message block instance defined above defined union
   union msgblock M;

   // tracks the amount of bits append to end of message block. 
   uint64_t nobits = 0;
  
   // current no of bytes read
   uint64_t nobytes; //64 bit integer used below

   //status at the start is reading 
   enum status S = READ;
  
   // f is name of the file pointer
   FILE* f;
  
   // file open command for the first arguement provided on the command line. Argv allows you do deal with cmd line arguments
   f = fopen(argv[1], "r"); 
   // stdarg.h helps cmd line arguments for later
 
   int i;

   // current status is still at reading the file
   while(S == READ){
     // fread deals in 64 bytes from f; reads up to not more than; M.e stores the 64 read bytes in a message block
     nobytes = fread(M.e, 1, 64, f);
     // 64 - 8 check if read block is less than 55 bytes. If it is it enters this statement
     if (nobytes < 56){
       printf("I've found a block with less than 56 bytes!\n"); // prints statement to warn if it is
       // 0x80 is seven zeros followed by a one. Put in at the end. 
       M.e[nobytes] = 0x80;   
       while (nobytes < 56){//while loop keeps going until it reaches 64
         nobytes = nobytes + 1;// add one to no bytes

         M.e[nobytes] = 0x00; // set all bytes to zero, between end of message up to last 8 bytes that need to be appended
       }
      // message block is array of 8, 64 bit integers, last bit element as nobits
      // works in modern c standards to read from same union
   	 M.s[7] = nobits;
	 S = FINISH;//status is set to finish
     } 
      else if(nobytes < 64){//extra message block for padding
        S = PAD0; //pad0 stands for all zeros for padding
  	M.e[nobytes] = 0x90;// one appended to message
       while (nobytes < 64){
	nobytes = nobytes + 1;
	M.e[nobytes] = 0x00;//add all zeroes
       }   
      }
	else if (feof(f)){ //if file is finished being read and was a multiple of 512 bits
	S = PAD1;//still padding required
	}   
   }

   if (S==PAD0 || S == PAD1){
       for(i=0; i <56; i++)//while i is less than 56 
	  M.e[i] = 0x00; 
	  M.s[7] = nobits; //fill in with zeroes
   }//if status is PAD0 add a block of padding 448 bits of zeroes and last 8 bytes is 64 bit big endian integer representing the no of bits in the original message
   else if (S==PAD1){
      M.e[0] = 0x08; //first bit of message block is a one for PAD1 and zero for PAD0
   }
    
   // closes file f 		  
   fclose(f); 

   // this displays all elements of M as 64 bytes in hex
   for (int i = 0; i < 64; i++)
   printf("%x ", M.e[i]);
   printf("\n");

 
   // return statement 	 
   return 0;
}
