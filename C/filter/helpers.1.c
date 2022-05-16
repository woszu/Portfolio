#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            double sum = image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed;
            double rmid = round(sum/3);

            image[h][w].rgbtBlue = rmid;
            image[h][w].rgbtGreen = rmid;
            image[h][w].rgbtRed = rmid;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            double array[9];

            double rr = round(image[h][w].rgbtRed * 0.393);
            double rg = round(image[h][w].rgbtGreen * 0.769);
            double rb = round(image[h][w].rgbtBlue * 0.189);
            double gr = round(image[h][w].rgbtRed * 0.349);
            double gg = round(image[h][w].rgbtGreen * 0.686);
            double gb = round(image[h][w].rgbtBlue * 0.168);
            double br = round(image[h][w].rgbtRed * 0.272);
            double bg = round(image[h][w].rgbtGreen * 0.534);
            double bb = round(image[h][w].rgbtBlue * 0.131);

            if (rr > 255)

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
