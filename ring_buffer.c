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

void write_buffer(RingBuffer *rb, int value) {
    if (rb->count < BUFFER_SIZE) {
        rb->buffer[rb->head] = value;
        rb->head = (rb->head + 1) % BUFFER_SIZE;
        rb->count++;
    } else {
        printf("Buffer is full. Cannot write value: %d\n", value);
    }
}

int read_buffer(RingBuffer *rb) {
    if (rb->count > 0) {
        int value = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % BUFFER_SIZE;
        rb->count--;
        printf("Read value: %d\n", value);
        return value;
    } else {
        return -1; // Buffer is empty
    }
}

int main() {
    RingBuffer rb;
    init_buffer(&rb);

    printf("Ring buffer initialized. Head: %d, Tail: %d, Count: %d\n", rb.head, rb.tail, rb.count);

    write_buffer(&rb, 5);
    write_buffer(&rb, 10);
    write_buffer(&rb, 15);
    printf("After writing values. Head: %d, Tail: %d, Count: %d\n", rb.head, rb.tail, rb.count);

    read_buffer(&rb);
    read_buffer(&rb);   
    printf("After reading values. Head: %d, Tail: %d, Count: %d\n", rb.head, rb.tail, rb.count);

    read_buffer(&rb);
    read_buffer(&rb); // Attempt to read from an empty buffer
    read_buffer(&rb); // Attempt to read from an empty buffer
    printf("After attempting to read from an empty buffer. Head: %d, Tail: %d, Count: %d\n", rb.head, rb.tail, rb.count);
    return 0;
}