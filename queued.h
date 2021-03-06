#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {uint16_t * buffer;
                uint16_t head;
                uint16_t tail;
                uint16_t max_index;
               } queue_t;

void init_queue(queue_t * ptr_to_queue, int max_items);
bool pop(queue_t *q0, uint16_t *data);
bool push(queue_t *q0, uint16_t data);

   
#endif // QUEUE_H_