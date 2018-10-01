#ifndef geohash_h
#define geohash_h

#include "../utils/buffer.h"

typedef struct {
  double latitude;
  double longitude;
} coordinate_t;

/**
 * encode geographical coordinates into a geohash format
 *
 * @param coordinate : longitude and latitude that going to be encode
 * @param precision : number of bit used to encode each coordinate
 * @param buffer : pointer to the buffer that going to store the geohash
 *                 representation
 *
 * @errno 0 if the hash was writen correctly in the buffer, 
 *        -1 if the given coordinate are not in a right format
 *        -2 if the buffer size is too small
 */ 

void geohash_encode(coordinate_t coordinate, int precision, buffer_t * buffer);

/* /\** */
/*  * decode a geohash into geographical coordinates */
/*  * */
/*  * @param geohash : geohash that going to be decode */
/*  * @param precision : number of bit used to encode each coordinate */
/*  * @param memory zone where longitude and latitude of the given geohash is going */
/*  *        to be write */
/*  *\/  */

/* void geohash_decode(char * geohash, int precision, coordinate_t * coordinate); */

#endif

