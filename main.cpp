//=============================================================================
// Base64 Encoding Starter Framework
// 2011.02.16 by Abe Pralle
//
// CS200
// Project 5: Base64
// 2013.02.05 Jason Travis
//
// Reads in a string and prints it as encoded/decoded base64 depending on the
// command line argument.
//
// Usage:
//
// base64 [encode|decode]
//
// Example output:
//
// Enter text:
// ABCDEFGHIJKLMNOPQRSTUVWXYZ
//
// encoding...
//
// CBA-FED-IHG-LKJ-ONM-RQP-UTS-XWV-
//=============================================================================
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

void printUsage();
string encode( string in );
string decode( string in );

const char base64[65] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

int main(int argc, char* argv[])
{
	if(argc != 2) {
		printUsage();
	}

	string input, output;

	// Read in original string.
	cout << "Enter text: ";
	getline(cin, input);

	// Parse command line argument
	if(strcmp(argv[1], "encode") == 0) {
		cout << "\nencoding...\n\n";
		output = encode(input);
	} else if((argv[1], "decode") == 0) {
		cout << "\ndecoding...\n\n";
		decode(input);
	} else {
		printUsage();
	}

	// Print result
	cout << output << endl;

	return 0;
}

void printUsage() {
	cout << "Usage: base64 [encode|decode]" << endl;
	exit(1);
}

string encode(string in)
{
	string out;
	// Round length down to a multiple of 3. It is easier to encode in multiples of three
	// and use a switch statement to catch the edge cases.
	int len = in.length();
	len -= (len % 3);
	// The set of character currently being encoded
	int ch0, ch1, ch2;

	// Use bitwise operators and the base64[] table to encode src.
	// 00000011 11112222 22333333
	// 000000 111111 222222 333333
	// A      B      C      D
	for(int i = 0; i < len; i+=3) {
		ch0 = in[i];
		ch1 = in[i+1];
		ch2 = in[i+2];
		out.push_back(base64[((ch0 >> 2) & 63)]);
		out.push_back(base64[((ch0 << 4) & 48) | ((ch1 >> 4) & 15)]);
		out.push_back(base64[((ch1 << 2) & 60) | ((ch2 >> 6) & 3)]);
		out.push_back(base64[ch2 & 63]);
	}

	// Encode the remaining characters and pad with '='
	switch(in.length()%3) {
		default:
			break;
		case 1:
			ch0 = in[len];
			out.push_back(base64[((ch0 >> 2) & 63)]);
			out.push_back(base64[((ch0 << 4) & 48)]);
			out.append(2, '=');
			break;
		case 2:
			ch0 = in[len];
			ch1 = in[len+1];
			out.push_back(base64[((ch0 >> 2) & 63)]);
			out.push_back(base64[((ch0 << 4) & 48) | ((ch1 >> 4) & 15)]);
			out.push_back(base64[((ch1 << 2) & 60)]);
			out.append(1, '=');
	}
	return out;
}

string decode(string in) {
}
