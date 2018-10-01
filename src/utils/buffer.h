#ifndef buffer_h
#define buffer_h
/**
 * Structure to use char array without losing information about their size
 */

typedef struct{
  char * memory;
  int size;
}buffer_t;


/**
 * create a buffer of a given size
 *
 * @return a pointer to the created buffer
 *
 */ 
buffer_t * buffer_create(int size);


/**
 * free the memory occupied by a buffer
 *
 * @param a pointer to a buffer
 *
 */ 
void buffer_destroy(buffer_t * buffer);

/**
 * get the buffer size
 *
 * @return the buffer size
 *
 */ 
int buffer_get_size(buffer_t * buffer);

/**
 * get the full buffer memory
 *
 * @return the full buffer memory
 *
 */ 
char * buffer_get_memory(buffer_t * buffer);

/**
 * set the ith byte of buffer to val
 *
 * @param buffer : buffer to modify
 * @param i : ith byte
 * @param val : value that going to be write at the ith byte of buffer
 *
 * @errno 0 if the byte was correctly writen 
 *        -1 if i > buffer.size
 */ 
void buffer_set(buffer_t * buffer, int i, char val);

/**
 * get the ith byte of buffer
 *
 * @param buffer : buffer that store the value
 * @param i : ith byte
 *
 * @return the ith byte of buffer
 *
 * @errno 0 if the byte was return
 *        -1 if i > buffer.size
 */ 
char buffer_get(buffer_t * buffer, int i);
#endif
