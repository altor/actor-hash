#ifndef msg_h
#define msg_h

#include <czmq.h>

//Action id
#define VERBOSE_ID 0
#define TERM_ID 1
#define LOG_ID 2
#define ENCODE_ID 3
#define GEO_ID 4
#define SIM_ID 5

/** 
 * a simple struct for serialize message as couple of action id and data
 */
typedef struct{
  char action_id;
  char data[256];
}msg_t;

#endif
