#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {uint8_t * buffer;
                uint8_t head;
                uint8_t tail;
                uint8_t max_index;
               } queue_t;

void init_queue(queue_t * ptr_to_queue, int max_items);
bool pop(queue_t *q0, uint8_t *data);
bool push(queue_t *q0, uint8_t data);

   
#endif // QUEUE_H_