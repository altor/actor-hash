#include <stdlib.h>
#include <math.h>
#include <errno.h>


#include "utils.h"

char utils_extract_bit_n(int x, int n){
  return (x & (int)pow(2, n)) >> n;
}


// return the base 32 representation of a base 10 digit
char digit_to_b32(unsigned int n){
  if(n < 10)
    return n + 48;
  else if(n < 17)
    return n + 88;
  else if (n < 19)
    return n + 89;
  else if (n < 21)
    return n + 90;
  else 
    return n + 91;
}

void utils_to_b32(unsigned int n, buffer_t * buffer){

  int current_bit = 0;
  while(n != 0){
    unsigned int q = n / 32;
    unsigned int r = n - (q * 32);

    buffer_set(buffer, current_bit, digit_to_b32(r));
    if(errno == -1)
      return;

    current_bit += 1;
    n = q;
    
  }

  int nb_bit = current_bit;
  buffer_set(buffer, nb_bit, 0);
  if(errno == -1)
    return;
  

  // reverse the buffer
  for(int j = 0; j < nb_bit / 2;j++){
    char a = buffer_get(buffer, j);
    char b = buffer_get(buffer, nb_bit - j - 1);
    buffer_set(buffer, j, b);
    if(errno == -1)
      return;
    buffer_set(buffer, nb_bit - j - 1, a);
    if(errno == -1)
      return;
  }
  errno = 0;
}
