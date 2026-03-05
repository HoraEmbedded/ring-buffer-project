#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <stdio.h>
#define BUFFER_SIZE 10

typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} RingBuffer;

void init_buffer(RingBuffer *rb);
void write_buffer(RingBuffer *rb, int value);
int read_buffer(RingBuffer *rb);
void display_buffer(RingBuffer *rb);
#endif // RING_BUFFER_H