#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "functions.h"

int main(int argc, char *argv[]) {
    char filter;
    FILE *output;
    char *filters = "begr";
    // check if enough arguments were given
    if (argc != 4 && argc != 3) {
        fprintf(stderr, "Usage: filter -(b, e, r, g) file.bmp [output.bmp]");
        exit(EXIT_FAILURE);
    }
    // check filter's validity
    filter = getopt(argc, argv, filters);
    if (filter == '?') {
        fprintf(stderr, "ERROR 1: Invalid filter");
        exit(EXIT_FAILURE);
    }
    // Check to potential multiple uses of a filter
    if (getopt(argc, argv, filters) != -1) {
        fprintf(stderr, "ERROR 2: It seems you are using multiple filters, only one is allowed");
        exit(EXIT_FAILURE);
    }
    // open the file in read mode by creating a pointer to the file in the memory
    FILE *input = fopen(argv[2], "rb");
    if (input == NULL) {
        fprintf(stderr, "ERROR 3: Could not open %s, it may not exist or make sure the path is correct", argv[2]);
        exit(EXIT_FAILURE);
    }
    // create an output file
    if (argc == 3) {
        output = fopen("output.bmp", "wb");
    } else {
        output = fopen(argv[3], "wb");
    }
    // Adapted from CS50's week 5 problem filter-more
    // Read the header of the bitmap file
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, input);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, input);
    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(output);
        fclose(input);
        fprintf(stderr, "ERROR 4: unsupported file format.");
        exit(EXIT_FAILURE);
    }

    // Get image's dimensions
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // Allocate memory for image
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        fprintf(stderr, "ERROR 5: not enough memory to store image.");
        fclose(output);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    // Determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Iterate over infile's scanlines
    for (int i = 0; i < height; i++)
    {
        // Read row into pixel array
        fread(image[i], sizeof(RGBTRIPLE), width, input);

        // Skip over padding
        fseek(input, padding, SEEK_CUR);
    }

    // Filter image
    switch (filter)
    {
        // Blur
        case 'b':
            blur(height, width, image);
            break;

        // Edges
        case 'e':
            edges(height, width, image);
            break;

        // Grayscale
        case 'g':
            grayscale(height, width, image);
            break;

        // Reflect
        case 'r':
            reflect(height, width, image);
            break;
    }

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, output);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, output);

    // Write new pixels to outfile
    for (int i = 0; i < height; i++)
    {
        // Write row to outfile
        fwrite(image[i], sizeof(RGBTRIPLE), width, output);

        // Write padding at end of row
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, output);
        }
    }

    // Free memory for image
    free(image);

}