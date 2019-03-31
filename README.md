# TOA Project2019
Module: Theory of Algorithms - Project 2019

Name: Ivan McGann
Student Number: G00340138

User manual:
er Manual:
1)  Clone the repository in the command line using the command "git clone https://github.com/IvanMcGann/TOA_Project2019"
2)  From the home menu enter the folder of the project by entering the command "cd TOA_Project2019"
3)  Once in the folder compile the SHA256.c file to create an executable (here named SHA) to run the program. Do this by using the command "gcc -o SHA SHA256.c"
4)  This creates an executable you can use to run the program, to run this you need to enter a command "./SHA " followed by the file you need to run.
5)  I will first test the SHA256 algorithm on an empty String, with the command "./SHA ""   "
6)  This will tell the user there was an error reading the content.
7)  Next I will create a file, I will keep it quick and just call it empty.txt, the command to do this is "vi empty.txt"
8)  This will open vi but you can exit this by pressing esc on your keyboard and pressing semicolon, then q and press enter to leave the file. Command for this is "esc -> :q -> press enter".
9)  This created an empty file, you can check the file sizes using the command "ls -l" 
10)  Now I will test the empty file using the SHA executable created in step 2.
11) Test this file using the command "./SHA empty.txt"
12) The output will be -- e3b0c442 98fc1c14 9afbf4c8 996fb924 27ae41e4 649b934c a495991b 7852b855 
13) Which is the correct output for an empty file.
14) 

References:

Secure Hash Algorithm Doc:
https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf

Secure Hash Standard Link for references sections: 
https://www.nist.gov/publications/secure-hash-standard

Convert Big Endian to little Endian:
https://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func/16708366#16708366

Empty SHA256 string:
https://crypto.stackexchange.com/questions/26133/sha-256-hash-of-null-input  

SHA256 Online Converter: 
http://www.unit-conversion.info/texttools/sha/

C Language Operators
https://www.studytonight.com/c/operators-in-c.php

Unions and Structures in C:
https://www.quora.com/Does-structures-and-unions-have-addresses-like-variables-and-functions-in-C

Tilde bitwise operator: 
https://stackoverflow.com/questions/3952122/what-does-operator-do

Macro for 64 bit little to big endian conversion:
https://blogs.oracle.com/solaris/optimizing-byte-swapping-for-fun-and-profit-v2

VI Commands:
https://www.cs.colostate.edu/helpdocs/vi.html
https://kb.iu.edu/d/afdc
https://www.unix.com/unix-for-dummies-questions-and-answers/79915-vi-paste-out-alignment.html




Video Links - 
Hash standard intro:
https://web.microsoftstream.com/video/6c22658e-7e5a-421a-b7f9-f0206741ca40
Prime Cube Roots:
https://web.microsoftstream.com/video/e5e7f5d8-3d2f-4115-9eaa-d9b1d6a91c4e
SHA256 Part 1:
https://web.microsoftstream.com/video/db7c03be-5902-4575-9629-34d176ff1366
SHA256 Part 2:
https://web.microsoftstream.com/video/2a86a2ac-aafb-46e0-a278-a3faa1d13cbf
Unions in C:
https://web.microsoftstream.com/video/78dc0c8d-a017-48c8-99da-0714866f35cb
Padding for C:
https://web.microsoftstream.com/video/9daaf80b-9c4c-4fdc-9ef6-159e0e4ccc13
Padding for C part 2:
https://web.microsoftstream.com/video/200e71ec-1dc1-47a4-9de8-6f58781e3f38
Finishing the SHA256 Algorithms:
https://web.microsoftstream.com/video/f823809a-d8df-4e12-b243-e1f8ed76b93f


