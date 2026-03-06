#include "ring_buffer.h"
#include <assert.h>

void test_init() {
    RingBuffer rb;
    init_buffer(&rb);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        assert(rb.buffer[i] == 0);
    }
    assert(rb.count == 0);
    assert(rb.head == 0);
    assert(rb.tail == 0);
}

void test_write_and_read() {
    RingBuffer rb;
    init_buffer(&rb);
    
    write_buffer(&rb, 1);
    write_buffer(&rb, 2);
    write_buffer(&rb, 3);
    
    assert(read_buffer(&rb) == 1);
    assert(read_buffer(&rb) == 2);
    
    write_buffer(&rb, 4);
    write_buffer(&rb, 5);
    
    assert(read_buffer(&rb) == 3);
    assert(read_buffer(&rb) == 4);
    assert(read_buffer(&rb) == 5);
}

void test_full() {
    RingBuffer rb;
    init_buffer(&rb);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        write_buffer(&rb, i + 1);
    }
    // Buffer should be full now
    write_buffer(&rb, 11); // Should indicate full

    for (int i = 0; i < BUFFER_SIZE; i++) {
        assert(read_buffer(&rb) == i + 1);
    }
    
    // Buffer should be empty now
    assert(read_buffer(&rb) == -1); // Should indicate empty
}   

int main() {
    test_init();
    printf("Initialization test passed!\n");

    test_write_and_read();
    printf("Write and read test passed!\n");
    
    test_full();
    printf("Full buffer test passed!\n");
    
    printf("All tests passed!\n");
    return 0;
}