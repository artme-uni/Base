#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "coder.h"

char *table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main(int argc, char *argv[]) {

    int eflag = 0;
    int dflag = 0;
    int iflag = 0;
    int fvalue = -1;

    int c;
    char *pEnd;
    opterr = 0;
    while ((c = getopt(argc, argv, "eidf:")) != -1)
        switch (c) {
            case 'e':
                eflag = 1;
                break;
            case 'd':
                dflag = 1;
                break;
            case 'i':
                iflag = 1;
                break;
            case 'f':
                fvalue = strtol(optarg, &pEnd, 10);
                break;
        }


    if (eflag == 1)
        encode(argv[argc - 2], argv[argc - 1], fvalue);
    else if (dflag == 1)
        decode(argv[argc - 2], argv[argc - 1], iflag);
    else {
        printf("Usage: %s -e in out to encode\n%s -d in out to decode\n", argv[0], argv[0]);
        printf("\n Base64.exe -keys input.txt output.txt \n");
        printf("-e   - encode file \n");
        printf("-f N - write ENTER after N symbols \n");
        printf("-d   - decode file \n");
        printf("-i   - ignore none-base64 symbols \n");
    }


    return 0;
}