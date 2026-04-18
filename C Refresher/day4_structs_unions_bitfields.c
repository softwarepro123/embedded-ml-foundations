/* ============================================================
 * day4_structs_unions_bitfields.c
 * ------------------------------------------------------------
 * Day 4 of the 14-Day C Refresher Challenge
 * Topic: Structs (for hardware registers), unions (for dual
 *        views of the same memory), and bit fields (for
 *        packed configuration values).
 *
 * Author: Eric Johnson (github.com/softwarepro123)
 *         Code generated with AI assistance, hand-copied,
 *         compiled with -Wall, and hand-debugged.
 *
 * Compile: gcc day4_structs_unions_bitfields.c -o day4_structs_unions_bitfields.exe -Wall
 * Run:     .\day4_structs_unions_bitfields.exe
 * ============================================================ */

#include <stdio.h>
#include <stdint.h>

/* ============================================================
 * Exercise 1: UART register block as a struct.
 * Each field maps to a hardware register at a specific offset.
 * volatile is MANDATORY on every hardware register — it stops
 * the compiler from optimizing reads and writes away.
 * ============================================================ */
typedef struct {
    volatile uint32_t CR;    /* 0x00: Control register      */
    volatile uint32_t SR;    /* 0x04: Status register       */
    volatile uint32_t DR;    /* 0x08: Data register         */
    volatile uint32_t BRR;   /* 0x0C: Baud rate register    */
} UART_TypeDef;

/* ============================================================
 * Exercise 3: Union for dual-view register access.
 * Same 32 bits, two views: one word OR four bytes.
 * This is exactly how byte-swapping gets implemented.
 * ============================================================ */
typedef union {
    uint32_t word;           /* all 32 bits at once          */
    uint8_t  bytes[4];       /* same storage, byte-indexed   */
} Register32_t;

/* ============================================================
 * Exercise 4: Bit fields packed into one byte.
 * 1 + 3 + 4 = 8 bits total — fits in a single uint8_t.
 * sizeof(ConfigReg_t) should equal 1.
 * ============================================================ */
typedef struct {
    uint8_t enable    : 1;   /* 1 bit:  0 or 1   */
    uint8_t mode      : 3;   /* 3 bits: 0-7      */
    uint8_t prescaler : 4;   /* 4 bits: 0-15     */
} ConfigReg_t;

/* ============================================================
 * Exercise 5: Function takes a struct POINTER.
 * Always pass structs by pointer, never by value — the caller
 * sees the modifications and no expensive copy is made.
 * ============================================================ */
void uart_configure(UART_TypeDef *uart, uint32_t baud_divisor) {
    uart->CR  = 0x0000000DU;      /* enable UART + TX + RX (bits 0, 2, 3) */
    uart->BRR = baud_divisor;     /* set baud rate                        */
}

int main(void) {
    /* -------- Exercises 1, 2, 5: simulated UART register block -------- *
     * On real hardware this would be:
     *     UART_TypeDef *uart = (UART_TypeDef *)0x40004400;
     * On the PC we simulate with a real struct instance.
     * ------------------------------------------------------------------ */
    UART_TypeDef fake_uart = {0};
    UART_TypeDef *uart = &fake_uart;

    uart_configure(uart, 0x683);   /* 0x683 approximates 115200 baud @ 16MHz */
    printf("UART CR  = 0x%08X\n", uart->CR);
    printf("UART BRR = 0x%08X\n", uart->BRR);

    /* -------- Exercise 3: union in action -------- */
    Register32_t r;
    r.word = 0xDEADBEEF;
    printf("\nUnion view of 0xDEADBEEF:\n");
    printf("  as word:  0x%08X\n", r.word);
    printf("  as bytes: 0x%02X 0x%02X 0x%02X 0x%02X\n",
           r.bytes[0], r.bytes[1], r.bytes[2], r.bytes[3]);
    /* Byte order reveals endianness live.
     * x86 / x64 Windows is little-endian, so you'll see: EF BE AD DE
     * (least-significant byte at the lowest address). */

    /* -------- Exercise 4: bit field struct -------- */
    ConfigReg_t cfg = {0};
    cfg.enable    = 1;
    cfg.mode      = 5;    /* binary 101 */
    cfg.prescaler = 12;   /* binary 1100 */

    printf("\nConfigReg: enable=%u mode=%u prescaler=%u\n",
           cfg.enable, cfg.mode, cfg.prescaler);
    printf("sizeof(ConfigReg_t) = %zu byte(s)\n", sizeof(ConfigReg_t));
    /* Should print 1. All three fields pack into a single byte. */

    return 0;
}
