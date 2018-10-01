#ifndef utils_h
#define utils_h

#include "buffer.h"

#define TRUE 1==1
#define FALSE 1!=1

/**
 * extract the n th bit from x
 */
char utils_extract_bit_n(int x, int n);

/**
 * write the base 32 representation of n in buffer. 
 * 
 * @errno - 1 if the buffer is too small to write the representation
*/
void utils_to_b32(unsigned int n, buffer_t * buffer);
#endif


