#ifndef actor_log_h
#define actor_log_h

#include <stdio.h>

/**
 * create a log actor
 */
zactor_t *log_actor_new( int id, int verbose_mode, FILE * output_file);

/**
 * log a message in the log actor [actor]
 * @errno 0 if the message was write succefully
 *        -1 if the message couldn't be delivered to the actor
 */
void log_actor_make_log(zactor_t *actor, const char data[256]);

/**
 * destroy a log actor
 * @errno 0 if the log actor was destroy succefully
 *        -1 if the termination message couldn't be delivered to the actor
 */
void log_actor_destroy(zactor_t *self);

#endif
