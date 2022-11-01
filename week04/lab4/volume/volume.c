#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int WAV_HEADER_SIZE = 44;

uint8_t header[WAV_HEADER_SIZE];

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    fread(header, sizeof(uint8_t), WAV_HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), WAV_HEADER_SIZE, output);

    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    fclose(input);
    fclose(output);
}

