#ifndef czmq_utils_h
#define czmq_utils_h


/**
 * wait for a msg of one frame long, from a source and write it on a given 
 * memory space
 * @errno 0 if the msg was write correctly in the given memory space
 *        -1 if an error was ocurre during reception
 */
void receive_one_frame(void * src, char * buffer);

/**
 * send a message of size byte to dest
 * @errno 0 if the msg was send correctly
 *        -1 if an error was ocurre during sending
 */
void send_one_frame(void * dest, void * msg, int size);

#endif
