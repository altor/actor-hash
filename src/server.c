#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "utils/msg.h"
#include "utils/utils.c"
#include "utils/czmq_utils.h"
#include "actors/log_actor.h"
#include "actors/geohash_actor.h"
#include "hash/geohash.h"
int main (void)
{

  int state = TRUE;
  char err_msg[100];
  
  //actor creation
  FILE * log_file = fopen("../log", "w+");
  zactor_t * log_actor = log_actor_new( 0, FALSE, log_file);
  zactor_t * geohash_actor = geohash_actor_new(1, FALSE, log_actor);
  
  //client communication socket creation
  zsock_t * client_socket = zsock_new_pair ("@tcp://127.0.0.1:5555");
  if(client_socket == NULL){
    fprintf(stderr, "can't connect to socket");
    return -1;
  }

  while(state){
    
    // message reception
    msg_t msg;
    printf("toto\n");
    receive_one_frame(client_socket, &msg);
    printf("%d\n", msg.action_id);
    switch(msg.action_id){
    case GEO_ID:
      send_one_frame(zactor_sock(geohash_actor), &msg, sizeof(msg_t));
      break;
    case TERM_ID:
      printf("ok0\n");
      geohash_actor_destroy(geohash_actor);
      printf("ok1\n");
      log_actor_destroy(log_actor);
      printf("ok2\n");
      state = FALSE;
      break;
    default:

      sprintf(err_msg, "unknow action_id : %d", msg.action_id);
      log_actor_make_log(log_actor, err_msg);
      continue;
    }
  }
  zsock_unbind(client_socket, "@tcp://127.0.0.1:5555");
  zsock_destroy(&client_socket);
  return 0;
}
