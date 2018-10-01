#ifndef actor_log_h
#define actor_log_h

#include "../hash/geohash.h"
/**
 * structure used to send a msg to a geohash actor
 */
typedef struct{
  char action_id;
  coordinate_t coordinate;
}geohash_msg_t;

/**
 * create a geohash actor
 */
zactor_t * geohash_actor_new(int id, int verbose_mode, zactor_t * log_actor);

/**
 * encode longitude and latitude coordinates
 * @errno 0 if the message was write succefully
 *        -1 if the message couldn't be delivered to the actor
 */
void geohash_actor_encode(zactor_t * self, double longitude, double latitude);

/**
 * destroy a geohash actor
 * @errno 0 if the geohash actor was destroy succefully
 *        -1 if the termination message couldn't be delivered to the actor
 */
void geohash_actor_destroy(zactor_t *self);

#endif
