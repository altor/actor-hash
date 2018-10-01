#include <stdlib.h>
#include <errno.h>
#include <czmq.h>

#include "czmq_utils.h"

void receive_one_frame(void * src, char * buffer){
  zframe_t * msg_frame = zframe_recv (src);
  if(msg_frame == NULL){
    errno = -1;
    return;
  }
  char * data = zframe_data(msg_frame);
  for(int i = 0; i < zframe_size(msg_frame); i++)
    buffer[i] = data[i];

  zframe_destroy(&msg_frame);
  errno = 0;
  return;
}

void send_one_frame(void * dest, void * msg, int size){
  zframe_t * msg_frame = zframe_new(msg, size);
  errno = zframe_send(&msg_frame, dest, 0);
}
