// Finished implementation of helpers.c by adding greyscale, sepia, reflect and blur filter function.
// by Wojciech Szubstarski 2020 for CS50.

//Adding <math.h> for 'round()' function
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Making loops for pixel by pixel grayscale conversion
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Calculating the rounded average value for all chanels
            double sum = image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed;
            double rmid = round(sum / 3);

            //Changing all chanels to new value to make each pixel greayscaled
            image[h][w].rgbtBlue = rmid;
            image[h][w].rgbtGreen = rmid;
            image[h][w].rgbtRed = rmid;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Making loops for pixel by pixel sepia conversion
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Making array to store sepia formula just for practice
            double array[9];

            //Calculating and storing sepia formula's values
            array[0] = image[h][w].rgbtRed * 0.393;
            array[1] = image[h][w].rgbtGreen * 0.769;
            array[2] = image[h][w].rgbtBlue * 0.189;
            array[3] = image[h][w].rgbtRed * 0.349;
            array[4] = image[h][w].rgbtGreen * 0.686;
            array[5] = image[h][w].rgbtBlue * 0.168;
            array[6] = image[h][w].rgbtRed * 0.272;
            array[7] = image[h][w].rgbtGreen * 0.534;
            array[8] = image[h][w].rgbtBlue * 0.131;

            //Changing all chanels to sepia value according to sepia formula and making sure the value don't exceed 255
            //For red chanel
            if (array[0] + array[1] + array[2] > 255)
            {
                image[h][w].rgbtRed = 255;
            }
            else
            {
                image[h][w].rgbtRed = round(array[0] + array[1] + array[2]);
            }

            //For green chanel
            if (array[3] + array[4] + array[5] > 255)
            {
                image[h][w].rgbtGreen = 255;
            }
            else
            {
                image[h][w].rgbtGreen = round(array[3] + array[4] + array[5]);
            }

            //For blue chanel
            if (array[6] + array[7] + array[8] > 255)
            {
                image[h][w].rgbtBlue = 255;
            }
            else
            {
                image[h][w].rgbtBlue = round(array[6] + array[7] + array[8]);
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Temporary value created to help swaping pixels
    RGBTRIPLE temp;

    //Making loops for pixel by pixel reflection for only half image because second half will be reflected wich first
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w <= round(((width - 1) / 2)); w++)
        {
            //Pixel from the first half goes to temp
            temp = image[h][w];
            //Pixel from the second half goes to first half
            image[h][w] = image[h][width - 1 - w];
            //Pixel from the temp from the first half goes to second
            image[h][width - 1 - w] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Temporary array created to store new values nesessary to allow using the original values of pixels.
    RGBTRIPLE copy[height][width];

    //Variables for storing sum of RGB values of pixel and pixels around it and divide for storing number of pixels around.
    double red = 0, green = 0, blue = 0, divide = 0;

    //Making loops for pixel by pixel blur if exists
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //For -1-1 pixel
            if (h - 1 >= 0 && w - 1 >= 0)
            {
                red += image[h - 1][w - 1].rgbtRed;
                green += image[h - 1][w - 1].rgbtGreen;
                blue += image[h - 1][w - 1].rgbtBlue;
                divide++;
            }

            //For -1 0 pixel
            if (h - 1 >= 0 && w >= 0)
            {
                red += image[h - 1][w].rgbtRed;
                green += image[h - 1][w].rgbtGreen;
                blue += image[h - 1][w].rgbtBlue;
                divide++;
            }

            //For -1+1 pixel
            if (h - 1 >= 0 && w + 1 < width)
            {
                red += image[h - 1][w + 1].rgbtRed;
                green += image[h - 1][w + 1].rgbtGreen;
                blue += image[h - 1][w + 1].rgbtBlue;
                divide++;
            }

            //For 0-1 pixel
            if (w - 1 >= 0)
            {
                red += image[h][w - 1].rgbtRed;
                green += image[h][w - 1].rgbtGreen;
                blue += image[h][w - 1].rgbtBlue;
                divide++;
            }

            //For center pixel
            red += image[h][w].rgbtRed;
            green += image[h][w].rgbtGreen;
            blue += image[h][w].rgbtBlue;
            divide++;

            //For 0+1 pixel
            if (w + 1 < width)
            {
                red += image[h][w + 1].rgbtRed;
                green += image[h][w + 1].rgbtGreen;
                blue += image[h][w + 1].rgbtBlue;
                divide++;
            }

            //For +1-1 pixel
            if (h + 1 < height && w - 1 >= 0)
            {
                red += image[h + 1][w - 1].rgbtRed;
                green += image[h + 1][w - 1].rgbtGreen;
                blue += image[h + 1][w - 1].rgbtBlue;
                divide++;
            }

            //For +1 0 pixel
            if (h + 1 < height && w >= 0)
            {
                red += image[h + 1][w].rgbtRed;
                green += image[h + 1][w].rgbtGreen;
                blue += image[h + 1][w].rgbtBlue;
                divide++;
            }

            //For +1+1 pixel
            if (h + 1 < height && w + 1 < width)
            {
                red += image[h + 1][w + 1].rgbtRed;
                green += image[h + 1][w + 1].rgbtGreen;
                blue += image[h + 1][w + 1].rgbtBlue;
                divide++;
            }

            //Make average value of 'box' pixels, change center pixel channel's valueandstore it in temporary array
            red = red / divide;
            green = green / divide;
            blue = blue / divide;
            copy[h][w].rgbtRed = round(red);
            copy[h][w].rgbtGreen = round(green);
            copy[h][w].rgbtBlue = round(blue);

            //Prepare values to next pixel
            red = 0, green = 0, blue = 0, divide = 0;

        }
    }

    //Making loops for copy new (blurred) values from temporary array to original places
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = copy[h][w].rgbtRed;
            image[h][w].rgbtGreen = copy[h][w].rgbtGreen;
            image[h][w].rgbtBlue = copy[h][w].rgbtBlue;
        }
    }
}
