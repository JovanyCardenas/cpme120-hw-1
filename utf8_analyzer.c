#include <stdio.h>
#include <stdbool.h> // include boolean

int main() {
    char text[256]; // char text input with size of 256

    fgets(text, sizeof(text), stdin); // gets input as the text var

    // initialize variables
    int byte_count = 0; // while loop until the string ends with \0
    bool valid_ascii = true;
    char uppercase_ascii[256]; // stores uppercase ascii characters
    int code_point_count = 0; // stores the total code points
    int bytes_per_code_point[256]; // stores the byte size of each code point

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
            uppercase_ascii[byte_count] = ch - 32; // subtracks 32 since 'A'=65 and 'a'=97 -> 97-65=32
        } else {
            uppercase_ascii[byte_count] = ch; // if they are not lower-case they will be left as they were
        }

        // printf("%c\n", text[i]); // this prints the letters per line (Debugging Line)
        byte_count++; // increments
    }

    uppercase_ascii[byte_count] = '\0'; // sets the last character as a null terminator to end the string

    int index = 0;

    while (text[index] != '\0') {
        unsigned char ch = text[index];
        int cp_bytes;

        if (ch <= 127) { // ASCII characters use 1 byte
            cp_bytes = 1;
        } else if ((ch & 0xE0) == 0xC0) { // starts with 110, so it uses 2 bytes
            cp_bytes = 2;
        } else if ((ch & 0xF0) == 0xE0) { // starts with 1110, so it uses 3 bytes
            cp_bytes = 3;
        } else if ((ch & 0xF8) == 0xF0) { // starts with 11110, so it uses 4 bytes
            cp_bytes = 4;
        }

        bytes_per_code_point[code_point_count] = cp_bytes; // store cp_bytes before increasing code_point_count

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

    printf("Bytes per code points: ");
    for (int i = 0; i < code_point_count; i++) { // loops through the whole code_point_count array and prints the result
        printf("%d ", bytes_per_code_point[i]);
    }
    printf("\n"); // new line

    printf("Substring of the first 6 code points: %s\n", substr_cp);
    // printf("Code points as decimal numbers: %s", code_points_decimal);
    // printf("Animal emojis: %s", emojis);

    return 0;
}

/*
 *  I am not as familiar with C programming language so I did use W3Schools to search for
 *  specific language information for C.
 */