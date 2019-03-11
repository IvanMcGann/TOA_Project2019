//Secure Hash Standard Link for references https://www.nist.gov/publications/secure-hash-standard
//Student Name: Ivan McGann Student No: G00340138

#include <stdio.h>
#include <stdint.h>

void sha256();

//SHA-256 functions for Sigma 1 & 2 (Sections 4.1.2 & 4.2.2)

uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// rotr (rotate right and shr(shift right operators (Section 3.2) 

uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);

int main(int argc, char *argv[]){

  sha256();
	      
  return 0;
}

// Function sha256 declared above and defined here


void sha256(){

   // Message schedule: (Section 6.2)	
   uint32_t W[64];
   // Working variables: (Section 6.2)
   uint32_t a, b, c, d, e, f, g, h;
   //Temporary Variables: (Section 6.2) 
   uint32_t T1, T2;
   //hash value: literal numbers wriiten in hexidecimal (Section 5.3.3)	    
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

   // Current message block: (Section 6.2.2)
   uint32_t M[16];
   
   //Used for looping
   int t;
	
   //W[t] = M[t]...for 0 <= t <= 15 (Section 6.2.2)	
   for (t = 0; t < 16; t++)
    W[t] = M[t];
   	
   //W[t] = Sigma1 for 16 <= t <= 63	
   for (t = 16; t < 64; t++) 
    W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
   //
   //

}
   // x is a w-bit word and n is an integer with 0 <= n <= w (Section 3.2)
   uint32_t rotr(uint32_t n, uint32_t x){
    return (x >> n) | (x << (32 - n));
   }
   //x is a w-bit word and n is an integer with 0 <= n < w (Section 3.2)
   uint32_t shr(uint32_t n, uint32_t x){
    return (x >> n);
   }

   //^ = XOR , | = OR 
   //(Sections 3.2 & 4.1.2)
   uint32_t sig0(uint32_t x){
    return (rotr(7, x) ^ rotr(18, x) ^ shr(3, x));
   }
   //(Sections 3.2 & 4.1.2)
   uint32_t sig1(uint32_t x){
    return (rotr(17, x) ^ rotr(19, x) ^ shr(10, x));	   
   }

   
