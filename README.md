# Ring Buffer Simulator

A lightweight, fully functional **circular buffer (ring buffer)** implementation in C, structured following professional embedded systems engineering conventions — with separated header, source, and driver files.

---

## Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [Architecture](#architecture)
- [API Reference](#api-reference)
- [Getting Started](#getting-started)
- [Usage Example](#usage-example)
- [Sample Output](#sample-output)
- [Configuration](#configuration)
- [Concepts & Design Decisions](#concepts--design-decisions)
- [Roadmap](#roadmap)
- [Author](#author)

---

## Overview

A **ring buffer** is a fixed-size, circular data structure that operates on the **FIFO** (First In, First Out) principle. It is one of the most widely used data structures in embedded systems engineering — found in UART drivers, audio processing pipelines, CAN bus communication stacks, and real-time operating systems.

This project implements a ring buffer from scratch in C, including:
- Safe write and read operations with boundary protection
- Visual state display for debugging and simulation
- Clean memory initialization to prevent undefined behavior
- Professional file separation: header, source, and main driver

---

## Project Structure

```
ring-buffer-simulator/
│
├── ring_buffer.h       # Public interface — struct definition & function declarations
├── ring_buffer.c       # Implementation — all function bodies
└── main.c              # Driver — demonstrates and tests the ring buffer
```

> **Design principle:** `ring_buffer.h` is the only file a consumer of this library needs.
> Internal implementation details are fully encapsulated in `ring_buffer.c`.

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

All declarations are in `ring_buffer.h`. Include it to access the full API:

```c
#include "ring_buffer.h"
```

---

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
git clone https://github.com/HoraEmbedded/ring-buffer-simulator.git
cd ring-buffer-simulator

# Compile all source files together
gcc main.c ring_buffer.c -o ring_buffer

# Run
./ring_buffer          # Linux / macOS
ring_buffer.exe        # Windows
```

> **Note:** Never compile `ring_buffer.h` directly — it is included automatically by the compiler when processing `main.c` and `ring_buffer.c`.

---

## Usage Example

```c
#include "ring_buffer.h"

int main() {
    RingBuffer rb;

    init_buffer(&rb);           // Initialize

    write_buffer(&rb, 10);      // Write data
    write_buffer(&rb, 20);
    write_buffer(&rb, 30);

    display_buffer(&rb);        // Visualize state

    read_buffer(&rb);           // Read data
    display_buffer(&rb);        // Visualize updated state

    return 0;
}
```

---

## Sample Output

```
=== Ring Buffer State ===
Head: 3, Tail: 0, Count: 3
[ 10] [ 20] [ 30] [  0] [  0] [  0] [  0] [  0] [  0] [  0]
  T               H

Read value: 10

=== Ring Buffer State ===
Head: 3, Tail: 1, Count: 2
[ 20] [ 30] [  0] [  0] [  0] [  0] [  0] [  0] [  0] [ 10]
       T         H
```

---

## Configuration

Buffer size is defined as a compile-time constant in `ring_buffer.h`:

```c
#define BUFFER_SIZE 10
```

Change this single value to resize the buffer. All logic in `ring_buffer.c` and `main.c` automatically adapts — no hardcoded values anywhere in the codebase.

---

## Concepts & Design Decisions

**Why separate `.h` and `.c` files?**
Separating interface from implementation is a fundamental principle of embedded software architecture. `ring_buffer.h` acts as a public contract — any consumer of this library only needs this file. `ring_buffer.c` remains an internal detail, free to change without affecting external code.

**Why pointers?**
All functions receive a `RingBuffer *` pointer rather than a copy of the struct. This ensures functions modify the original buffer in memory, not a temporary local copy — critical for correctness in embedded environments where memory is constrained.

**Why modulo for wrap-around?**
The expression `(index + 1) % BUFFER_SIZE` provides a branchless, safe way to wrap indices around the buffer boundary — efficient and clean.

**Why `-1` as error return?**
Since the buffer stores non-negative integers in this implementation, `-1` serves as a sentinel value signaling an empty-read error — a common convention in C embedded libraries.

**Why a separate `count` field?**
Tracking element count independently avoids the classic ambiguity between full and empty states when `head == tail`, without sacrificing a buffer slot.

---

## Roadmap

- [x] Phase 1 — Core ring buffer implementation in C
- [x] Phase 2 — Professional file separation (`.h` / `.c` / `main.c`)
- [ ] Phase 3 — Interrupt simulation with producer/consumer threads
- [ ] Phase 4 — Port to STM32 microcontroller (hardware)

---

## Author

**HoraEmbedded** — Electronics and Automation Systems Engineering Student

---

## License

This project is open source and available under the [MIT License](LICENSE).