/**
 * CS200
 * Project 4: Float Analysis
 * Jason Travis
 *
 * Takes a float and uses bitwise operations to
 * print a summary of its bit components.
 */
#include <stdio.h>

void exponent(int);
void mantissa(int);
void binary(int, int, int);
void printAnalysis(int);

int main() {
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
 * printAnalysis prints a summary of the float bits components
 */
void printAnalysis(int bits) {
	int sign = (bits >> 31) & 1;
	int exp = (bits >> 23) & 255;

	// interpret sign as either 'positive' or 'negative'
	char  *s;
	if(sign == 0) {
		s = "(positive)";
	} else {
		s = "(negative)";
	}

	printf("Float Analysis\n");
	
	printf("  Bit Pattern:\t%d ", sign);
	exponent(bits); printf(" ");
	mantissa(bits); printf("\n");
	printf("\t\tS Exponent Significand/Mantissa\n\n");

	printf("  Sign:\t\t%d %s\n", sign, s);

	printf("  Exponent:\t");
	exponent(bits);
	printf(" = %d; w/bias 127 -> (%d-127) = %d\n", exp, exp, exp - 127);
	
	printf("  Significand:\t");
	mantissa(bits); printf("\n");
	printf("   w/implied 1: 1.");
	mantissa(bits); printf("\n");
	
	printf("  Combined:\t+ [1.");
	mantissa(bits);
	printf("] * 2^%d\n", exp - 127);
	printf("   or:\n");
	// TODO: + [1 + (1/2) + (1/64)] * 2^3
}

/*
 * exponent is a wrapper around binary that prints the exponent
 * piece of the float bits
 */
void exponent(int bits) {
	binary(bits, 30, 8);
}

/*
 * mantissa is a wrapper around binary that prints the significand
 * piece of the float bits
 */
void mantissa(int bits) {
	binary(bits, 22, 22);
}

/*
 * binary prints the binary representation of a range of bits.
 * bits is the source from which the range of bits will be taken.
 * high is the index of the highest order bit in the range.
 * len is the length of the range.
 */
void binary(int bits, int high, int len) {
	int i;
	for(i = high; i > (high - len); i--) {
		printf("%d", (bits >> i) & 1);
	}
}
