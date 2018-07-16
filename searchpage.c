#include <stdio.h>
#include <stdlib.h>
/* This program reads a Unitel disc image containing Videotex pages and
 * generates a liste of ranges for the cut command. It does not care about the
 * disc filesystem as it tries to directly detect Videotex pages.
 * The disc image is read from the standard input and ranges are printed on the
 * standard output.
 * It is quick and dirty! A better approach would be to interpret the filesystem
 * structure and extract files.
 */

/* A 4 megabyte buffer should be enough for a Unitel disc image :-) */
#define BUFFERSIZE (4*1024*1024)
unsigned char bytes_in[BUFFERSIZE];

int main(int argc, char *argv[]) {
    ssize_t total_bytes = 0;
    ssize_t start = 0;
    ssize_t offset = 0;
    int byte_in = 0;

    /* Read the entire file in memory (quick, inefficient and dirty) */
    while((byte_in = getchar()) != EOF) {
        bytes_in[total_bytes++] = byte_in;
    }

    /* The program consider that pages are recorded every 32 bytes at minimum */
    for(start = 0; start < total_bytes; start += 32) {
        /* Consider a Videotex page starts with 0x1E or 0x1F code */
        if(bytes_in[start] != 0x1E && bytes_in[start] != 0x1F) continue;

        for(
            offset = start;

            /* Videotex codes must be between 0x01 and 0x7F, everything else
             * cannot be part of a Videotex page.
             */
            offset < total_bytes &&
            bytes_in[offset] <= 0x7F &&
            bytes_in[offset] > 0x00;

            offset++
        );

        /* Prints the range formatted for the cut command */
        printf("%d-%d\n", start, offset);

        /* Go to the next authorized offset (quick and dirty) */
        for(start = offset; start % 32 != 0; start++);
    }
}