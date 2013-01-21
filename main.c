/**
 * CS200
 * Project 4: Float Analysis
 * Jason Travis
 *
 * Takes a float and uses bitwise operations to
 * print a summary of its bit components.
 */
#include <stdio.h>

void printAnalysis(int);
char* exponent(int);
char* mantissa(int);
void fractions(int);
char* binary(char*, int, int);

// string representations
char expo[8]; // binary exponent
char sig[23]; // binary significand

int main()
{
	float f;

	printf("Enter real number: ");

	scanf("%f", &f);

	// Bitwise operations cannot be used on a float.
	// Casting to an integer will truncate the float.
	// Cast to a int pointer so we can perform bitwise
	// operations on the underlying float bits.
	int bits = *((int*) &f);

	printAnalysis(bits);

	return 0;
}
/*
 * printAnalysis prints a summary of the float components
 */
void printAnalysis(int bits)
{
	int sign = (bits >> 31) & 1;
	int exp = (bits >> 23) & 255;

	printf("Float Analysis\n");

	printf("  Bit Pattern:\t%d %s %s\n", sign, exponent(bits), mantissa(bits));
	printf("\t\tS Exponent Significand/Mantissa\n\n");

	// interpret sign as either 'positive' or 'negative'
	char *s;
	if(sign == 0) {
		s = "(positive)";
	} else {
		s = "(negative)";
	}
	printf("  Sign:\t\t%d %s\n", sign, s);

	printf("  Exponent:\t%s = %d; w/bias 127 -> (%d-127) = %d\n", exponent(bits), exp, exp, exp - 127);

	printf("  Significand:\t%s\n", mantissa(bits));
	printf("   w/implied 1: 1.%s\n", mantissa(bits));

	printf("  Combined:\t+ [1.%s] * 2^%d\n", mantissa(bits) , exp - 127);
	printf("   or:\t\t+ [");
	fractions(bits);
	printf("] * 2^%d\n", exp - 127);
}

/*
 * exponent is a wrapper around binary that stores a binary
 * representation of the exponent in the expo global variable
 * and returns the pointer.
 */
char* exponent(int bits)
{
	return binary(expo, bits >> 23, 8);
}

/*
 * mantissa is a wrapper around binary that stores a binary
 * representation of the significand in the sig global variable
 * and returns the pointer.
 */
char* mantissa(int bits)
{
	return binary(sig, bits, 23);
}

/*
 * fractions is a wrapper around binary that prints the significand
 * as a sum of decimal fractions.
 */
void fractions(int bits)
{
	//binary(sig, bits, 23); sig should already be populated by mantissa
	// 1 + 1/2^(i+1) + ...
	printf("1");
	int i;
	for(i = 0; i < 23; i++) {
		if(sig[i] - '0') {
			printf(" + (1/%d)", (sig[i] - '0') << i + 1);
		}
	}
}

/*
 * binary prints the binary representation of a range of bits.
 * bits is the source from which the range of bits will be taken.
 * high is the index of the highest order bit in the range.
 * len is the length of the range.
 */
char* binary(char *dst, int bits, int len)
{
	int i;
	for(i = 0; i < len; i++) {
		// shift index 'i' bit all the way to the right,
		// clear all other bits, and shift to its ascii value.
		dst[i] = ((bits >> (len - 1 - i) & 1) + '0');
	}
	return dst;
}
