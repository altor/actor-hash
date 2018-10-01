/**
 * =========================================================================
 * geohash_actor - hash longitude and latitude coordinate to the geohash format
 * =========================================================================
 */

#include <czmq.h>
#include "geohash_actor.h"
#include "../utils/czmq_utils.h"
#include "../utils/msg.h"
#include "../utils/utils.h"
#include "../utils/buffer.h"


//  --------------------------------------------------------------------------
//  THE SELF_T STructure holds the state for one actor instance

typedef struct {
  zsock_t *pipe;              //  Actor command pipe
  zpoller_t *poller;          //  Socket poller
  
  int id;
  zactor_t * log_actor;
  int terminated;            //  Did caller ask us to quit?
  int verbose;               //  Verbose logging enabled?
} self_t;

static self_t *
s_self_new (zsock_t *pipe, int id, int verbose_mode, zactor_t * log_actor)
{
  self_t *self = (self_t *) zmalloc (sizeof (self_t));
  self->pipe = pipe;
  self->id = id;
  self->log_actor = log_actor;
  self->terminated = FALSE;
  self->verbose = verbose_mode;
  self->poller = zpoller_new (self->pipe, NULL);
  return self;
}

static void
s_self_destroy (self_t **self_p)
{
  assert (self_p);
  if (*self_p) {
    self_t *self = *self_p;
    zpoller_destroy (&self->poller);

    free (self);
    *self_p = NULL;
  }
}


//  --------------------------------------------------------------------------
//  Handle a command from calling application

static int
s_self_handle_pipe (self_t *self)
{

  geohash_msg_t msg;
  receive_one_frame(self->pipe, &msg);

  if (self->verbose)
    zsys_info ("actor %d: API command=%s", self->id, msg.action_id);
  if (msg.action_id == VERBOSE_ID)
    self->verbose = TRUE;
  
  else if (msg.action_id == GEO_ID){
    buffer_t * buffer = buffer_create(10);
    printf("%f, %f\n", msg.coordinate.longitude, msg.coordinate.latitude);
    geohash_encode(msg.coordinate, 4, buffer);
    printf("%s\n", buffer_get_memory(buffer));
    log_actor_make_log(self->log_actor, buffer_get_memory(buffer));
    buffer_destroy(buffer);
    // !!!! GESTION ERREUR !!!!!!
  }
  else if (msg.action_id == TERM_ID ){
    self->terminated = TRUE;
    // !!!! GESTION ERREUR !!!!!!
  }
  else {
    zsys_error ("actor %d: - invalid command: %s", self->id, msg.action_id);
    assert (false);
  }

  
  /* zstr_free (&command); */
  /* zmsg_destroy (&request); */
  return 0;
}


//  --------------------------------------------------------------------------

typedef struct{
  int id;
  int verbose_mode;
  zactor_t * log_actor;

}geohash_actor_args_t;

void geohash_actor_fn(zsock_t *pipe, void *void_args)
{
  geohash_actor_args_t * args = (geohash_actor_args_t*)void_args;
  self_t *self = s_self_new(pipe, args->id, args->verbose_mode, args->log_actor);
  //  Signal successful initialization
  zsock_signal (pipe, 0);

  while (!self->terminated) {
    zsock_t *which = (zsock_t *) zpoller_wait (self->poller, -1);
    if (which == self->pipe)
      s_self_handle_pipe (self);
    else
      if (zpoller_terminated (self->poller))
	break;          //  Interrupted
  }
  s_self_destroy (&self);
}


//  --------------------------------------------------------------------------
//  INTERFACE
//  --------------------------------------------------------------------------

zactor_t *geohash_actor_new(int id, int verbose_mode, zactor_t * log_actor){
  geohash_actor_args_t args;
  args.id = id;
  args.verbose_mode = verbose_mode;
  args.log_actor = log_actor;
  return zactor_new(geohash_actor_fn, &args);    
}

/* void geohash_actor_encode(zactor_t * self, double longitude, double latitude){ */
/*   geohash_msg_t msg; */
/*   msg.action_id = GEO_ID; */
/*   msg.coordinate.latitude = latitude; */
/*   msg.coordinate.longitude = longitude; */
/*   send_one_frame(zactor_sock(self), &msg, sizeof(geohash_msg_t)); */
/* } */

void geohash_actor_destroy(zactor_t *self){
  geohash_msg_t msg;
  msg.action_id = TERM_ID;

  send_one_frame(zactor_sock(self), &msg, sizeof(geohash_msg_t));
  printf("toto2 %d\n", errno);
  if(errno == -1)
    return;
  zactor_destroy(&self);
  errno = 0;
}

