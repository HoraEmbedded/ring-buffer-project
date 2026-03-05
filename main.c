#include "ring_buffer.h"
int main() {
    RingBuffer rb;
    init_buffer(&rb);

    write_buffer(&rb, 10);
    write_buffer(&rb, 20);
    write_buffer(&rb, 30);
    display_buffer(&rb);

    read_buffer(&rb);
    display_buffer(&rb);

    write_buffer(&rb, 40);
    write_buffer(&rb, 50);
    display_buffer(&rb);

    return 0;
}

