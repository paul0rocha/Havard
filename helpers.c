#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = (int) round(
                (image[i][j].rgbtBlue +
                 image[i][j].rgbtGreen +
                 image[i][j].rgbtRed) / 3.0
            );

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
}

// Limit color value to 255
int limit(int value)
{
    if (value > 255)
    {
        return 255;
    }

    return value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = (int) round(
                0.393 * originalRed +
                0.769 * originalGreen +
                0.189 * originalBlue
            );

            int sepiaGreen = (int) round(
                0.349 * originalRed +
                0.686 * originalGreen +
                0.168 * originalBlue
            );

            int sepiaBlue = (int) round(
                0.272 * originalRed +
                0.534 * originalGreen +
                0.131 * originalBlue
            );

            image[i][j].rgbtRed = limit(sepiaRed);
            image[i][j].rgbtGreen = limit(sepiaGreen);
            image[i][j].rgbtBlue = limit(sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temporary = image[i][j];

            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temporary;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Make a copy of the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Apply blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            for (int row = -1; row <= 1; row++)
            {
                for (int column = -1; column <= 1; column++)
                {
                    int newRow = i + row;
                    int newColumn = j + column;

                    if (newRow >= 0 && newRow < height &&
                        newColumn >= 0 && newColumn < width)
                    {
                        sumRed += copy[newRow][newColumn].rgbtRed;
                        sumGreen += copy[newRow][newColumn].rgbtGreen;
                        sumBlue += copy[newRow][newColumn].rgbtBlue;

                        count++;
                    }
                }
            }

            image[i][j].rgbtRed = (int) round((float) sumRed / count);
            image[i][j].rgbtGreen = (int) round((float) sumGreen / count);
            image[i][j].rgbtBlue = (int) round((float) sumBlue / count);
        }
    }
}
