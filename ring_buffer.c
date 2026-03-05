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

void display_buffer(RingBuffer *rb) {
    printf("=== Ring Buffer State ===\n");
    printf("Head: %d, Tail: %d, Count: %d\n", rb->head, rb->tail, rb->count);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        int index = (rb->tail + i) % BUFFER_SIZE;
        printf("[%2d] ", rb->buffer[index]);
    }
    printf("\n");

    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i == rb->head && i == rb->tail) {
            printf(" H/T ");
        } else if (i == rb->head) {
            printf(" H   ");
        } else if (i == rb->tail) {
            printf(" T   ");
        } else {
            printf("     ");
        }
    }
    printf("\n");
}

int main() {
    RingBuffer rb;
    init_buffer(&rb);

    printf("Ring buffer initialized. Head: %d, Tail: %d, Count: %d\n \n", rb.head, rb.tail, rb.count);

    display_buffer(&rb);

    write_buffer(&rb, 5);
    write_buffer(&rb, 10);
    write_buffer(&rb, 15);
    printf("After writing values. Head: %d, Tail: %d, Count: %d\n \n", rb.head, rb.tail, rb.count);
    display_buffer(&rb);

    read_buffer(&rb);
    read_buffer(&rb);   
    printf("After reading values. Head: %d, Tail: %d, Count: %d\n  \n", rb.head, rb.tail, rb.count);
    display_buffer(&rb);

    read_buffer(&rb);
    read_buffer(&rb); // Attempt to read from an empty buffer
    read_buffer(&rb); // Attempt to read from an empty buffer
    printf("After attempting to read from an empty buffer. Head: %d, Tail: %d, Count: %d\n", rb.head, rb.tail, rb.count);
    display_buffer(&rb);    
    return 0;
}