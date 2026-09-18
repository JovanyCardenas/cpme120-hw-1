#include <stdio.h>
#include <stdbool.h> // include boolean

/*  Jovany Cardenas Vargas
 *  CMPE 120 - HW #1
 *  Started 9/17/2026 2:15pm
 *  Completed 9/17/2026 6:45pm
 */

int main() {
    char text[256]; // char text input with size of 256

    fgets(text, sizeof(text), stdin); // gets input as the text var

    // initialize variables
    int byte_count = 0; // while loop until the string ends with \0
    bool valid_ascii = true;
    char uppercase_ascii[256]; // stores uppercase ascii characters
    int code_point_count = 0; // stores the total code points
    int bytes_per_code_point[256]; // stores the byte size of each code point
    unsigned int code_points_decimal[256];

    while (text[byte_count] != '\0') { // Ends at \0 - end string

        if (text[byte_count] == '\n') { // Finds the extra \n at the end - new line
            text[byte_count] = '\0'; // replace \n with \0
            break; // exits while loop since it found the end and replaced \n with \0
        }

        unsigned char ch = text[byte_count]; // interpret byte as an unsigned char

        if (ch > 127) { // check to see if its outside 0-127 which is ASCII size
            valid_ascii = false;
        }

        if (ch >= 97 && ch <= 122) { // Checks to see if they fall from 'a'=97 - 'z'=122
            uppercase_ascii[byte_count] = ch - 32; // subtracts 32 since 'A'=65 and 'a'=97 -> 97-65=32
        } else {
            uppercase_ascii[byte_count] = ch; // if they are not lower-case they will be left as they were
        }

        // printf("%c\n", text[byte_count]); // this prints the letters per line (Debugging Line)
        byte_count++; // increments
    }

    uppercase_ascii[byte_count] = '\0'; // sets the last character as a null terminator to end the string

    int index = 0;

    // UTF-8 uses marker bits at the start of each byte.
    // The masks remove those marker bits and the shifts put the remaining
    // bits back together to get the Unicode code point value.

    while (text[index] != '\0') {
        unsigned char ch = text[index];
        int cp_bytes;
        unsigned int code_point;

        if (ch <= 127) { // ASCII characters use 1 byte
            cp_bytes = 1;

            // ASCII stores the code point value in the single byte
            code_point = ch;

        } else if ((ch & 0xE0) == 0xC0) { // starts with 110, so it uses 2 bytes
            cp_bytes = 2;

            // remove 110 and 10 UTF-8 markers, then combine the remaining bits
            code_point = ((ch & 0x1F) << 6) | (text[index + 1] & 0x3F);

        } else if ((ch & 0xF0) == 0xE0) { // starts with 1110, so it uses 3 bytes
            cp_bytes = 3;

            // remove 1110 and 10 UTF-8 markers, then shift and combine the remaining bits
            code_point = ((ch & 0x0F) << 12)
                   | ((text[index + 1] & 0x3F) << 6)
                   | (text[index + 2] & 0x3F);

        } else if ((ch & 0xF8) == 0xF0) { // starts with 11110, so it uses 4 bytes
            cp_bytes = 4;

            // remove 11110 and 10 UTF-8 markers, then shift and combine the remaining bits
            code_point = ((ch & 0x07) << 18)
                       | ((text[index + 1] & 0x3F) << 12)
                       | ((text[index + 2] & 0x3F) << 6)
                       | (text[index + 3] & 0x3F);
        }

        bytes_per_code_point[code_point_count] = cp_bytes; // store cp_bytes before increasing code_point_count

        code_points_decimal[code_point_count] = code_point;

        index += cp_bytes;
        code_point_count++; // one group of bytes is one code point
    }

    char substr_cp[256]; // gets the first 6 code points
    int substring_bytes = 0;

    // find how many bytes are used by the first code points
    for (int i = 0; i < code_point_count && i < 6; i++) {
        substring_bytes += bytes_per_code_point[i];
    }

    // copy those bytes into the substring
    for (int i = 0; i < substring_bytes; i++) {
        substr_cp[i] = text[i];
    }

    substr_cp[substring_bytes] = '\0'; // end the substring

    if (valid_ascii) { // true & false printing
        printf("Valid ASCII: true\n");
    } else {
        printf("Valid ASCII: false\n");
    }
    printf("Uppercased ASCII: %s\n", uppercase_ascii);
    printf("Length in bytes: %d\n", byte_count); // test for printing total bytes
    printf("Number of code points: %d\n", code_point_count);

    printf("Bytes per code point: ");
    for (int i = 0; i < code_point_count; i++) { // loops through the whole code_point_count array and prints the result
        printf("%d ", bytes_per_code_point[i]);
    }
    printf("\n"); // new line

    printf("Substring of the first 6 code points: %s\n", substr_cp);
    printf("Code points as decimal numbers: ");

    for (int i = 0; i < code_point_count; i++) {
        printf("%u ", code_points_decimal[i]);
    }
    printf("\n");

    printf("Animal emojis: ");

    int byte_index = 0; // keeps track of byte position

    for (int i = 0; i < code_point_count; i++) {

        // check if code point is either in either animal emoji range
        if ((code_points_decimal[i] >= 128000 && code_points_decimal[i] <= 128063) ||
            (code_points_decimal[i] >= 129408 && code_points_decimal[i] <= 129454)) {

            // print all the bytes that make up the emoji
            for (int j = 0; j < bytes_per_code_point[i]; j++) {
                printf("%c", text[byte_index + j]);
            }
        }

        // move to the next code point in text
        byte_index += bytes_per_code_point[i];
    }
    printf("\n");


    return 0;
}

/*
 *  I am not as familiar with C programming language so I did use other sources to search for
 *  certain language information and context for C.
 */