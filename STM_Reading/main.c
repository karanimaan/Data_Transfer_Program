#include <stdio.h>
#include <string.h>

void Decompression (char *Out_size, const unsigned char *Compressed_size, unsigned CompressedLength) {

	unsigned long long Buffer = 0;
	char Bits = 0;
	while (CompressedLength) {
		while (CompressedLength && Bits < 7 * 8) {
			Buffer |= (unsigned long long)*Compressed_size++ << Bits;
			Bits += 8;
			--CompressedLength;
		}
		while (Bits > 0) {
			*Out_size++ = Buffer & 0x7F;
			Buffer >>= 7;
			Bits -= 7;
		}

		Bits = 0;
		Buffer = 0;
	}
}

#define COMPRESSED_LENGTH 9  // => 7//8 * size of original
#define DECOMPRESSED_LENGTH 10
#define COMPRESSED_FILENAME "C:\\Users\\Karan\\OneDrive - University of Cape Town\\COURSES\\Design\\Data_Transfer_Program\\STM_Reading\\compressed.txt"
#define DECOMPRESSED_FILENAME "C:\\Users\\Karan\\OneDrive - University of Cape Town\\COURSES\\Design\\Data_Transfer_Program\\STM_Reading\\decompressed.txt"

int main() {
    // read from file
    FILE *f = fopen(COMPRESSED_FILENAME, "r");
    unsigned char compressed_string[COMPRESSED_LENGTH] = "";
    fgets(compressed_string, COMPRESSED_LENGTH, f);
    fclose(f);

    // decompress
    char decompressed_string[DECOMPRESSED_LENGTH] = "";
    Decompression(decompressed_string, compressed_string, COMPRESSED_LENGTH);

    // write to file
    f = fopen(DECOMPRESSED_FILENAME, "w");
    fprintf(f, "%s\n", decompressed_string);
    fclose(f);

    //printf("%s\n", decompressed_string);

    return 0;
}