#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check command line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    char *input_file = argv[1];

    // Open file to work with
    FILE *inptr = fopen(input_file, "rb");
    if (inptr == NULL)
    {
        printf("Could not open file %s\n", input_file);
        return 1;
    }

    // Initialize variables

    // Buffer array
    typedef uint8_t BYTE;
    BYTE buffer[512];

    // Count of images
    int image_count = 0;

    // Block size
    int BLOCK_SIZE = 512;

    // Output file
    FILE *output_file = NULL;

    char *file_name = malloc(8 * sizeof(char));

    // Check if memory allocation was successful
    if (file_name == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(inptr);
        return 1;
    }

    // Read source by blocks to check if it's a jpeg format
    while (fread(buffer, sizeof(char), BLOCK_SIZE, inptr))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the previously opened file (if any)
            if (output_file != NULL)
            {
                fclose(output_file);
            }

            // Use sprinttf to prefix the count of the image to the file name written
            sprintf(file_name, "%03i.jpg", image_count);

            // Write to the output file the content
            output_file = fopen(file_name, "wb");
            if (output_file == NULL)
            {
                printf("Could not create output file %s\n", file_name);
                free(file_name);
                fclose(inptr);
                return 1;
            }

            // Increase the count of images found
            image_count++;
        }

        // Check if output has been used for valid input
        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(char), BLOCK_SIZE, output_file);
        }
    }

    // Close the last output file
    if (output_file != NULL)
    {
        fclose(output_file);
    }

    // Close files
    fclose(inptr);
    free(file_name);

    return 0;
}
