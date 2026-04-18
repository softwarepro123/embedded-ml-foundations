/* ============================================================
 * day2_pointers.c
 * ------------------------------------------------------------
 * Day 2 of the 14-Day C Refresher Challenge
 * Topic: Pointers, pointer arithmetic, const vs volatile,
 *        and the hardware register access pattern.
 *
 * Author: Eric Johnson (github.com/softwarepro123)
 *         Code generated with AI assistance, hand-copied,
 *         compiled with -Wall, and hand-debugged.
 *
 * Compile: gcc day2_pointers.c -o day2_pointers.exe -Wall
 * Run:     .\day2_pointers.exe
 * ============================================================ */

#include <stdio.h>
#include <stdint.h>

/* ============================================================
 * Swap two integers via pointers — NO temporary variable.
 * This is the classic XOR swap trick. Only works for integers.
 * Real code should use a temp for readability, but knowing
 * this pattern proves you understand pointer semantics.
 * ============================================================ */
void swap_xor(int *a, int *b) {
    if (a == b) return;   /* same address — nothing to swap */
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

/* ============================================================
 * Modify a variable via pointer — demonstrates that changes
 * persist in the caller. This is how you return multiple
 * values or "return" a value through an out-parameter.
 * ============================================================ */
void increment(int *value) {
    (*value)++;
}

int main(void) {
    /* -------- Basic pointer operations -------- */
    int x = 42;
    int *p = &x;          /* p points to x */

    printf("=== Basic Pointer ===\n");
    printf("x            = %d\n",    x);
    printf("&x (address) = %p\n",    (void *)&x);
    printf("p            = %p\n",    (void *)p);
    printf("*p (value)   = %d\n",    *p);

    /* -------- Modify via pointer -------- */
    *p = 99;
    printf("\nAfter *p = 99:\n");
    printf("x = %d  (changed through pointer)\n", x);

    /* -------- Function modifies via pointer -------- */
    increment(&x);
    printf("\nAfter increment(&x):\n");
    printf("x = %d\n", x);

    /* -------- Swap via pointers -------- */
    int a = 10, b = 20;
    printf("\n=== Swap Via Pointers ===\n");
    printf("Before: a=%d b=%d\n", a, b);
    swap_xor(&a, &b);
    printf("After:  a=%d b=%d\n", a, b);

    /* -------- Pointer arithmetic -------- */
    int arr[5] = {100, 200, 300, 400, 500};
    int *ap = arr;        /* points to arr[0] */

    printf("\n=== Pointer Arithmetic ===\n");
    printf("ap[0]  = %d  (address %p)\n", *ap,       (void *)ap);
    ap++;                 /* moves by sizeof(int) = 4 bytes */
    printf("ap+1   = %d  (address %p)\n", *ap,       (void *)ap);
    ap += 2;
    printf("ap+3   = %d  (address %p)\n", *ap,       (void *)ap);
    printf("(incrementing an int* moves it by 4 bytes on this machine)\n");

    /* -------- Hardware register access pattern -------- *
     * On real hardware you would write:
     *     volatile uint32_t *reg = (uint32_t *)0x40020000;
     * On the PC we simulate with a real variable.
     * The volatile keyword tells the compiler:
     *   "never cache this value, never optimize this access away"
     * This is MANDATORY on every hardware register.
     * ---------------------------------------------------- */
    volatile uint32_t simulated_register = 0;
    volatile uint32_t *reg_ptr = &simulated_register;

    printf("\n=== Simulated Register Access ===\n");
    *reg_ptr = 0xDEADBEEF;
    printf("After *reg_ptr = 0xDEADBEEF\n");
    printf("Value at register: 0x%08X\n", *reg_ptr);

    *reg_ptr |= (1U << 5);
    printf("After setting bit 5:  0x%08X\n", *reg_ptr);

    *reg_ptr &= ~(1U << 5);
    printf("After clearing bit 5: 0x%08X\n", *reg_ptr);

    /* -------- const vs volatile vs const volatile -------- *
     * const        — the POINTER cannot modify the value (but the value may
     *                still change through other means). Use for read-only
     *                parameters you promise not to touch.
     *
     * volatile     — the value may change at any time outside the program's
     *                control (hardware register, ISR, another thread).
     *                Forces the compiler to re-read every time.
     *
     * const volatile — read-only hardware status register. You cannot write
     *                  to it, but its value changes on its own. Classic use:
     *                  hardware timer count register, UART status register.
     * ---------------------------------------------------- */
    const int read_only = 7;
    printf("\n=== const Example ===\n");
    printf("const int read_only = %d\n", read_only);
    /* read_only = 8;  <- would be a compile error */

    printf("\n(const volatile example would target a hardware register,\n");
    printf(" e.g. `const volatile uint32_t *status = (uint32_t*)0x40010000;`\n");
    printf(" meaning: read-only status register that can change on its own.)\n");

    return 0;
}
