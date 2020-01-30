#include "coder.h"

extern char *table;

int decode(char input[], char output[], int flag)
{

    FILE *input1;
    if ((input1 = fopen(input, "r")) == NULL)
    {
        printf("Cannot open %s \n", input);
        exit(1);
    }

    FILE *output1;
    if ((output1 = fopen(output, "wb")) == NULL)
    {
        printf("Cannot open %s \n", output);
        exit(1);
    }

    const int size = 1024 * 3;

    char *read = malloc(sizeof(char) * (4 / 3) * size);
    unsigned char *write = malloc(sizeof(unsigned char) * size);

    int read_count = fread(read, 1, size, input1);
    int write_count = 0;

    unsigned char letters[4];
    int letters_lenght = 0;

    while (read_count != 0)
    {
        if (read_count % 4 != 0 && flag == 0)
        {
            printf("bad input\n");
            return 1;
        }

        for (int i = 0; i < read_count; i++)
        {

            unsigned char letter = table_number(read[i]);
            if (letter != 255 || read[i] == '=')
            {
                letters[letters_lenght] = letter;
                letters_lenght++;
            } else if (flag == 0)
            {
                printf("bad input\n");
                return 1;
            }

            if (letters_lenght == 4)
            {
                unsigned char a1 = letters[0];
                unsigned char a2 = letters[1];
                unsigned char a3 = letters[2];
                unsigned char a4 = letters[3];

                unsigned char b1 = (a1 << 2) | (a2 >> 4);
                unsigned char b2 = (a2 << 4) | (a3 >> 2);
                unsigned char b3 = (a3 << 6) | (a4);

                write[write_count++] = b1;
                if (letters[2] != 255)
                    write[write_count++] = b2;
                if (letters[3] != 255)
                    write[write_count++] = b3;

                letters_lenght = 0;

            }
        }


        fwrite(write, 1, write_count, output1);

        write_count = 0;
        read_count = fread(read, 1, size, input1);
    }

    free(read);
    free(write);

    fclose(input1);
    fclose(output1);

}

int encode(char input[], char output[], int fvalue)
{

    FILE *input1;
    if ((input1 = fopen(input, "rb")) == NULL)
    {
        printf("Cannot open %s \n", input);
        exit(1);
    }

    FILE *output1;
    if ((output1 = fopen(output, "w")) == NULL)
    {
        printf("Cannot open %s \n", output);
        exit(1);
    }

    const int size = 1024 * 3;

    unsigned char *read = malloc(sizeof(unsigned char) * size);
    char *write = malloc(sizeof(char) * (4 / 3) * size);

    int read_count = fread(read, 1, size, input1);
    int write_count = 0;

    while (read_count != 0)
    {
        if (read_count % 3 != 0)
        {
            read[read_count] = '\0';
        }

        if (read_count % 3 == 1)
        {
            read[read_count + 1] = '\0';
        }

        for (int i = 0; i < read_count; i += 3)
        {

            unsigned char a1 = read[i];
            unsigned char a2 = read[i + 1];
            unsigned char a3 = read[i + 2];

            char b1 = a1 >> 2;
            char b2 = (a2 >> 4) | (a1 << 4 & 63);
            char b3 = (a3 >> 6) | (a2 << 2 & 63);
            char b4 = (a3 & 63);

            write[write_count++] = table[b1];

            if (fvalue > 0 && (write_count + 1) % fvalue == 0) write[write_count++] = '\n';

            write[write_count++] = table[b2];

            if (fvalue > 0 && (write_count + 1) % fvalue == 0) write[write_count++] = '\n';

            if ((i + 1) >= read_count)
            {
                write[write_count++] = '=';
                if (fvalue > 0 && (write_count + 1) % fvalue == 0) write[write_count++] = '\n';
            } else
            {
                write[write_count++] = table[b3];
                if (fvalue > 0 && (write_count + 1) % fvalue == 0) write[write_count++] = '\n';
            }

            if ((i + 2) >= read_count)
            {
                write[write_count++] = '=';
                if (fvalue > 0 && (write_count + 1) % fvalue == 0) write[write_count++] = '\n';
            }
            else
            {
                write[write_count++] = table[b4];
                if (fvalue > 0 && (write_count + 1) % fvalue == 0) write[write_count++] = '\n';
            }
        }

        fwrite(write, 1, write_count, output1);

        write_count = 0;
        read_count = fread(read, 1, size, input1);
    }

    free(read);
    free(write);

    fclose(input1);
    fclose(output1);

}

