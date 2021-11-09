#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {int16_t * buffer;
                uint16_t head;
                uint16_t tail;
                uint16_t max_index;
               } queue_t;

void init_queue(queue_t * ptr_to_queue, int max_items);
bool read_q(queue_t *q0, int16_t *datum);
bool write_q(queue_t *q0, int16_t datum);

   
#endif // QUEUE_H_
