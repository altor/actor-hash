#include <math.h>
#include <errno.h>

#include "geohash.h"
#include "../utils/utils.h"



// UTILITARIES FUNCTION //

// divide the interval [min - max] until an interval matching the precision is
// finding. return the binary codes that encode this interval
int gen_bin_code(double coordinate, int nb_bit, double min, double max){

  if(nb_bit == 0)
    return 0;
  else{
    double mean = (min + max) / 2;

    if(coordinate > mean)
      return pow(2, nb_bit - 1) + gen_bin_code(coordinate, nb_bit - 1, mean, max);
    else
      return gen_bin_code(coordinate, nb_bit - 1, min, mean);
  }
}

// aggregate the two coordinate bin code into one bin code, using latitude bits
// for odd bits and longitude bits for even bits. The final bin code is has
// nb_bit bit
unsigned int aggregate_bin_code_aux(unsigned int latitude_bin_code, unsigned int longitude_bin_code, int nb_bit, int use_longitude){

  if (nb_bit == 0)
    return 0;

  char bit = utils_extract_bit_n( use_longitude ? longitude_bin_code : latitude_bin_code, (nb_bit - 1) / 2 );
  return bit * pow(2 , nb_bit - 1) + aggregate_bin_code_aux(latitude_bin_code, longitude_bin_code, nb_bit - 1, !use_longitude);
}

unsigned int aggregate_bin_code(unsigned int latitude_bin_code, unsigned int longitude_bin_code, int nb_bit){
  return aggregate_bin_code_aux(latitude_bin_code, longitude_bin_code, nb_bit, TRUE);
}


// PUBLIC FONCTION //

void geohash_encode(coordinate_t coordinate, int nb_char, buffer_t * buffer){

  int nb_bit = nb_char * 5;
  int nb_latitude_bit = nb_bit / 2;
  int nb_longitude_bit = nb_bit / 2 + nb_bit % 2;
  
  if(coordinate.latitude > 90 || coordinate.latitude < -90){
    errno = -1;
    return;
  }

  if(coordinate.longitude > 180 || coordinate.longitude < -180){
    errno = -1;
    return;
  }

  unsigned int latitude_bin_code  = gen_bin_code(coordinate.latitude, nb_latitude_bit, -90, 90);
  unsigned int longitude_bin_code  = gen_bin_code(coordinate.longitude, nb_longitude_bit, -180, 180);

  unsigned int bin_code = aggregate_bin_code(latitude_bin_code, longitude_bin_code, nb_bit);
  utils_to_b32(bin_code, buffer);
  
  if(errno == -1){
    errno = -2;
    return;
  } else{
    errno = 0;
    return;
  }
  
}

void geohash_decode(char * geohash, int nb_char, coordinate_t * coordinate){
  return;
}
