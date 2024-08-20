// This program reads an SD card and recovers deleted photos.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid Syntax: ./recover {file name}\n");
        return 1;
    }

    // open the file
    FILE *f = fopen(argv[1], "r");

    // check if the file exists
    if (!f)
    {
        printf("No file could be opened.\n");
        return 1;
    }

    uint8_t buffer[512];
    int imageCounter = 0;
    FILE *newFile = NULL;
    char fileName[8];

    while (fread(&buffer, sizeof(buffer), 1, f))
    {
        // check if it's the header of a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            // if it already has an open file then write to it and close it
            if (newFile)
            {
                fclose(newFile);
            }

            // create the new file
            sprintf(fileName, "%03i.jpg", imageCounter);
            newFile = fopen(fileName, "w");
            imageCounter++;
        }

        if (newFile)
        {
            fwrite(buffer, sizeof(buffer), 1, newFile);
        }
    }

    if (newFile)
    {
        fclose(newFile);
    }

    fclose(f);
}
