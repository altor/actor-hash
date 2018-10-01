#include <errno.h>
#include <stdlib.h>

#include "buffer.h"

buffer_t * buffer_create(int size){
  buffer_t * buffer = malloc(sizeof(buffer_t));

  buffer->memory = malloc(size * sizeof(char));
  buffer->size = size;
}

void buffer_destroy(buffer_t * buffer){
  free(buffer->memory);
  free(buffer);
}

int buffer_get_size(buffer_t * buffer){
  return buffer->size;
}

char * buffer_get_memory(buffer_t * buffer){
  return buffer->memory;
}

void buffer_set(buffer_t * buffer, int i, char val){
  if(i > buffer->size){
    errno = -1;
    return;
  }
  
  buffer->memory[i] = val;
  errno = 0;
}

char buffer_get(buffer_t * buffer, int i){
  if(i > buffer->size){
    errno = -1;
    return -1;
  }
  
  errno = 0;
  return buffer->memory[i];
}
