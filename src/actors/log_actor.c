/**
 * =========================================================================
 * log_actor - write received msg in a log file
 * 
 *     - (LOG_ID, msg(string)) : write [msg] in the log file
 * =========================================================================
 */
#include <czmq.h>
#include "log_actor.h"
#include "../utils/czmq_utils.h"
#include "../utils/msg.h"
#include "../utils/utils.h"

//  --------------------------------------------------------------------------
//  THE SELF_T STructure holds the state for one actor instance

typedef struct {
  zsock_t *pipe;              //  Actor command pipe
  zpoller_t *poller;          //  Socket poller
  
  int id;
  FILE * output_file;
  
  int terminated;            //  Did caller ask us to quit?
  int verbose;               //  Verbose logging enabled?
} self_t;

static self_t *
s_self_new (zsock_t *pipe, int id, FILE * output_file, int verbose_mode)
{
  self_t *self = (self_t *) zmalloc (sizeof (self_t));
  self->pipe = pipe;
  self->id = id;
  self->output_file = output_file;
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

    fclose(self->output_file);
    
    free (self);
    *self_p = NULL;
  }
}


//  --------------------------------------------------------------------------
//  Handle a command from calling application

static int
s_self_handle_pipe (self_t *self)
{
  //  Get the whole message off the pipe in one go

  msg_t msg;
  receive_one_frame(self->pipe, &msg);

  if (self->verbose)
    zsys_info ("actor %d: API command=%s", self->id, msg.action_id);
  if (msg.action_id == VERBOSE_ID)
    self->verbose = TRUE;
  else if (msg.action_id == LOG_ID){
    fprintf(self->output_file, "%s\n", msg.data);
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

  return 0;
}


//  --------------------------------------------------------------------------

typedef struct{
  int id;
  int verbose_mode;
  FILE * output_file;

}log_actor_args_t;

void log_actor_fn(zsock_t *pipe, void *void_args)
{
  log_actor_args_t * args = (log_actor_args_t*)void_args;
  self_t *self = s_self_new (pipe, args->id, args->output_file, args->verbose_mode);
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

zactor_t *log_actor_new( int id, int verbose_mode, FILE * output_file){
  log_actor_args_t args;
  args.id = id;
  args.verbose_mode = verbose_mode;
  args.output_file = output_file;
  return zactor_new(log_actor_fn, &args);    
}

void log_actor_make_log(zactor_t *self, const char data[256]){
  msg_t msg;
  msg.action_id = LOG_ID;
  strcpy(msg.data, data);
  send_one_frame(zactor_sock(self), &msg, sizeof(msg_t));
}

void log_actor_destroy(zactor_t *self){
  msg_t msg;
  msg.action_id = TERM_ID;
  send_one_frame(self, &msg, sizeof(msg_t));
  if(errno == -1)
    return;
  zactor_destroy(&self);
  errno = 0;
}
