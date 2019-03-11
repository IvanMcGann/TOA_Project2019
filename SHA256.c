//Secure Hash Standard Link for references https://www.nist.gov/publications/secure-hash-standard
//Student Name: Ivan McGann Student No: G00340138

#include <stdio.h>
#include <stdint.h>

void sha256();

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
   //test quit

}

