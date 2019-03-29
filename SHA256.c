//Secure Hash Standard Link for references https://www.nist.gov/publications/secure-hash-standard
//Student Name: Ivan McGann Student No: G00340138

#include <stdio.h>
#include <stdint.h>

//message block represtentation
union msgblock{
	uint8_t e[64]; //64 element array of 8 bit integers = 512 byte message block
	uint32_t t[16]; //16 element array of 32 bit integers = 512 byte message block
	uint64_t s[8]; //8 element array of 64 bit integers = 512 bit message block
};

//similar to a short integer, used to flag the current status of the message
enum status {READ, PAD0, PAD1, FINISH};


void sha256();

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



int main(int argc, char *argv[]){

  sha256();
	      
  return 0;
}

// Function sha256 declared above and defined here


void sha256(){

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

    
  // Current message block (Section 6.2.2)
   uint32_t M[16];
   
   //Used for looping below
   int t;
   
   //SHA-256 hash computation uses functions and constants previously defined in( Sections 4.1.2 & 4.2.2)
   //(Section 6.2.2)
   
   //Part 1. (Section 6.2.2)
   //W[t] = M[t]...for 0 <= t <= 15 (Section 6.2.2)	
   for (t = 0; t < 16; t++)
    W[t] = M[t];
   	
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
   uint32_t Ch(uint32_t x, uint32_t y, uint32_t z)
    return ((x & y) ^ ((!x) & z)
   }
    //Section (4.1.2) Maj is majority
   uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
    return ((x & y) ^ (x & z) ^ (y & z));
   }
   
/////////////////////////////////////////



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
     printf("Read %2llu bytes \n", nobytes);//display byte sizes to user
     nobits = nobits + (nobytes * 8);//calculate no of bits from bytes     
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
       for(i = 0; i < 56; i++)//while i is less than 56 
	  M.e[i] = 0x00; 
	  M.s[7] = nobits; //fill in with zeroes
   }//if status is PAD0 add a block of padding 448 bits of zeroes and last 8 bytes is 64 bit big endian integer representing the no of bits in the original message
   if (S==PAD1)
      M.e[0] = 0x08; //first bit of message block is a one for PAD1 and zero for PAD0
   
    
   // closes file f 		  
   fclose(f); 

   // this displays all elements of M as 64 bytes in hex
   for (int i = 0; i < 64; i++)
   printf("%x ", M.e[i]);
   printf("\n");

 
   // return statement 	 
   return 0;
}