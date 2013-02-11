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

static const string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main(int argc, char* argv[])
{
	if(argc != 2) {
		printUsage();
	}

	string in, out;

	// Read in original string.
	cout << "Enter text: ";
	getline(cin, in);

	// Parse command line argument
	if(strcmp(argv[1], "encode") == 0) {
		cout << "\nencoding...\n\n";
		out = encode(in);
	} else if(strcmp(argv[1], "decode") == 0) {
		cout << "\ndecoding...\n\n";
		out = decode(in);
	} else {
		printUsage();
	}

	// Print result
	cout << out << endl;

	return 0;
}

void printUsage() {
	cout << "Usage: base64 [encode|decode]" << endl;
	exit(1);
}

// encode returns a string encoded in base64.
string encode(string in)
{
	string out;
	// Round length down to a multiple of 3. It is easier to encode in multiples of three
	// and use a switch statement to catch the edge cases.
	int len = in.length();
	len -= (len % 3);
	// The set of characters currently being encoded
	int ch0, ch1, ch2;

	// Use bitwise operators and the base64[] table to encode src.
	// 00000011 11112222 22333333
	// 000000 111111 222222 333333
	// A      B      C      D
	for(int i = 0; i < len; i+=3) {
		ch0 = in[i];
		ch1 = in[i+1];
		ch2 = in[i+2];
		out.push_back(base64[((ch0 >> 2) & 0x3f)]);
		out.push_back(base64[((ch0 << 4) & 0x30) | ((ch1 >> 4) & 0x0f)]);
		out.push_back(base64[((ch1 << 2) & 0x3f) | ((ch2 >> 6) & 0x03)]);
		out.push_back(base64[ch2 & 0x3f]);
	}

	// Encode the remaining characters and pad with '='
	switch(in.length()%3) {
		default:
			break;
		case 1:
			ch0 = in[len];
			out.push_back(base64[((ch0 >> 2) & 0x3f)]);
			out.push_back(base64[((ch0 << 4) & 0x30)]);
			out.append(2, '=');
			break;
		case 2:
			ch0 = in[len];
			ch1 = in[len+1];
			out.push_back(base64[((ch0 >> 2) & 0x3f)]);
			out.push_back(base64[((ch0 << 4) & 0x30) | ((ch1 >> 4) & 0x0f)]);
			out.push_back(base64[((ch1 << 2) & 0x3c)]);
			out.append(1, '=');
	}

	return out;
}

// decode returns a decoded base64 string.
string decode(string in) {
	string out;
	// Round length down to a multiple of 4.
	int len = in.length();
	len -= (len % 4);
	// The set of character currently being decoded
	int ch0, ch1, ch2, ch3;

	// Use bitwise operators and the base64[] table to encode src.
	// A      B      C      D
	// 000000 111111 222222 333333
	// 00000011 11112222 22333333
	for(int i = 0; i < len; i+=4) {
		ch0 = base64.find(in[i]);
		ch1 = base64.find(in[i+1]);
		ch2 = base64.find(in[i+2]);
		ch3 = base64.find(in[i+3]);
		out.push_back((ch0 << 2) | (ch1 >> 4));
		out.push_back(((ch1 << 4) & 0xf0) | (ch2 >> 2));
		out.push_back((ch2 << 6) | ch3);
	}

	return out;
}
