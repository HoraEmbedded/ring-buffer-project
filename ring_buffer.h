/**@file ring_buffer.h
@brief This header file defines the structure and function prototypes for a ring buffer (circular buffer) implementation in C. The ring buffer allows for efficient storage and retrieval of data in a fixed-size buffer, where the head and tail pointers wrap around when they reach the end of the buffer.
@author HoraEmbedded
@Version 1.0
*/

#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <stdio.h>
#define BUFFER_SIZE 10

/**@brief The RingBuffer structure contains the buffer array, head and tail indices, and a count of the number of elements currently in the buffer.*/
typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} RingBuffer;

/**@brief Initializes the ring buffer by setting head and tail indices to 0, count to 0, and initializing all buffer elements to 0.
 * @param rb A pointer to the RingBuffer structure to be initialized.*/
void init_buffer(RingBuffer *rb);

/**@brief Writes a value to the ring buffer. If the buffer is full, it will print a message indicating that the buffer is full and will not write the value.
 * @param rb A pointer to the RingBuffer structure where the value will be written.
 * @param value The integer value to be written to the buffer.*/
void write_buffer(RingBuffer *rb, int value);

/**@brief Reads a value from the ring buffer. If the buffer is empty, it will print a message indicating that the buffer is empty and will return -1.
 * @param rb A pointer to the RingBuffer structure from which the value will be read.
 * @return The integer value read from the buffer, or -1 if the buffer is empty.*/
int read_buffer(RingBuffer *rb);

/**@brief Displays the contents of the ring buffer.
 * @param rb A pointer to the RingBuffer structure whose contents will be displayed.*/
void display_buffer(RingBuffer *rb);
#endif // RING_BUFFER_H