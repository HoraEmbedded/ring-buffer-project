#include <stdio.h>

#define BUFFER_SIZE 10

typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} RingBuffer;

void init_buffer(RingBuffer *rb) {
        rb->head = 0;
        rb->tail = 0;
        rb->count = 0;
        for (int i = 0; i < BUFFER_SIZE; i++) {
            rb->buffer[i] = 0; // Initialize buffer elements to 0
        }
}

int main() {
    RingBuffer rb;
    init_buffer(&rb);

    printf("Ring buffer initialized. Head: %d, Tail: %d, Count: %d\n", rb.head, rb.tail, rb.count);
    return 0;
}