#include <czmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "utils/msg.h"
#include "utils/czmq_utils.h"
#include "actors/geohash_actor.h"

int main (int argc, char ** argv)
{
  geohash_msg_t msg2;
  if(argc < 1){
    fprintf(stderr, "bad number of parameters");
    return -1;
  }
  
  // server connexion
  zsock_t * server_socket = zsock_new_pair (">tcp://127.0.0.1:5555");
  if(server_socket == NULL){
    fprintf(stderr, "can't connect to server");
    return -1;
  }

  
  //message creation
  msg_t msg;
  char toot[1000];

  switch(atoi(argv[1])){
  case 0:
    msg.action_id = TERM_ID;
    scanf("%s", toot);
    send_one_frame(server_socket, &msg, sizeof(msg_t));
    break;
  case 1:

    msg2.coordinate.longitude = atof(argv[2]);
    msg2.coordinate.latitude = atof(argv[3]);
    msg2.action_id = GEO_ID;
    scanf("%s", toot);
    //sending
    send_one_frame(server_socket, &msg2, sizeof(geohash_msg_t));
    break;
  }
  
  if(errno == -1){
    fprintf(stderr, "error during sending");
    return -1;
  }
  
  //
  zsock_disconnect(server_socket, "tcp://127.0.0.1:5555");
  zsock_destroy(&server_socket);

  return 0;
}
