#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void compress( char* data, int size, FILE* outfile );
void decompress( char* data, int size, FILE* outfile );
char* readFileData( char* filename, int* size_ptr );
int main( int num_args, char* arg_values[] )
{
	if (num_args != 2) {
		printf( "Usage: rle filename (produces filename.rle)\n" );
		printf( "       rle filename.rle (produces filename.plain)\n" );
		exit(1);
	}
	char* input_filename = arg_values[1];
	// read the file data into an array
	int size;
	char* data = readFileData(input_filename,&size);
	// Call compress() or decompress().
	FILE* outfile;
	int len = strlen(input_filename);
	if (len < 4 || strcmp(input_filename+(len-4),".rle") != 0) {
		char output_filename[80];
		strcpy( output_filename, input_filename );
		strcat( output_filename, ".rle" );
		printf( "Compressing %s to %s\n", input_filename, output_filename );
		outfile = fopen( output_filename, "wb" );
		compress( data, size, outfile );
	} else {
		char output_filename[80];
		strncpy( output_filename, input_filename, len-4 );
		output_filename[len-4] = 0;
		strcat( output_filename, ".plain" );
		printf( "Decompressing %s to %s\n", input_filename, output_filename );
		outfile = fopen( output_filename, "wb" );
		decompress( data, size, outfile );
	}
	// Close the output file to ensure data is saved.
	fclose(outfile);
	// Free the array we allocated
	delete data;
	return 0;
}
void compress( char* data, int size, FILE* outfile )
{
	int i = 0;
	int iter = 0;
	// loop through the data
	while(iter < size) {
		// count the consecutive chars
		do {
			iter++;
		} while(iter < size && data[i] == data[iter]);
		// write the count and char to file
		putc((char)(iter - i), outfile);
		putc(data[i], outfile);
		// advance the index
		i = iter;
	}
}
// decompress writes the decompressed data to outfile
void decompress( char* data, int size, FILE* outfile )
{
	for (int i=0; i<size; i+=2) {
			for(char count=0; count < data[i]; ++count) {
					putc(data[i+1], outfile);
			}
	}
}
char* readFileData( char* filename, int* size_ptr )
{
	// Returns a pointer to an array storing the file data.
	// Sets the variable pointed to by 'size' to contain the file size.
	// Exits the program if the filename doesn't exist.
	FILE* infile = fopen(filename,"rb");
	if ( !infile ) {
		printf( "No such file \"%s\"!\n", filename );
		exit(1);
	}
	// Get file size by going to the end of the file, getting the
	// position, and then going back to the start of the file.
	fseek( infile, 0, SEEK_END );
	int size = ftell(infile);
	fseek( infile, 0, SEEK_SET );
	// read the data from the file
	char* data = new char[size];
	fread( data, 1, size, infile );
	fclose(infile);
	*size_ptr = size;
	return data;
}

