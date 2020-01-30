#include "add.h"
extern char *table;

unsigned char table_number(char a) {
    for (int i = 0; i < 64; ++i) {
        if (a == table[i])
            return i;
    }
    return 255;
}