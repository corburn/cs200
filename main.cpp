//=============================================================================
// Base64 Encoding Starter Framework
// 2011.02.16 by Abe Pralle
//
// Reads a string of text and prints a resulting string of text where every
// 3 original characters have been transformed into 4 result characters
// consisting of the first three characters reversed followed by a hypen.
//
// Example output:
//
// Enter text:
// ABCDEFGHIJKLMNOPQRSTUVWXYZ
//
// You typed in "ABCDEFGHIJKLMNOPQRSTUVWXYZ" (26 characters)
//
// Encoded value:
// CBA-FED-IHG-LKJ-ONM-RQP-UTS-XWV-
//=============================================================================
#include <iostream>
using namespace std;
void encode( char* src, char* dest );
int main()
{
	// Declare arrays to store original and encoded strings.
	char st[80];
	char encoded[120];
	// Read in original string.
	cout << "Enter text: ";
	cin.getline( st, 80 );
	// Print back out along with the # of characters.
	int len = strlen(st);
	cout << "You typed in \"" << st << "\" (" << len << " characters)" << endl;
	// Round length down to a multiple of 3.
	len -= (len % 3);
	// Encode the string - every 3 characters of original becomes
	// 4 characters of result.
	int dest_index = 0;
	for (int i=0; i<len; i+=3) {
		encode( st+i, encoded+dest_index );
		dest_index += 4;
	}
	// Null terminate destination string.
	encoded[dest_index] = 0;
	// Print encoded value.
	cout << "Encoded value: ";
	cout << encoded << endl;
	return 0;
}
void encode( char* src, char* dest )
{
	int ch0 = src[0];
	int ch1 = src[1];
	int ch2 = src[2];
	dest[0]
	dest[1]
	dest[2]
	dest[3]
}
