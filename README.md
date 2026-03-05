# Ring Buffer Simulator

A lightweight, fully functional **circular buffer (ring buffer)** implementation in C, designed to simulate real-world embedded systems data queues.

---

## Table of Contents

- [Overview](#overview)
- [Architecture](#architecture)
- [API Reference](#api-reference)
- [Getting Started](#getting-started)
- [Usage Example](#usage-example)
- [Sample Output](#sample-output)
- [Configuration](#configuration)
- [Concepts & Design Decisions](#concepts--design-decisions)
- [Author](#author)

---

## Overview

A **ring buffer** is a fixed-size, circular data structure that operates on the **FIFO** (First In, First Out) principle. It is one of the most widely used data structures in embedded systems engineering — found in UART drivers, audio processing pipelines, CAN bus communication stacks, and real-time operating systems.

This project implements a ring buffer from scratch in C, including:
- Safe write and read operations with boundary protection
- Visual state display for debugging and simulation
- Clean memory initialization to prevent undefined behavior

---

## Architecture

```
  Index:  [  0  ][  1  ][  2  ][  3  ][  4  ][  5  ][  6  ][  7  ][  8  ][  9  ]
  Data:   [ 10  ][ 20  ][ 30  ][  _  ][  _  ][  _  ][  _  ][  _  ][  _  ][  _  ]
             ↑                    ↑
           TAIL                  HEAD

  TAIL  →  next read position
  HEAD  →  next write position
  COUNT →  number of elements currently stored
```

**Wrap-around behavior:**
When `HEAD` or `TAIL` reaches the end of the buffer, it wraps back to index `0` using modulo arithmetic:

```c
head = (head + 1) % BUFFER_SIZE;
```

**State conditions:**

| Condition | Indicator |
|-----------|-----------|
| Buffer empty | `count == 0` |
| Buffer full | `count == BUFFER_SIZE` |

---

## API Reference

### `void init_buffer(RingBuffer *rb)`
Initializes the ring buffer. Sets `head`, `tail`, and `count` to `0` and clears all slots.

| Parameter | Type | Description |
|-----------|------|-------------|
| `rb` | `RingBuffer *` | Pointer to the buffer instance |

---

### `void write_buffer(RingBuffer *rb, int value)`
Writes a value into the buffer at the current `head` position. Prints an error and rejects the write if the buffer is full.

| Parameter | Type | Description |
|-----------|------|-------------|
| `rb` | `RingBuffer *` | Pointer to the buffer instance |
| `value` | `int` | Value to write |

---

### `int read_buffer(RingBuffer *rb)`
Reads and removes the value at the current `tail` position. Returns `-1` if the buffer is empty.

| Parameter | Type | Description |
|-----------|------|-------------|
| `rb` | `RingBuffer *` | Pointer to the buffer instance |

| Return Value | Meaning |
|---|---|
| `int` | The value read from the buffer |
| `-1` | Buffer was empty — no data available |

---

### `void display_buffer(RingBuffer *rb)`
Prints the current state of the buffer to stdout, including all slot values and the positions of `HEAD` and `TAIL`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `rb` | `RingBuffer *` | Pointer to the buffer instance |

---

## Getting Started

### Prerequisites

- GCC compiler (`gcc --version` to verify)
- Git (optional, for cloning)

### Build & Run

```bash
# Clone the repository
git clone https://github.com/HoraEmbedded/ring-buffer-project.git
cd ring-buffer-project

# Compile
gcc ring_buffer.c -o ring_buffer

# Run
./ring_buffer          # Linux / macOS
ring_buffer.exe        # Windows
```

---

## Usage Example

```c
int main() {
    RingBuffer rb;

    init_buffer(&rb);         // Initialize

    write_buffer(&rb, 10);    // Write data
    write_buffer(&rb, 20);
    write_buffer(&rb, 30);

    display_buffer(&rb);      // Visualize state

    read_buffer(&rb);         // Read data
    read_buffer(&rb);

    display_buffer(&rb);      // Visualize updated state

    return 0;
}
```

---

## Sample Output

```
=== Ring Buffer State ===
Head: 3 | Tail: 0 | Count: 3
[ 10] [ 20] [ 30] [  0] [  0] [  0] [  0] [  0] [  0] [  0]
  T               H

Read value: 10
Read value: 20

=== Ring Buffer State ===
Head: 3 | Tail: 2 | Count: 1
[ 10] [ 20] [ 30] [  0] [  0] [  0] [  0] [  0] [  0] [  0]
               T   H
```

---

## Configuration

Buffer size is defined as a compile-time constant at the top of `ring_buffer.c`:

```c
#define BUFFER_SIZE 10
```

Change this value to resize the buffer. All logic automatically adapts — no hardcoded values anywhere in the codebase.

---

## Concepts & Design Decisions

**Why pointers?**
All functions receive a `RingBuffer *` pointer rather than a copy of the struct. This ensures functions modify the original buffer in memory, not a temporary local copy — critical for correctness in embedded environments.

**Why modulo for wrap-around?**
The expression `(index + 1) % BUFFER_SIZE` provides a branchless, safe way to wrap indices around the buffer boundary — efficient and clean.

**Why `-1` as error return?**
Since the buffer stores non-negative integers in this implementation, `-1` serves as a sentinel value signaling an empty-read error — a common convention in C embedded libraries.

**Why a separate `count` field?**
Tracking element count independently avoids the classic ambiguity between full and empty states when `head == tail`, without sacrificing a buffer slot.

---

## Author

**HoraEmbedded** — Electronics and Automation Systems Engineering Student

---
