The Durand-Kerner Method

Daniil Martyn
daniil.martyn@email.wsu.edu

Files Included:
	dk.c
	README.txt

This program numerically calculates the real and/or imaginary roots of a polynomial equation. 
The polynomial must be normalized so that the highest degree coefficient = 1. The input to
the program should be redirected from the command line such as: ./dk < input.txt
The input file should list the coefficients in order from least degree to highest degree, not
including the 1 coefficient of the highest degree. For each coefficient, the format is "real imaginary".
There is no filter for garbage input so be careful. To compile the program, navigate to the 
directory where dk.c is stored within the terminal and compile using gcc. 
	gcc -std=c99 dk.c -o dk -lm