#include "helpers.h"
#include <math.h>

// Helper function to get the minimum of two values
int min(int a, int b)
{
    return (a < b) ? a : b;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Grab each pixels value for the single grey output
            int average_rgb = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // aplly the average to each RGB "channel"
            image[i][j].rgbtRed = average_rgb;
            image[i][j].rgbtGreen = average_rgb;
            image[i][j].rgbtBlue = average_rgb;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate sepia values for each RGB component based on the required algorithm in the problem set
            int sepiaRed = min(round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue), 255);
            int sepiaGreen = min(round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue), 255);
            int sepiaBlue = min(round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue), 255);

            // Assign the new sepia RGB values to the corresponing pixel
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
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
            // Swap pixels on the left half with corresponding pixels on the right half
            // Temp variable for transfering the pixels
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Variable for transfer
    RGBTRIPLE temp_blur[height][width];

    // Copy the original image into the "temp_blur" array to avoid modifying the image prematurely
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_blur[i][j] = image[i][j];
        }
    }

    // Apply the blur effect to the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            // Iterate over the surrounding 3x3 grid (including the current pixel)
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int row = i + k;
                    int col = j + l;

                    // Check for boundaries
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        sumRed += temp_blur[row][col].rgbtRed;
                        sumGreen += temp_blur[row][col].rgbtGreen;
                        sumBlue += temp_blur[row][col].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average RGB values and set them in the original image
            image[i][j].rgbtRed = round((float)sumRed / count);
            image[i][j].rgbtGreen = round((float)sumGreen / count);
            image[i][j].rgbtBlue = round((float)sumBlue / count);
        }
    }
}
