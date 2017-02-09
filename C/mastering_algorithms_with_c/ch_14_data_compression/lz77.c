
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include "bit.h"
#include "compress.h"

static int compare_win(const unsigned char* window, const unsigned char
* buffer, int* offset, unsigned char* next)
{
    int match,
            longest,
            i,
            j,
            k;
    *offset = 0;
    longest = 0;
    *next = buffer[0];
    for (k = 0; k < LZ77_WINDOW_SIZE; k++) {
        i = k;
        j = 0;
        match = 0;

        /**************************************************************************
        *                                                                         *
        *  Determine how many symbols match in the sliding window at offset k.    *
        *                                                                         *
        **************************************************************************/

        while (i < LZ77_WINDOW_SIZE && j < LZ77_BUFFER_SIZE - 1) {
            if (window[i] != buffer[j]) {
                break;
            }
            match++;
            i++;
            j++;
        }

        /**************************************************************************
        *                                                                         *
        *  Keep track of the offset, length, and next symbol for the best match.  *
        *                                                                         *
        **************************************************************************/

        if (match > longest) {
            *offset = k;
            longest = match;
            *next = buffer[j];
        }
    }
    return longest;
}

int lz77_compress(const unsigned char* original, unsigned char** compressed,
                  int size)
{
    unsigned long token;

    unsigned char window[LZ77_WINDOW_SIZE],
            buffer[LZ77_BUFFER_SIZE],
            * comp,
            * temp,
            next;

    int offset,
            length,
            remaining,
            tbits,
            hsize,
            ipos,
            opos,
            tpos,
            i;
    *compressed = NULL;
    hsize = sizeof(int);
    if ((comp = (unsigned char*) malloc(hsize)) == NULL) {
        return -1;
    }
    memcpy(comp, &size, sizeof(int));
    memset(window, 0, LZ77_WINDOW_SIZE);
    memset(buffer, 0, LZ77_BUFFER_SIZE);
    ipos = 0;
    for (i = 0; i < LZ77_BUFFER_SIZE && ipos < size; i++) {
        buffer[i] = original[ipos];
        ipos++;
    }
    opos = hsize * 8;
    remaining = size;
    while (remaining > 0) {
        if ((length = compare_win(window, buffer, &offset, &next)) != 0) {

            /***********************************************************************
            *                                                                      *
            *  Encode a phrase token.                                              *
            *                                                                      *
            ***********************************************************************/

            token = 0x00000001 << (LZ77_PHRASE_BITS - 1);

            /***********************************************************************
            *                                                                      *
            *  Set the offset where the match was found in the sliding window.     *
            *                                                                      *
            ***********************************************************************/

            token = token | (offset << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS -
                                        LZ77_WINOFF_BITS));

            /***********************************************************************
            *                                                                      *
            *  Set the length of the match.                                        *
            *                                                                      *
            ***********************************************************************/

            token = token | (length << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS -
                                        LZ77_WINOFF_BITS - LZ77_BUFLEN_BITS));

            /***********************************************************************
            *                                                                      *
            *  Set the next symbol in the look-ahead buffer after the match.       *
            *                                                                      *
            ***********************************************************************/

            token = token | next;

            /***********************************************************************
            *                                                                      *
            *  Set the number of bits in the token.                                *
            *                                                                      *
            ***********************************************************************/

            tbits = LZ77_PHRASE_BITS;
        } else {

            /***********************************************************************
            *                                                                      *
            *  Encode a symbol token.                                              *
            *                                                                      *
            ***********************************************************************/

            token = 0x00000000;

            /***********************************************************************
            *                                                                      *
            *  Set the unmatched symbol.                                           *
            *                                                                      *
            ***********************************************************************/

            token = token | next;

            /***********************************************************************
            *                                                                      *
            *  Set the number of bits in the token.                                *
            *                                                                      *
            ***********************************************************************/

            tbits = LZ77_SYMBOL_BITS;
        }

        /**************************************************************************
        *                                                                         *
        *  Ensure that the token is in big-endian format.                         *
        *                                                                         *
        **************************************************************************/

        token = htonl(token);

        /**************************************************************************
        *                                                                         *
        *  Write the token to the buffer of compressed data.                      *
        *                                                                         *
        **************************************************************************/

        for (i = 0; i < tbits; i++) {
            if (opos % 8 == 0) {

                /********************************************************************
                *                                                                   *
                *  Allocate another byte for the buffer of compressed data.         *
                *                                                                   *
                ********************************************************************/

                if ((temp = (unsigned char*) realloc(comp, (opos / 8) + 1)) == NULL) {
                    free(comp);
                    return -1;
                }
                comp = temp;
            }
            tpos = (sizeof(unsigned long) * 8) - tbits + i;
            bit_set(comp, opos, bit_get((unsigned char*) &token, tpos));
            opos++;
        }

        /**************************************************************************
        *                                                                         *
        *  Adjust the phrase length to account for the unmatched symbol.          *
        *                                                                         *
        **************************************************************************/

        length++;

        /**************************************************************************
        *                                                                         *
        *  Copy data from the look-ahead buffer to the sliding window.            *
        *                                                                         *
        **************************************************************************/

        memmove(&window[0], &window[length], LZ77_WINDOW_SIZE - length);
        memmove(&window[LZ77_WINDOW_SIZE - length], &buffer[0], length);

        /**************************************************************************
        *                                                                         *
        *  Read more data into the look-ahead buffer.                             *
        *                                                                         *
        **************************************************************************/

        memmove(&buffer[0], &buffer[length], LZ77_BUFFER_SIZE - length);
        for (i = LZ77_BUFFER_SIZE - length; i < LZ77_BUFFER_SIZE && ipos < size; i++) {
            buffer[i] = original[ipos];
            ipos++;
        }

        /**************************************************************************
        *                                                                         *
        *  Adjust the total symbols remaining by the phrase length.               *
        *                                                                         *
        **************************************************************************/

        remaining = remaining - length;
    }
    *compressed = comp;
    return ((opos - 1) / 8) + 1;
}

