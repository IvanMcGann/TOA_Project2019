//Secure Hash Standard Link for references https://www.nist.gov/publications/secure-hash-standard
//Student Name: Ivan McGann Student No: G00340138

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


//adapted from
//https://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func

#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))


//message block represtentation
union msgblock{
	uint8_t e[64]; //64 element array of 8 bit integers = 512 byte message block
	uint32_t t[16]; //16 element array of 32 bit integers = 512 byte message block
	uint64_t s[8]; //8 element array of 64 bit integers = 512 bit message block
};

//similar to a short integer, used to flag the current status of the message
enum status {READ, PAD0, PAD1, FINISH};

//SHA-256 functions for Sigma 1 & 2 (Sections 4.1.2 & 4.2.2)

uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// rotr (rotate right and shr(shift right operators (Section 3.2) 

uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);

//each function operates on 32-bit words, which are represented as x, y, and z.
//The result of each function is a new 32-bit word (Section 4.1.2)

//
uint32_t SIG0(uint32_t x);
uint32_t SIG1(uint32_t x);

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);


void SHA256(FILE *fmsg);

// retrieves next message block
int nextmsgblock(FILE *fmsg,union msgblock *M, enum status *S, uint64_t *nobits);

//start of program
int main(int argc, char *argv[]){
   // f is name of the file pointer
   FILE *fmsg;  

  // if there is no imput file the program won't try to read the file
  if (argc==1){
    printf("Error, no input file \n");
    exit(1);
  }
  


   // file open command for the first arguement provided on the command line. Argv allows you do deal with cmd line arguments
   fmsg = fopen(argv[1], "r");
   
   // if file corrupted or file can't be accessed 
   if (fmsg == NULL){
     printf("Error opening file %s \n", argv[1]);
     exit(2);
   } 
 
   
   // stdarg.h helps cmd line arguments for later
   SHA256(fmsg);
	       
   // closes file f 		  
   fclose(fmsg); 
 

  return 0;
}

// Function sha256 declared above and defined here


void SHA256(FILE *fmsg){
  
   // current  message block
   union msgblock M;

   // tracks the amount of bits read from the file. 
   uint64_t nobits = 0;
  
   //status of the current message block wrt padding 
   enum status S = READ;
  
  
   //64 constant 32-bit words,  represent the first thirty-two bits of the fractional parts of the cube roots of the first sixty-four prime numbers.
   
   //The K Constants (Section 4.2.2)
   uint32_t K[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };    
	
   // Message schedule (Section 6.2)	
   uint32_t W[64];
   
   // Working variables (Section 6.2)
   uint32_t a, b, c, d, e, f, g, h;
   
   //Temporary Variables (Section 6.2) 
   uint32_t T1, T2;
   
   //hash value: literal numbers written in hexidecimal (Section 5.3.3)	    
   //These are obtained by taking the first 32 bits of of the fractional parts of the square roots of the first eight prime numbers
   uint32_t H[8] = {
    0x6a09e667,
    0xbb67ae85,
    0x3c6ef372,
    0xa54ff53a,
    0x510e527f,
    0x9b05688c,
    0x1f83d9ab,
    0x5be0cd19	  
    };

    
   
   //Used for looping below
   int i, t;
   
   //SHA-256 hash computation uses functions and constants previously defined in( Sections 4.1.2 & 4.2.2)
   //(Section 6.2.2)
   while(nextmsgblock(fmsg, &M, &S, &nobits)){
   //Part 1. (Section 6.2.2)
   //W[t] = M[t]...for 0 <= t <= 15 (Section 6.2.2)	
   for (t = 0; t < 16; t++)
    W[t] = SWAP_UINT32(M.t[t]);
   	
   //W[t] = Sigma1 for 16 <= t <= 63	
   for (t = 16; t < 64; t++) 
    W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
   
   //Part 2. (Section 6.2.2)
   //Initialize the eight working variables, a, b, c, d, e, f, g, and h, with the (i-1)st hash value
   a = H[0]; b = H[1]; c = H[2]; d = H[3];
   e = H[4]; f = H[5]; g = H[6]; h = H[7];

   //Part 3.
   //For t=0 to 63 (Section 6.2.2)  
   for (t = 0; t < 64; t++){
   T1 = h + SIG1(e) + Ch(e, f, g) + K[t] + W[t];
   T2 = SIG0(a) + Maj(a, b, c);
   h = g;
   g = f;
   f = e;
   e = d + T1;
   d =c;
   c = b;
   b = a;	
   a = T1 + T2;
   }
  //Part 4.
  //Compute the ith intermediate hash value H(i) (Section 6.2.2)  
  
   H[0] = a + H[0];  
   H[1] = b + H[1];
   H[2] = c + H[2];
   H[3] = d + H[3];
   H[4] = e + H[4];
   H[5] = f + H[5];
   H[6] = g + H[6];
   H[7] = h + H[7];
}
    //^ = XOR , | = OR
 printf("%x %x %x %x %x %x %x %x :", H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);   

 printf("\n");

}
   //x is a w-bit word and n is an integer with 0 <= n <= w (Section 3.2)
   uint32_t rotr(uint32_t n, uint32_t x){
    return (x >> n) | (x << (32 - n));
   }
   //x is a w-bit word and n is an integer with 0 <= n < w (Section 3.2)
   uint32_t shr(uint32_t n, uint32_t x){
    return (x >> n);
   }

   //^ = XOR , | = OR, ! = not and 
   

   //(Sections 3.2 & 4.1.2)
   uint32_t sig0(uint32_t x){
    return (rotr(7, x) ^ rotr(18, x) ^ shr(3, x));
   }
   //(Sections 3.2 & 4.1.2)
   uint32_t sig1(uint32_t x){
    return (rotr(17, x) ^ rotr(19, x) ^ shr(10, x));	   
   }

   //Section (4.1.2)
   uint32_t SIG0(uint32_t x){
    return (rotr(2, x) ^ rotr(13, x) ^ rotr(22, x));
   }
   //Section (4.1.2)
   uint32_t SIG1(uint32_t x){
    return (rotr(6, x) ^ rotr(11, x) ^ rotr(25, x));
   }
   //Section (4.1.2) Ch is choosing   
   uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
    return ((x & y) ^ ((~x) & z));
   }
    //Section (4.1.2) Maj is majority
   uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
    return ((x & y) ^ (x & z) ^ (y & z));
   }
   
