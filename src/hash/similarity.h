#ifndef similarity_h
#define similarity_h

#include "../utils/buffer.h"

/**
 * encode any data its 16 byte similarity hash
 *
 * @param data : pointer to the data to hash
 * @param size : size of the data to hash (in bytes)
 * @param buffer : pointer to the buffer that going to store the 
                   similarity hash (which much have 16 bytes space)
 */ 
void similarity_encode(void * data, int size, buffer_t * buffer);

#endif
