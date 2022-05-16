// A program that recovers JPEGs from a forensic image.
// by Wojciech Szubstarski 2020 for CS50.


// Include 'cs50.h' only for bool
#include <cs50.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Ensure correctness of FAT size
typedef uint8_t BLOCK;

int main(int argc, char *argv[])
{

    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: recover [source file to recover]\n");
        return 1;
    }

    // Remember source filename
    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");

    // Check if sourcefile exist
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }


    // Ensure correctness of FAT size
    BLOCK block[512];

    // Space to hold the jpeg name X X X . j p g /0
    char jpeg_name[8];
    int jpeg_number = 0;
    bool is_jpeg = false;
    FILE *outptr = NULL;

    // Repeat until meets end of sourcefile
    while (fread(&block, sizeof(block), 1, inptr) != 0)
    {
        // Search the specific four bytes pattern of jpeg
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            // if program found jpeg (not first)
            if (is_jpeg)
            {
                // Close previous jpeg
                fclose(outptr);
                // Create jpeg with next number and start write in it
                sprintf(jpeg_name, "%03d.jpg", jpeg_number++);
                outptr = fopen(jpeg_name, "w");
                fwrite(&block, sizeof(block), 1, outptr);
            }
            // if program found first jpeg
            else
            {
                // Mark that jpegs are started in card
                is_jpeg = true;
                // Create jpeg with next number and start write in it
                sprintf(jpeg_name, "%03d.jpg", jpeg_number++);
                outptr = fopen(jpeg_name, "w");
                fwrite(&block, sizeof(block), 1, outptr);
            }
        }
        else
        {
            // if jpeg is created keep writing in it
            if (is_jpeg)
            {
                fwrite(&block, sizeof(block), 1, outptr);
            }
        }
    }
    // Close courcefile and last output file
    fclose(outptr);
    fclose(inptr);
    return 0;
}