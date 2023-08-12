#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2

    // Remember filename
    char *input_file = argv[1];
    // Read file
    FILE *inptr = fopen(input_file, "rb");
    if (inptr == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    int header_size = sizeof(WAVHEADER);

    fread(&header, header_size, 1, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == 1)
    {
        printf("Incorrect format file, only '.wav' files for this program\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5

    // Remember file name
    char *output_file = argv[2];

    FILE *outptr = fopen(output_file, "wb");
    if (outptr == NULL)
    {
        printf("Could not open output file\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, header_size, 1, outptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int size = get_block_size(header);

    // Write reversed audio file
    // TODO #8
    // Find the last block to start reading
    if (fseek(inptr, size, SEEK_END))
    {
        return 1;
    }

    BYTE buffer[size];
    while (ftell(inptr) - size > header_size)
    {
        // -2 to reverse the writing, which means move 2 blocks backwards each time
        if (fseek(inptr, -2 * size, SEEK_CUR))
        {
            return 1;
        }
        // If not at the beggining of the file, keep reading/writing
        fread(buffer, size, 1, inptr);
        fwrite(buffer, size, 1, outptr);
    }

    // Close files
    fclose(inptr);
    fclose(outptr);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 0;
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int size = header.numChannels * (header.bitsPerSample / 8);
    return size;
}
