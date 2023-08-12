// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 4;
    }

    // Make the height negative to indicate top-down approach
    bi.biHeight = -abs(bi.biHeight);

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Determine padding for scanlines in the input BMP
    int padding_in = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Determine padding for scanlines in the output BMP
    int padding_out = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Allocate memory to store the entire input BMP image
    RGBTRIPLE **image = malloc(abs(bi.biHeight) * sizeof(RGBTRIPLE *));
    if (image == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(outptr);
        fclose(inptr);
        return 5;
    }

    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        image[i] = malloc(bi.biWidth * sizeof(RGBTRIPLE));
        if (image[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            // Free previously allocated memory
            for (int j = 0; j < i; j++)
            {
                free(image[j]);
            }
            free(image);
            fclose(outptr);
            fclose(inptr);
            return 5;
        }
    }

    // Top-down approach: read the entire input BMP image into memory
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Read the entire scanline into memory
        fread(image[i], sizeof(RGBTRIPLE), bi.biWidth, inptr);

        // Skip over padding in the input BMP file
        fseek(inptr, padding_in, SEEK_CUR);
    }

    // Top-down approach: Write the entire BMP image from memory to the output BMP file
    for (int i = abs(bi.biHeight) - 1; i >= 0; i--)
    {
        // Write the entire scanline from memory to the output BMP file
        fwrite(image[i], sizeof(RGBTRIPLE), bi.biWidth, outptr);

        // Write padding to the output BMP file
        for (int k = 0; k < padding_out; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Free memory allocated for the input BMP image
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        free(image[i]);
    }
    free(image);

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Success
    return 0;
}