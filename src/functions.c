//
// Created by pariz on 16/03/2025.
//

#include "functions.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = (BYTE) average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            BYTE oldblue = image[i][j].rgbtBlue;
            BYTE oldred = image[i][j].rgbtRed;
            BYTE oldgreen = image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtBlue = oldblue;
            image[i][width - j - 1].rgbtRed = oldred;
            image[i][width - j - 1].rgbtGreen = oldgreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int counter = 0;
    float averagered = 0;
    float averagegreen = 0;
    float averageblue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            averagered = averageblue = averagegreen = counter = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        counter++;
                        averagered += image[k][l].rgbtRed;
                        averageblue += image[k][l].rgbtBlue;
                        averagegreen += image[k][l].rgbtGreen;
                    }
                }
            }
            temp[i][j].rgbtRed = (BYTE) round(averagered / counter);
            temp[i][j].rgbtGreen = (BYTE) round(averagegreen / counter);
            temp[i][j].rgbtBlue = (BYTE) round(averageblue / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gxred = 0;
            float Gxgreen = 0;
            float Gxblue = 0;
            float Gyred = 0;
            float Gygreen = 0;
            float Gyblue = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int x = i + k;
                    int y = j + l;

                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        Gxred += image[x][y].rgbtRed * Gx[k + 1][l + 1];
                        Gxgreen += image[x][y].rgbtGreen * Gx[k + 1][l + 1];
                        Gxblue += image[x][y].rgbtBlue * Gx[k + 1][l + 1];

                        Gyred += image[x][y].rgbtRed * Gy[k + 1][l + 1];
                        Gygreen += image[x][y].rgbtGreen * Gy[k + 1][l + 1];
                        Gyblue += image[x][y].rgbtBlue * Gy[k + 1][l + 1];
                    }
                }
            }
            int red = round(sqrt(pow(Gxred, 2) + pow(Gyred, 2)));
            int green = round(sqrt(pow(Gxgreen, 2) + pow(Gygreen, 2)));
            int blue = round(sqrt(pow(Gxblue, 2) + pow(Gyblue, 2)));

            temp[i][j].rgbtRed = fmin(round(red), 255);
            temp[i][j].rgbtGreen = fmin(round(green), 255);
            temp[i][j].rgbtBlue = fmin(round(blue), 255);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
