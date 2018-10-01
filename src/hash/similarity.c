#include <openssl/md5.h>
#include <math.h>

#include "similarity.h"
#include "../utils/utils.h"


#define HASH_SIZE 16 //hash size in byte
#define NB_CHUNK 32

// UTILITARIES FUNCTION //
void update_bit_array(char * chunk_hash, int bit_array[HASH_SIZE * 8]){
  for(int i = 0; i < HASH_SIZE; i++){
    for(int j = 0; j < 8; j++){
      if(utils_extract_bit_n(chunk_hash[i], j) == 1)
	bit_array[i*8 + j] += 1;
      else
	bit_array[i*8 + j] -= 1;
    }
  }
}

void extract_bit_array(char * data, int size, int bit_array[HASH_SIZE * 8], int chunk_size){
  int chunk_begining = 0;

  for(int current_bit = 0; current_bit < size; current_bit++){
    if(current_bit % chunk_size == 0 || current_bit == size){

      char chunk_hash[16];
      MD5(data + chunk_begining, current_bit - chunk_begining, chunk_hash);
      update_bit_array(chunk_hash, bit_array);
      chunk_begining = current_bit;
    }
  }
}


// PUBLIC FONCTION //
void similarity_encode(void * data, int size, buffer_t * buffer){

  int nb_chunk = size < NB_CHUNK ? size : NB_CHUNK;
  
  int chunk_size = size / nb_chunk; // number of bytes per chunk
  printf("toto%d\n", chunk_size);
  int bit_array[HASH_SIZE * 8];

  //bit array initialisation
  for(int i = 0; i < HASH_SIZE * 8; i ++)
    bit_array[i] = 0;

  //bit array creation
  extract_bit_array((char *)data, size, bit_array, chunk_size);

  //write similarity hash in buffer
  for(int i = 0; i < HASH_SIZE; i ++){
    char c = 0;

    for(int j = 0; j < 8; j++){
      if(bit_array[i*8 + j] > 0)
	c += pow(2, j);
    }
    buffer_set(buffer, i, c);
  }
  
  return;
}
