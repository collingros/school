/*	collin gros
	11-04-2020
	cs474
	proj2

	this code was retrieved from:
		https://stackoverflow.com/questions/827691/how-do-you-
			implement-a-circular-buffer-in-c

	and is used by main.c for the circular buffer.	*/

#include <string.h>
#include <stdlib.h>


typedef struct circular_buffer
{
    void *buffer;     // data buffer
    void *buffer_end; // end of data buffer
    size_t capacity;  // maximum number of items in the buffer
    size_t count;     // number of items in the buffer
    size_t sz;        // size of each item in the buffer
    void *head;       // pointer to head
    void *tail;       // pointer to tail
} circular_buffer;

void cb_init(circular_buffer *cb, size_t capacity, size_t sz);

void cb_free(circular_buffer *cb);

void cb_push_back(circular_buffer *cb, const void *item);

void cb_pop_front(circular_buffer *cb, void *item);


