/* ============================================================
 * day1_basics.c
 * ------------------------------------------------------------
 * Day 1 of the 14-Day C Refresher Challenge
 * Topic: Variables, types, operators, printf format specifiers,
 *        and bitwise register-manipulation macros.
 *
 * Author: Eric Johnson (github.com/softwarepro123)
 *         Code generated with AI assistance, hand-copied,
 *         compiled with -Wall, and hand-debugged.
 *
 * Compile: gcc day1_basics.c -o day1_basics.exe -Wall
 * Run:     .\day1_basics.exe
 * ============================================================ */

#include <stdio.h>
#include <stdint.h>

/* ============================================================
 * Bitwise register-manipulation macros.
 * These are the foundation of embedded firmware — you will
 * type variants of these every single day in real work.
 * ============================================================ */
#define SET_BIT(reg, bit)     ((reg) |=  (1U << (bit)))
#define CLEAR_BIT(reg, bit)   ((reg) &= ~(1U << (bit)))
#define TOGGLE_BIT(reg, bit)  ((reg) ^=  (1U << (bit)))
#define READ_BIT(reg, bit)    (((reg) >> (bit)) & 1U)

int main(void) {
    /* -------- Basic types with printf format specifiers -------- */
    int          signed_val   = -42;
    unsigned int unsigned_val = 100U;
    float        float_val    = 3.14159f;
    char         char_val     = 'E';
    uint32_t     hex_val      = 0x40020000U;   /* a simulated register address */

    printf("=== Basic Types ===\n");
    printf("signed int   (%%d):     %d\n",  signed_val);
    printf("unsigned int (%%u):     %u\n",  unsigned_val);
    printf("float        (%%f):     %f\n",  float_val);
    printf("char         (%%c):     %c\n",  char_val);
    printf("hex lowercase(%%x):     %x\n",  hex_val);
    printf("hex uppercase(%%X):     %X\n",  hex_val);
    printf("hex padded   (%%08X):   0x%08X\n", hex_val);

    /* -------- Arithmetic operators -------- */
    printf("\n=== Arithmetic ===\n");
    printf("7 + 3   = %d\n", 7 + 3);
    printf("7 - 3   = %d\n", 7 - 3);
    printf("7 * 3   = %d\n", 7 * 3);
    printf("7 / 3   = %d  (integer division)\n", 7 / 3);
    printf("7 %% 3   = %d  (modulo — remainder)\n", 7 % 3);

    /* -------- Bitwise operators -------- */
    uint8_t a = 0xF0;    /* 1111 0000 */
    uint8_t b = 0x0F;    /* 0000 1111 */
    printf("\n=== Bitwise Ops on 0xF0 and 0x0F ===\n");
    printf("a & b   = 0x%02X\n",  a & b);   /* AND     */
    printf("a | b   = 0x%02X\n",  a | b);   /* OR      */
    printf("a ^ b   = 0x%02X\n",  a ^ b);   /* XOR     */
    printf("~a      = 0x%02X\n",  (uint8_t)~a); /* NOT */
    printf("a << 1  = 0x%02X\n",  (uint8_t)(a << 1));
    printf("a >> 1  = 0x%02X\n",  a >> 1);

    /* -------- Register-manipulation macros on a simulated register -------- */
    uint32_t reg = 0x00000000U;
    printf("\n=== Bit Manipulation Macros ===\n");
    printf("Initial reg  = 0x%08X\n", reg);

    SET_BIT(reg, 5);
    printf("After SET_BIT(reg, 5)      = 0x%08X\n", reg);

    SET_BIT(reg, 12);
    printf("After SET_BIT(reg, 12)     = 0x%08X\n", reg);

    TOGGLE_BIT(reg, 5);
    printf("After TOGGLE_BIT(reg, 5)   = 0x%08X\n", reg);

    printf("READ_BIT(reg, 12) = %u\n", READ_BIT(reg, 12));
    printf("READ_BIT(reg, 5)  = %u\n", READ_BIT(reg, 5));

    CLEAR_BIT(reg, 12);
    printf("After CLEAR_BIT(reg, 12)   = 0x%08X\n", reg);

    return 0;
}