// retrieves next message block, padding below
int nextmsgblock(FILE *fmsg, union msgblock *M, enum status *S, uint64_t *nobits) {
  
  // current no of bytes recieved from fread
   uint64_t nobytes; //64 bit integer used below

     
  //used for looping
   int i;

  // If all the message blocks are finished, then S should be set to FINISH
   if (*S == FINISH)
      return 0;
  //If not finished check if we need another block if padding
  if (*S == PAD0 || *S == PAD1){
    for(i = 0; i < 56; i++)// set first 56 to all zeroes 
       M->e[i] = 0x00; // set the last 64 bits to the number of bits in the file 
      M->s[7] = *nobits;
      *S = FINISH; 
  if (*S==PAD1)
      M->e[0] = 0x80; //first bit of message block is a one for PAD1 and zero for PAD0
   //keep loop in sha256() running an extra iteration  
   return 1;
  }//if s is PAD1 then set the first bit of M to one.
   
  //If program reaches here its still reading the file, (*S == READ)

   nobytes = fread(M->e, 1, 64, fmsg);
     // 64 - 8 check if read block is less than 55 bytes. If it is it enters this statement
     *nobits = *nobits + (nobytes * 8);//calculate no of bytes read     
    // Add zero bits, as per the standard 
       if (nobytes < 56){
       // If less than 56 bytes are read, more padding added in message block. 
       M->e[nobytes] = 0x80;   
     // add zero bits until the last 64 bits
       while (nobytes < 56){
         nobytes = nobytes + 1;
	 M->e[nobytes] = 0x00; // set all bytes to zero, between end of message up to last 8 bytes that need to be appended
       }
      // message block is array of 8, 64 bit integers, last bit element as nobits
      // works in modern c standards to read from same union
      // Append file size in bits
	 M->s[7] = *nobits;
	 *S = FINISH;//status is set to finish
     } //if not finished check can some padding be put in message block
      else if(nobytes < 64){
	*S = PAD0; //Tell s we need another message block with padding but no one bit. 
	M->e[nobytes] = 0x80;// one bit appended to current message block
       while (nobytes < 64){//pad rest of block with zero bits
	nobytes = nobytes + 1;
	M->e[nobytes] = 0x00;//add all zeroes
       }//otherwise check if the program is at the end of the file   
      }
      else if (feof(fmsg)){ //if file is finished being read and was a multiple of 512 bits
       //tell S we need another message block with all the padding
       *S = PAD1;
      }   
    
   //if program reaches here return 1 so this function is called again 	 
   return 1;
}
