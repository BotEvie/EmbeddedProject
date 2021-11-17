// Not sure if this is old code from algorithms and design or example code by Dr. Carroll from embedded systems,
// but its on my computer and looks like it should work.
// 

#include "queued.h"

//bool cq_full(queue_t *q0);
bool cq_stuff(queue_t *q0);

void init_queue(queue_t *ptr_to_queue, int max_items)
{
  uint8_t * new_buff = (uint8_t *const) malloc((max_items+1) *sizeof(uint8_t));  
  ptr_to_queue ->buffer = new_buff;
  ptr_to_queue ->head = 0;
  ptr_to_queue ->tail = 0;
  ptr_to_queue ->max_index = max_items;
}

bool pop(queue_t *q0, uint8_t *data)
{
    bool success;
    if(q0->head == q0->tail)  // if empty
    { 
        *data = 0;
        success = false; 
    }
    else{
        *data = (q0->buffer)[q0->head];
        q0->head++;                      // move head to next location
        if ((q0->head) > q0->max_index) {q0->head=0;}  // loop back around if exceeding max index
        success = true;
    }
    return success;
}

bool push(queue_t *q0, uint8_t data)
{
    uint8_t new_tail = q0->tail + 1;
    if (new_tail > q0->max_index) {new_tail = 0; } // loop back around if going past max index
    if (new_tail == q0->head) {return false; } //queue full = error
    else{
        (q0->buffer)[q0->tail] = data;  
        q0->tail = new_tail;
    }
    return true;
  
}

bool cq_stuff(queue_t *q0)
{
  if(q0->head != q0->tail){ return true; }
	else{return false;}
}
/*
bool cq_full(queue_t *q0)
{
  
    if(q0->head == q0->tail)  // if empty
    { 
        return false; 
    }
    else if((q0->head + 1) == q0->tail)
    {
      return true;
    }
		else {return true;}
}
*/

