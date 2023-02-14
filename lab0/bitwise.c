#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BIT(n) (1<<(n))

char *byte2bin(uint8_t n, char *binstr) 
{
    // one element per bit (0/1)
    uint8_t binary[8];

    int i = 0;
    for (i = 0; i < 8; i++) {
        binary[i] = n % 2;
        n = n / 2;
    }

    // printing binary array in reverse order
    for (int j = 7, k= 0; j >= 0; j--, k++) {
        sprintf(binstr + k, "%d", binary[j]);
    }
        
	return binstr;
}

void print_usage(char *name) {
	printf("Usage: %s <action> <byte> <bit no>\n", name);
	printf("\tWhere: <action> one of 'h'|'l'|'r'|'s'|'t'\n"
		"\t\t <byte> 8-bit integer in hexadecimal\n"
		"\t\t <bit no> of bit to operate on\n");
}

void print_result(unsigned long n, char *binary) {
    byte2bin(n, binary);
    binary[8] = '\0';
    printf("<result> %s\n", binary);
}

int main(int argc, char *argv[])
{
	char a;	// action: 'h', 'l', 'r', 's', 't'
	unsigned long n; // value to convert must be smaller than 256
	int bit; // bit to operate on: must be between 0 an 7
    char binary[9]; // array for binary representation of n,
					//  remember that in C strings are terminated with a 0
 
	// Validate command line arguments
    if (argc != 4 ||
        (*argv[1] != 'h' && *argv[1] != 'l' && *argv[1] != 'r' && *argv[1] != 's' && *argv[1] != 't') ||
        (argv[2][0] != '0' || argv[2][1] != 'x' || strtol(argv[2], NULL, 16) >= 256) ||
        (atoi(argv[3]) < 0 || atoi(argv[3]) > 7)) {
        print_usage("bitwise");
        return EXIT_FAILURE;
    }

    a = *argv[1];
    n = strtol(argv[2], NULL, 16);
    bit = atoi(argv[3]);

	// Print to stdout the binary representation of n
	printf("<action> %c\n", a);
    byte2bin(n, binary);
    binary[8] = '\0';
    printf("<byte> %s\n", binary);
    printf("<bit no> %d\n", bit);
    
	// Do what the user asked and print the result
	switch (a) {
        case 'h':
            if (n & BIT(bit))
                printf("<result> true\n");
            else
                printf("<result> false\n");
            break;
        case 'l':
            if (n & BIT(bit))
                printf("<result> false\n");
            else
                printf("<result> true\n");
            break;
        case 's':
            n |= BIT(bit);
            print_result(n, binary);
            break;
        case 'r':
            n &= ~BIT(bit);
            print_result(n, binary);
            break;
        case 't':
            if (n & BIT(bit))
                n &= ~BIT(bit);
            else
                n |= BIT(bit);
            print_result(n, binary);
            break;
    }
    return 0;
}
