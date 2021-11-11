// Not sure if this is old code from algorithms and design or example code by Dr. Carroll from embedded systems,
// but its on my computer and looks like it should work.
// 



#include "queue.h"

void init_queue(queue_t * ptr_to_queue, int max_items)
{
  int16_t * new_buff = (int16_t *const) malloc((max_items+1) * sizeof(int16_t));
  ptr_to_queue ->buffer = new_buff;
  ptr_to_queue ->head = 0;
  ptr_to_queue ->tail = 0;
  ptr_to_queue ->max_index = max_items;
}

bool pop(queue_t *q0 int16_t *data)
{
  if(q0->head == q0->tail)
  { // if empty
      *data = 0;
      success = false; //{datum==0,success == false}
  }
  else{
         *data = (q0->buffer)[q0->head];  // acquire data @(buffer[head])
         q0->head++;                      // move head to next location
         if ((q0->head) > q0->max_index) q0->head=0;  // loop back around if exceeding max index
         success = true;
    }
}

bool push(queue_t *q0, int16_t *data)
{
  uint16_t new_tail = q0->tail + 1;
  if (new_tail > q0->max_index) {new_tail = 0}; // loop back around if going past max index
  if (new_tail == q0->head) {return false}; //queue full = error
  else{
      (q0->buffer)[q0->tail] = data;  // access as (ptr)[int] see read_q
      q0->tail = new_tail;
  }
    return true;
  
}


