/* ============================================================
 * day3_arrays_memory.c
 * ------------------------------------------------------------
 * Day 3 of the 14-Day C Refresher Challenge
 * Topic: Arrays, strings, memory layout, memcpy/memset from
 *        scratch, and a circular ring buffer.
 *
 * Author: Eric Johnson (github.com/softwarepro123)
 *         Code generated with AI assistance, hand-copied,
 *         compiled with -Wall, and hand-debugged.
 *
 * Compile: gcc day3_arrays_memory.c -o day3_arrays_memory.exe -Wall
 * Run:     .\day3_arrays_memory.exe
 * ============================================================ */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>     /* for size_t */

#define BUFFER_SIZE 8   /* small size so wrap-around is easy to see */

/* ============================================================
 * memcpy from scratch. Standard library has one, but every
 * embedded engineer should be able to write this in their
 * sleep. Critical on small systems that don't link libc.
 * ============================================================ */
void *my_memcpy(void *dest, const void *src, size_t n) {
    uint8_t       *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

/* ============================================================
 * memset from scratch. Same reasoning as memcpy.
 * ============================================================ */
void *my_memset(void *dest, int value, size_t n) {
    uint8_t *d = (uint8_t *)dest;
    for (size_t i = 0; i < n; i++) {
        d[i] = (uint8_t)value;
    }
    return dest;
}

/* ============================================================
 * Ring buffer — the most common data structure in embedded
 * firmware. Used for UART RX/TX queues, event queues,
 * inter-task communication, and more.
 *
 * head and tail are declared volatile because in real firmware,
 * one is modified by an ISR and the other by the main loop.
 * ============================================================ */
typedef struct {
    uint8_t           data[BUFFER_SIZE];
    volatile uint32_t head;   /* write index — advanced by producer */
    volatile uint32_t tail;   /* read index  — advanced by consumer */
} RingBuffer_t;

/* Returns 0 on success, -1 if the buffer is full. */
int rb_write(RingBuffer_t *rb, uint8_t byte) {
    uint32_t next_head = (rb->head + 1) % BUFFER_SIZE;
    if (next_head == rb->tail) {
        return -1;   /* full */
    }
    rb->data[rb->head] = byte;
    rb->head = next_head;
    return 0;
}

/* Returns 0 on success (byte written to *out), -1 if empty. */
int rb_read(RingBuffer_t *rb, uint8_t *out) {
    if (rb->head == rb->tail) {
        return -1;   /* empty */
    }
    *out = rb->data[rb->tail];
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    return 0;
}

int rb_is_empty(const RingBuffer_t *rb) {
    return rb->head == rb->tail;
}

int main(void) {
    /* -------- Array iteration: index vs pointer -------- */
    int arr[5] = {10, 20, 30, 40, 50};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    printf("=== Array Iteration ===\n");
    printf("By index:   ");
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nBy pointer: ");
    for (int *p = arr; p < arr + n; p++) {
        printf("%d ", *p);
    }
    printf("\n");

    /* -------- char arr[] vs char *ptr -------- *
     * char arr[] — an array on the stack, writable.
     * char *ptr  — a pointer to a string literal in ROM.
     *              Writing to *ptr is undefined behavior.
     * ---------------------------------------------------- */
    char writable[] = "Hello";     /* copy on the stack (RAM)      */
    const char *readonly = "World"; /* points into ROM / text seg  */
    writable[0] = 'J';              /* OK                           */
    /* readonly[0] = 'Z';  <- would crash or be UB on real hardware */
    printf("\n=== Arrays vs String Pointers ===\n");
    printf("writable (RAM, modified): %s\n", writable);
    printf("readonly (ROM):           %s\n", readonly);

    /* -------- my_memcpy / my_memset -------- */
    uint8_t src[8]  = {1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t dst[8]  = {0};
    my_memcpy(dst, src, sizeof(src));

    printf("\n=== my_memcpy ===\n");
    printf("src: ");
    for (size_t i = 0; i < 8; i++) printf("%u ", src[i]);
    printf("\ndst: ");
    for (size_t i = 0; i < 8; i++) printf("%u ", dst[i]);
    printf("\n");

    my_memset(dst, 0xAA, sizeof(dst));
    printf("\n=== my_memset (to 0xAA) ===\n");
    printf("dst: ");
    for (size_t i = 0; i < 8; i++) printf("0x%02X ", dst[i]);
    printf("\n");

    /* -------- Ring buffer demo -------- */
    RingBuffer_t rb = {0};
    printf("\n=== Ring Buffer Test ===\n");
    printf("Buffer size: %d\n", BUFFER_SIZE);

    /* Write 5 bytes */
    for (uint8_t i = 1; i <= 5; i++) {
        rb_write(&rb, i * 10);
    }
    printf("Wrote: 10 20 30 40 50\n");

    /* Read 3 bytes */
    printf("Read:  ");
    for (int i = 0; i < 3; i++) {
        uint8_t v;
        rb_read(&rb, &v);
        printf("%u ", v);
    }
    printf("\n");

    /* Write 5 more to exercise wrap-around */
    for (uint8_t i = 6; i <= 10; i++) {
        rb_write(&rb, i * 10);
    }
    printf("Wrote: 60 70 80 90 100 (wraps around)\n");

    /* Drain everything remaining */
    printf("Drain: ");
    while (!rb_is_empty(&rb)) {
        uint8_t v;
        rb_read(&rb, &v);
        printf("%u ", v);
    }
    printf("\n");

    printf("\nRing buffer proved:\n");
    printf("  - FIFO ordering preserved across wrap-around\n");
    printf("  - head/tail indices correctly modulo BUFFER_SIZE\n");
    printf("  - empty detection works (head == tail)\n");

    return 0;
}
