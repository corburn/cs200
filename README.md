cs200
=====

Northern Arizona University Introduction to Computer Organization

random.asm mimics the drand48 Linear Congruence Psuedo Random Number Generator, however, it does not accurately implement the algorithm.
It takes a minimum, maximum, and count integer as input and returns the specified number of random numbers between the minimum and maximum values inclusive.

This program was compiled using [NASM](http://www.nasm.us/) assembler and the gcc compiler on a 64bit Linux operating system.

To compile, open a terminal and run: nasm -felf64 random.asm && gcc random.o -o random