int lz77_uncompress(const unsigned char* compressed, unsigned char
** original)
{
    unsigned char window[LZ77_WINDOW_SIZE],
            buffer[LZ77_BUFFER_SIZE],
            * orig,
            * temp,
            next;

    int offset,
            length,
            remaining,
            hsize,
            size,
            ipos,
            opos,
            tpos,
            state,
            i;
    *original = orig = NULL;
    hsize = sizeof(int);
    memcpy(&size, compressed, sizeof(int));
    memset(window, 0, LZ77_WINDOW_SIZE);
    memset(buffer, 0, LZ77_BUFFER_SIZE);
    ipos = hsize * 8;
    opos = 0;
    remaining = size;
    while (remaining > 0) {

        /**************************************************************************
        *                                                                         *
        *  Get the next bit in the compressed data.                               *
        *                                                                         *
        **************************************************************************/

        state = bit_get(compressed, ipos);
        ipos++;
        if (state == 1) {

            /***********************************************************************
            *                                                                      *
            *  Handle processing a phrase token.                                   *
            *                                                                      *
            ***********************************************************************/

            memset(&offset, 0, sizeof(int));
            for (i = 0; i < LZ77_WINOFF_BITS; i++) {
                tpos = (sizeof(int) * 8) - LZ77_WINOFF_BITS + i;
                bit_set((unsigned char*) &offset, tpos, bit_get(compressed, ipos));
                ipos++;
            }
            memset(&length, 0, sizeof(int));
            for (i = 0; i < LZ77_BUFLEN_BITS; i++) {
                tpos = (sizeof(int) * 8) - LZ77_BUFLEN_BITS + i;
                bit_set((unsigned char*) &length, tpos, bit_get(compressed, ipos));
                ipos++;
            }
            next = 0x00;
            for (i = 0; i < LZ77_NEXT_BITS; i++) {
                tpos = (sizeof(unsigned char) * 8) - LZ77_NEXT_BITS + i;
                bit_set((unsigned char*) &next, tpos, bit_get(compressed, ipos));
                ipos++;
            }

            /***********************************************************************
            *                                                                      *
            *  Ensure that the offset and length have the correct byte ordering    *
            *  for the system.                                                     *
            *                                                                      *
            ***********************************************************************/

            offset = ntohl(offset);
            length = ntohl(length);

            /***********************************************************************
            *                                                                      *
            *  Write the phrase from the window to the buffer of original data.    *
            *                                                                      *
            ***********************************************************************/

            i = 0;
            if (opos > 0) {
                if ((temp = (unsigned char*) realloc(orig, opos + length + 1)) == NULL) {
                    free(orig);
                    return -1;
                }
                orig = temp;
            } else {
                if ((orig = (unsigned char*) malloc(length + 1)) == NULL) {
                    return -1;
                }
            }
            while (i < length && remaining > 0) {
                orig[opos] = window[offset + i];
                opos++;

                /********************************************************************
                *                                                                   *
                *  Record each symbol in the look-ahead buffer until ready to       *
                *  update the sliding window.                                       *
                *                                                                   *
                ********************************************************************/

                buffer[i] = window[offset + i];
                i++;

                /********************************************************************
                *                                                                   *
                *  Adjust the total symbols remaining to account for each symbol    *
                *  consumed.                                                        *
                *                                                                   *
                ********************************************************************/

                remaining--;
            }

            /***********************************************************************
            *                                                                      *
            *  Write the unmatched symbol to the buffer of original data.          *
            *                                                                      *
            ***********************************************************************/

            if (remaining > 0) {
                orig[opos] = next;
                opos++;

                /********************************************************************
                *                                                                   *
                *  Also record this symbol in the look-ahead buffer.                *
                *                                                                   *
                ********************************************************************/

                buffer[i] = next;

                /********************************************************************
                *                                                                   *
                *  Adjust the total symbols remaining to account for the unmatched  *
                *  symbol.                                                          *
                *                                                                   *
                ********************************************************************/

                remaining--;
            }

            /***********************************************************************
            *                                                                      *
            *  Adjust the phrase length to account for the unmatched symbol.       *
            *                                                                      *
            ***********************************************************************/

            length++;
        } else {

            /***********************************************************************
            *                                                                      *
            *  Handle processing a symbol token.                                   *
            *                                                                      *
            ***********************************************************************/

            next = 0x00;
            for (i = 0; i < LZ77_NEXT_BITS; i++) {
                tpos = (sizeof(unsigned char) * 8) - LZ77_NEXT_BITS + i;
                bit_set((unsigned char*) &next, tpos, bit_get(compressed, ipos));
                ipos++;
            }

            /***********************************************************************
            *                                                                      *
            *  Write the symbol to the buffer of original data.                    *
            *                                                                      *
            ***********************************************************************/

            if (opos > 0) {
                if ((temp = (unsigned char*) realloc(orig, opos + 1)) == NULL) {
                    free(orig);
                    return -1;
                }
                orig = temp;
            } else {
                if ((orig = (unsigned char*) malloc(1)) == NULL) {
                    return -1;
                }
            }
            orig[opos] = next;
            opos++;

            /***********************************************************************
            *                                                                      *
            *  Record the symbol in the look-ahead buffer until ready to update    *
            *  the sliding window.                                                 *
            *                                                                      *
            ***********************************************************************/

            if (remaining > 0) {
                buffer[0] = next;
            }

            /***********************************************************************
            *                                                                      *
            *  Adjust the total symbols remaining to account for the unmatched     *
            *  symbol.                                                             *
            *                                                                      *
            ***********************************************************************/

            remaining--;

            /***********************************************************************
            *                                                                      *
            *  Set the phrase length to account for the unmatched symbol.          *
            *                                                                      *
            ***********************************************************************/

            length = 1;
        }

        /**************************************************************************
        *                                                                         *
        *  Copy the look-ahead buffer into the sliding window.                    *
        *                                                                         *
        **************************************************************************/

        memmove(&window[0], &window[length], LZ77_WINDOW_SIZE - length);
        memmove(&window[LZ77_WINDOW_SIZE - length], &buffer[0], length);
    }
    *original = orig;
    return opos;
}
