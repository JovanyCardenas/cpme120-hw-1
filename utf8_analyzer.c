#include <stdio.h>
#include <stdbool.h> // include boolean

int main() {
    char text[256]; // char text input with size of 256

    fgets(text, sizeof(text), stdin); // gets input as the text var

    int byte_count = 0; // while loop until the string ends with \0
    bool valid_ascii = true;

    while (text[byte_count] != '\0') { // Ends at \0 - end string

        if (text[byte_count] == '\n') { // Finds the extra \n at the end - new line
            text[byte_count] = '\0'; // replace \n with \0
            break; // exits while loop since it found the end and replaced \n with \0
        }

        unsigned char ch = text[byte_count]; // interpret byte as an unsigned char

        if (ch > 127) { // check to see if its outside 0-127 which is ASCII size
            valid_ascii = false;
        }

        // printf("%c\n", text[i]); // this prints the letters per line (Debugging Line)
        byte_count++; // increments
    }

    if (valid_ascii) {
        printf("Valid ASCII: true\n");
    }else {
        printf("Valid ASCII: false\n");
    }
    // printf("Uppercased ASCII: %s\n", uppercase_ascii);
    printf("Length in bytes: %d\n", byte_count); // test for printing total bytes
    // printf("Number of code points: %d\n", code_point_count);
    // printf("Bytes per code points: %s\n", bytes_per_code_point);
    // printf("Substring of the first 6 code points: %s\n", substr_cp);
    // printf("Code points as decimal numbers: %s", code_points_decimal);
    // printf("Animal emojis: %s", emojis);

    return 0;
}
