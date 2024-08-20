#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop for every pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get the average sum of the pixel's colors and assign it to it's colors
            int avgColor = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avgColor;
            image[i][j].rgbtGreen = avgColor;
            image[i][j].rgbtBlue = avgColor;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loop for the image's half, swapping the pixels between them
    for (int h = 0; h < height; h++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            RGBTRIPLE temp = image[h][col];
            image[h][col] = image[h][width - col - 1];
            image[h][width - col - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create new image
    RGBTRIPLE imageRet[height][width];

    // loop for every row
    for (int row = 0; row < height; row++)
    {
        // loop for every column
        for (int col = 0; col < width; col++)
        {
            int avgRed = 0, avgGreen = 0, avgBlue = 0, counter = 0;
            avgRed += image[row][col].rgbtRed;
            avgGreen += image[row][col].rgbtGreen;
            avgBlue += image[row][col].rgbtBlue;
            counter++;

            // not leftmost column; it has pixels to the left
            if (col != 0)
            {
                avgRed += image[row][col - 1].rgbtRed;
                avgGreen += image[row][col - 1].rgbtGreen;
                avgBlue += image[row][col - 1].rgbtBlue;
                counter++;
            }

            // not rightmost column; it has pixels to the right
            if (col < width - 1)
            {
                avgRed += image[row][col + 1].rgbtRed;
                avgGreen += image[row][col + 1].rgbtGreen;
                avgBlue += image[row][col + 1].rgbtBlue;
                counter++;
            }

            // not topmost row; it has pixels above
            if (row != 0)
            {
                avgRed += image[row - 1][col].rgbtRed;
                avgGreen += image[row - 1][col].rgbtGreen;
                avgBlue += image[row - 1][col].rgbtBlue;
                counter++;

                // check for outer top left adjacent
                if (col > 0)
                {
                    avgRed += image[row - 1][col - 1].rgbtRed;
                    avgGreen += image[row - 1][col - 1].rgbtGreen;
                    avgBlue += image[row - 1][col - 1].rgbtBlue;
                    counter++;
                }

                // check for outer top right adjacent
                if (col < width - 1)
                {
                    avgRed += image[row - 1][col + 1].rgbtRed;
                    avgGreen += image[row - 1][col + 1].rgbtGreen;
                    avgBlue += image[row - 1][col + 1].rgbtBlue;
                    counter++;
                }
            }

            // not bottom most row; it has pixels below
            if (row < height - 1)
            {
                avgRed += image[row + 1][col].rgbtRed;
                avgGreen += image[row + 1][col].rgbtGreen;
                avgBlue += image[row + 1][col].rgbtBlue;
                counter++;

                // check for outer bottom left adjacent
                if (col > 0)
                {
                    avgRed += image[row + 1][col - 1].rgbtRed;
                    avgGreen += image[row + 1][col - 1].rgbtGreen;
                    avgBlue += image[row + 1][col - 1].rgbtBlue;
                    counter++;
                }

                // check for outer bottom right adjacent
                if (col < width - 1)
                {
                    avgRed += image[row + 1][col + 1].rgbtRed;
                    avgGreen += image[row + 1][col + 1].rgbtGreen;
                    avgBlue += image[row + 1][col + 1].rgbtBlue;
                    counter++;
                }
            }

            // assign the colors to the pixel
            imageRet[row][col].rgbtRed = round(avgRed / (float) counter);
            imageRet[row][col].rgbtGreen = round(avgGreen / (float) counter);
            imageRet[row][col].rgbtBlue = round(avgBlue / (float) counter);
        }
    }

    // copy new image to old
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = imageRet[row][col];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0;
            int gyBlue = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxRed = 0;
            int gyRed = 0;

            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }
                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }

                    gxBlue += image[i + r][j + c].rgbtBlue * gx[r + 1][c + 1];
                    gyBlue += image[i + r][j + c].rgbtBlue * gy[r + 1][c + 1];
                    gxGreen += image[i + r][j + c].rgbtGreen * gx[r + 1][c + 1];
                    gyGreen += image[i + r][j + c].rgbtGreen * gy[r + 1][c + 1];
                    gxRed += image[i + r][j + c].rgbtRed * gx[r + 1][c + 1];
                    gyRed += image[i + r][j + c].rgbtRed * gy[r + 1][c + 1];
                }
            }

            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
